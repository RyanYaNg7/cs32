#include "freeglut.h"
#include "GameController.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "SoundFX.h"
#include "SpriteManager.h"
#include <string>
#include <map>
#include <utility>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*
spriteWidth = .67
spritesPerRow = 16

RowWidth = spriteWidth*spritesPerRow = 10.72
PixelWidth = RowWidth/256 = .041875
newSpriteWidth = PixelWidth * NumPixels

spriteHeight = .54
spritesPerRow = 16

RowHeight = spriteHeight*spritesPerCol = 8.64

PixelHeight = RowHeight/256 = .03375

newSpriteHeight = PixelHeight * NumPixels
*/

static const int WINDOW_WIDTH = 768; //1024;
static const int WINDOW_HEIGHT = 768;

static const int PERSPECTIVE_NEAR_PLANE = 4;
static const int PERSPECTIVE_FAR_PLANE	= 22;

static const double FONT_SCALEDOWN = 760.0;

static const double SCORE_Y = 3.8;
static const double SCORE_Z = -10;

static const int MS_PER_FRAME = 5;

static void drawPrompt(string mainMessage, string secondMessage);
static void drawScoreAndLives(string);

enum GameController::GameControllerState : int {
	welcome, init, makemove, animate, contgame, finishedlevel, cleanup, gameover, prompt, quit, not_applicable
};

void GameController::initDrawersAndSounds()
{
	struct SpriteInfo
	{
		int imageID;
		int frameNum;
		std::string tgaFileName;
	};

	SpriteInfo drawers[] = {
		{ IID_NACHENBLASTER , 0, "ship.tga"},
		{ IID_SMALLGON, 0, "smallgon.tga" },
		{ IID_SMOREGON, 0, "smoregon.tga" },
		{ IID_SNAGGLEGON, 0, "snagglegon.tga" },
		{ IID_REPAIR_GOODIE, 0, "health.tga" },
		{ IID_LIFE_GOODIE, 0, "life.tga" },
		{ IID_TORPEDO_GOODIE, 0, "sonar.tga" },
		{ IID_TORPEDO, 0, "torpedo.tga" },
		{ IID_TURNIP, 0, "turnip.tga" },
		{ IID_CABBAGE, 0, "cabbage.tga"},
		{ IID_STAR, 0, "star1.tga" },
		{ IID_EXPLOSION, 0, "explosion.tga" },
	};

	SoundMapType::value_type sounds[] = {
		make_pair(SOUND_THEME          , "theme.wav"),
		make_pair(SOUND_GOODIE         , "goodie.wav"),
		make_pair(SOUND_BLAST          , "ouch.wav"),
		make_pair(SOUND_PLAYER_SHOOT   , "laser.wav"),
		make_pair(SOUND_ALIEN_SHOOT    , "laser2.wav"),
		make_pair(SOUND_FINISHED_LEVEL , "finished.wav"),
		make_pair(SOUND_DEATH          , "blowup.wav"),
		make_pair(SOUND_TORPEDO        , "torpedo.wav"),
	};

	for (int k = 0; k < sizeof(drawers)/sizeof(drawers[0]); k++)
	{
		string path = m_gw->assetDirectory();
		if (!path.empty())
			path += '/';
		const SpriteInfo& d = drawers[k];
		if (!m_spriteManager.loadSprite(path + d.tgaFileName, d.imageID, d.frameNum))
			exit(1);
	}
	for (int k = 0; k < sizeof(sounds)/sizeof(sounds[0]); k++)
		m_soundMap[sounds[k].first] = sounds[k].second;
}

static void doSomethingCallback()
{
	Game().doSomething();
}

static void reshapeCallback(int w, int h)
{
	Game().reshape(w, h);
}

static void keyboardEventCallback(unsigned char key, int x, int y)
{
	Game().keyboardEvent(key, x, y);
}

static void specialKeyboardEventCallback(int key, int x, int y)
{
	Game().specialKeyboardEvent(key, x, y);
}

static void timerFuncCallback(int)
{
	Game().doSomething();
	glutTimerFunc(MS_PER_FRAME, timerFuncCallback, 0);
}

void GameController::run(int argc, char* argv[], GameWorld* gw, string windowTitle)
{
	gw->setController(this);
	m_gw = gw;
	setGameState(welcome);
	m_lastKeyHit = INVALID_KEY;
	m_singleStep = false;
	m_curIntraFrameTick = 0;
	m_playerWon = false;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(windowTitle.c_str());

	initDrawersAndSounds();

	glutKeyboardFunc(keyboardEventCallback);
	glutSpecialFunc(specialKeyboardEventCallback);
	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(doSomethingCallback);
	glutTimerFunc(MS_PER_FRAME, timerFuncCallback, 0);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
	delete m_gw;
}

void GameController::keyboardEvent(unsigned char key, int /* x */, int /* y */)
{
	switch (key)
	{
		case 'a': case '4': m_lastKeyHit = KEY_PRESS_LEFT;	break;
		case 'd': case '6': m_lastKeyHit = KEY_PRESS_RIGHT; break;
		case 'w': case '8': m_lastKeyHit = KEY_PRESS_UP;	break;
		case 's': case '2': m_lastKeyHit = KEY_PRESS_DOWN;	break;
		case 't':			m_lastKeyHit = KEY_PRESS_TAB;	break;
		case 'f':			m_singleStep = true;			break;
		case 'r':			m_singleStep = false;			break;
		case 'q': case 'Q': setGameState(quit);				break;
		default:			m_lastKeyHit = key;				break;
	}
}

void GameController::specialKeyboardEvent(int key, int /* x */, int /* y */)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:	 m_lastKeyHit = KEY_PRESS_LEFT;	 break;
		case GLUT_KEY_RIGHT: m_lastKeyHit = KEY_PRESS_RIGHT; break;
		case GLUT_KEY_UP:	 m_lastKeyHit = KEY_PRESS_UP;	 break;
		case GLUT_KEY_DOWN:	 m_lastKeyHit = KEY_PRESS_DOWN;	 break;
		default:			 m_lastKeyHit = INVALID_KEY;	 break;
	}
}

void GameController::playSound(int soundID)
{
	if (soundID == SOUND_NONE)
    {
        SoundFX().abortClip();
		return;
    }

	SoundMapType::const_iterator p = m_soundMap.find(soundID);
	if (p != m_soundMap.end())
	{
		string path = m_gw->assetDirectory();
		if (!path.empty())
			path += '/';
		SoundFX().playClip(path + p->second);
	}
}

void GameController::setGameState(GameControllerState s)
{
	if (m_gameState != quit)
		m_gameState = s;
}

void GameController::setGameStateAfterPrompting(GameControllerState s,
									string mainMessage, string secondMessage)
{
	m_mainMessage = mainMessage;
	m_secondMessage = secondMessage;
	m_nextStateAfterPrompt = s;
	setGameState(prompt);
}

void GameController::quitGame()
{
	setGameState(quit);
}

void GameController::doSomething()
{
	switch (m_gameState)
	{
		case not_applicable:
			break;
		case welcome:
			playSound(SOUND_THEME);
			setGameStateAfterPrompting(init, "Welcome to NachenBlaster!",
											"Press Enter to begin play...");
			break;
		case init:
			{
				int status = m_gw->init();
				SoundFX().abortClip();
				if (status == GWSTATUS_PLAYER_WON)
				{
					m_playerWon = true;
					setGameState(gameover);
				}
				else if (status == GWSTATUS_LEVEL_ERROR)
					setGameStateAfterPrompting(quit,
						"Error in level data file encoding!",
						"Press Enter to quit...");
				else
					setGameState(makemove);
			}
			break;
		case makemove:
			m_curIntraFrameTick = ANIMATION_POSITIONS_PER_TICK;
			m_nextStateAfterAnimate = not_applicable;
			{
				int status = m_gw->move();
				if (status == GWSTATUS_PLAYER_DIED)
				{
					  // animate one last frame so the player can see what happened
					m_nextStateAfterAnimate = (m_gw->isGameOver() ? gameover : contgame);
				}
				else if (status == GWSTATUS_FINISHED_LEVEL)
				{
					m_gw->advanceToNextLevel();
					  // animate one last frame so the player can see what happened
					m_nextStateAfterAnimate = finishedlevel;
				}
			}
			setGameState(animate);
			break;
		case animate:
			displayGamePlay();
			if (m_curIntraFrameTick-- <= 0)
			{
				if (m_nextStateAfterAnimate != not_applicable)
					setGameState(m_nextStateAfterAnimate);
				else
				{
					int key;
					if (!m_singleStep  ||  getLastKey(key))
						setGameState(makemove);
				}
			}
			break;
		case contgame:
			setGameStateAfterPrompting(cleanup, "You lost a life!",
										"Press Enter to continue playing...");
			break;
		case finishedlevel:
			setGameStateAfterPrompting(cleanup, "Woot! You finished the level!",
										"Press Enter to continue playing...");
			break;
		case cleanup:
			m_gw->cleanUp();
			setGameState(init);
			break;
		case gameover:
			{
				ostringstream oss;
				oss << (m_playerWon ? "You won the game!" : "Game Over!")
					<< " Final score: " << m_gw->getScore() << "!";
				setGameStateAfterPrompting(quit, oss.str(), "Press Enter to quit...");
				m_gw->cleanUp();
			}
			break;
		case prompt:
			drawPrompt(m_mainMessage, m_secondMessage);
			{
				int key;
				if (getLastKey(key) && key == '\r')
					setGameState(m_nextStateAfterPrompt);
			}
			break;
		case quit:
            SoundFX().abortClip();
			glutLeaveMainLoop();
			break;
	}
}

void GameController::displayGamePlay()
{
	glEnable(GL_DEPTH_TEST); // must be done each time before displaying graphics or gets disabled for some reason
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef _MSC_VER
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
#pragma GCC diagnostic pop
#endif

    GraphObject::drawAllObjects(
        [=](int imageID, int animationNumber, double x, double y, int angle, double size)
        {
            int frame = animationNumber % m_spriteManager.getNumFrames(imageID);
            m_spriteManager.plotSprite(imageID, frame, x, y, angle, size);
            
        });

	drawScoreAndLives(m_gameStatText);

	glutSwapBuffers();
}

void GameController::reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
#ifdef _MSC_VER
	gluPerspective(45.0, double(WINDOW_WIDTH) / WINDOW_HEIGHT, PERSPECTIVE_NEAR_PLANE, PERSPECTIVE_FAR_PLANE);
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	gluPerspective(45.0, double(WINDOW_WIDTH) / WINDOW_HEIGHT, PERSPECTIVE_NEAR_PLANE, PERSPECTIVE_FAR_PLANE);
#pragma GCC diagnostic pop
#endif
	glMatrixMode (GL_MODELVIEW);
}

static void doOutputStroke(double x, double y, double z, double size, const char* str, bool centered)
{
	if (centered)
	{
		double len = glutStrokeLength(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char*>(str)) / FONT_SCALEDOWN;
		x = -len / 2;
		size = 1;
	}
	GLfloat scaledSize = static_cast<GLfloat>(size / FONT_SCALEDOWN);
	glPushMatrix();
	glLineWidth(1);
	glLoadIdentity();
	glTranslatef(static_cast<GLfloat>(x), static_cast<GLfloat>(y), static_cast<GLfloat>(z));
	glScalef(scaledSize, scaledSize, scaledSize);
	for ( ; *str != '\0'; str++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *str);
	glPopMatrix();
}

//static void outputStroke(double x, double y, double z, double size, const char* str)
//{
//	doOutputStroke(x, y, z, size, str, false);
//}

static void outputStrokeCentered(double y, double z, const char* str)
{
	doOutputStroke(0, y, z, 1, str, true);
}

static void drawPrompt(string mainMessage, string secondMessage)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	glLoadIdentity ();
	outputStrokeCentered(1, -5, mainMessage.c_str());
	outputStrokeCentered(-1, -5, secondMessage.c_str());
	glutSwapBuffers();
}

static void drawScoreAndLives(string gameStatText)
{
	static int RATE = 1;
	static GLfloat rgb[3] =
		{ static_cast<GLfloat>(.6), static_cast<GLfloat>(.6), static_cast<GLfloat>(.6) };
	for (int k = 0; k < 3; k++)
	{
		double strength = rgb[k] + randInt(-RATE, RATE) / 100.0;
		if (strength < .6)
			strength = .6;
		else if (strength > 1.0)
			strength = 1.0;
		rgb[k] = static_cast<GLfloat>(strength);
	}
	glColor3f(rgb[0], rgb[1], rgb[2]);
	outputStrokeCentered(SCORE_Y, SCORE_Z, gameStatText.c_str());
}
