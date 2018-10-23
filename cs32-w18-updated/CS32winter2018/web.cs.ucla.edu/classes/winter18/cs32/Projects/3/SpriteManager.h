#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include "freeglut.h"

#ifndef GL_BGR
#define GL_BGR GL_BGR_EXT
#endif

#ifndef GL_BGRA
#define GL_BGRA GL_BGRA_EXT
#endif

#include "GameConstants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

static const double VISIBLE_MIN_X = -2.39;
static const double VISIBLE_MAX_X = 2.39;
static const double VISIBLE_MIN_Y = -2.1;
static const double VISIBLE_MAX_Y = 1.9;
static const double VISIBLE_MIN_Z = -20;
// static const double VISIBLE_MAX_Z = -6;

class SpriteManager
{
public:

	SpriteManager()
	 : m_mipMapped(true)
	{
	}

	void setMipMapping(bool status)
	{
		m_mipMapped = status;
	}

	bool loadSprite(std::string filename_tga, int imageID, int frameNum)
	{
		  // Load Texture Data From TGA File

		int spriteID = getSpriteID(imageID, frameNum);
		if (INVALID_SPRITE_ID == spriteID)
			return false;

		m_frameCountPerSprite[imageID]++;	// keep track of how many frames per sprite we loaded

		std::string line;
		std::string contents = "";
		std::ifstream tgaFile(filename_tga, std::ios::in|std::ios::binary);

		if (!tgaFile)
			return false;

		char type[3];
		char info[6];

		  // Read file header info
		tgaFile.read(type, 3);
		tgaFile.seekg(12);
		tgaFile.read(info, 6);
		unsigned int textureWidth = static_cast<unsigned char>(info[0]) + static_cast<unsigned char>(info[1]) * 256;
		unsigned int textureHeight = static_cast<unsigned char>(info[2]) + static_cast<unsigned char>(info[3]) * 256;
		unsigned char byteCount = static_cast<unsigned char>(info[4]) / 8;
		long imageSize = textureWidth * textureHeight * byteCount;
		char* imageData = new char[imageSize];
		tgaFile.seekg(18);
		  // Read image data
		tgaFile.read(imageData, imageSize);
		if (!tgaFile)
		{
			delete [] imageData;
			return false;
		}

		  //image type either 2 (color) or 3 (greyscale)
		if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
			return false;

		if (byteCount != 3 && byteCount != 4)
			return false;

		  // Transfer Texture To OpenGL

		glEnable(GL_DEPTH_TEST);

		  // allocate a texture handle
		GLuint glTextureID;
		glGenTextures(1, &glTextureID);

		  // bind our new texture
		glBindTexture(GL_TEXTURE_2D, glTextureID);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		if (m_mipMapped)
		{
			  // when texture area is small, bilinear filter the closest mipmap
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			  // when texture area is large, bilinear filter the first mipmap
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		  // Have the texture wrap both vertically and horizontally.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLfloat>(GL_REPEAT));
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLfloat>(GL_REPEAT));

		if (m_mipMapped)
		{
			  // build our texture mipmaps
			  // byteCount of 3 means that BGR data is being supplied. byteCount of 4 means that BGRA data is being supplied.
            makeMipmaps(byteCount, textureWidth, textureHeight, imageData);
		}
		else
		{
			  // byteCount of 3 means that BGR data is being supplied. byteCount of 4 means that BGRA data is being supplied.
			if (3 == byteCount)
				glTexImage2D(GL_TEXTURE_2D, 0, 3, textureWidth, textureHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
			else if (4 == byteCount)
				glTexImage2D(GL_TEXTURE_2D, 0, 4, textureWidth, textureHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, imageData);
		}

		delete [] imageData;

		m_imageMap[spriteID] = glTextureID;

		return true;
	}

	int getNumFrames(int imageID) const
	{
		auto it = m_frameCountPerSprite.find(imageID);
		if (it == m_frameCountPerSprite.end())
			return 0;

		return it->second;
	}

	bool plotSprite(int imageID, int frame, double x, double y, int angleDegrees, double size)
	{
		int spriteID = getSpriteID(imageID, frame);
		if (INVALID_SPRITE_ID == spriteID)
			return false;

		auto it = m_imageMap.find(spriteID);
		if (it == m_imageMap.end())
			return false;

		glPushMatrix();

		double finalWidth, finalHeight;

		finalWidth = SPRITE_WIDTH_GL * size;
		finalHeight = SPRITE_HEIGHT_GL * size;

		// object's x/y location is center-based, but sprite plotting is upper-left-corner based
		const double xoffset = 0;// finalWidth / 2;
		const double yoffset = 0;// finalHeight / 2;

        double gx, gy, gz;
        convertToGlutCoords(x, y, gx, gy, gz);
		glTranslatef(static_cast<GLfloat>(gx-xoffset),static_cast<GLfloat>(gy-yoffset),static_cast<GLfloat>(gz));
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glEnable (GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, it->second);

		glColor3f(1.0, 1.0, 1.0);

		double cx1,cx2,cx3,cx4;
		double cy1,cy2,cy3,cy4;

		cx1 = cy1 = 0;
		cx2 = 1; cy2 = 0;
		cx3 = 1; cy3 = 1;
		cx4 = 0; cy4 = 1;

		double rx1, ry1, rx2, ry2, rx3, ry3, rx4, ry4;
		rotate(-finalWidth/2, -finalHeight/2, angleDegrees, rx1, ry1);
		rotate(finalWidth/2, -finalHeight/2, angleDegrees, rx2, ry2);
		rotate(finalWidth/2, finalHeight/2, angleDegrees, rx3, ry3);
		rotate(-finalWidth/2, finalHeight/2, angleDegrees, rx4, ry4);

		glBegin(GL_QUADS);
		glTexCoord2d(cx1, cy1);
		glVertex3f(static_cast<GLfloat>(rx1), static_cast<GLfloat>(ry1), 0);
		glTexCoord2d(cx2, cy2);
		glVertex3f(static_cast<GLfloat>(rx2), static_cast<GLfloat>(ry2), 0);
		glTexCoord2d(cx3, cy3);
		glVertex3f(static_cast<GLfloat>(rx3), static_cast<GLfloat>(ry3), 0);
		glTexCoord2d(cx4, cy4);
		glVertex3f(static_cast<GLfloat>(rx4), static_cast<GLfloat>(ry4), 0);
		glEnd();


		/*
		glBegin (GL_QUADS);
		  glTexCoord2d(cx1, cy1);
		  glVertex3f(0, 0, 0);
		  glTexCoord2d(cx2, cy2);
		  glVertex3f(static_cast<GLfloat>(finalWidth), 0, 0);
		  glTexCoord2d(cx3, cy3);
		  glVertex3f(static_cast<GLfloat>(finalWidth), static_cast<GLfloat>(finalHeight), 0);
		  glTexCoord2d(cx4, cy4);
		  glVertex3f(0, static_cast<GLfloat>(finalHeight), 0);
		glEnd();
		*/

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

		glPopAttrib();
		glPopMatrix();

		return true;
	}

	~SpriteManager()
	{
		for (auto it = m_imageMap.begin(); it != m_imageMap.end(); it++)
			glDeleteTextures(1, &it->second);
	}

private:

	static void rotate(double x, double y, double degrees, double& xout, double& yout)
	{
        static const double PI = 4 * atan(1.0);
		double theta = (degrees / 360.0) * (2 * PI);
		xout = x * cos(theta) - y * sin(theta);
		yout = y * cos(theta) + x * sin(theta);
	}
    
    static void convertToGlutCoords(double x, double y, double& gx, double& gy, double& gz)
    {
        x /= VIEW_WIDTH;
        y /= VIEW_HEIGHT;
        gx = 2 * VISIBLE_MIN_X + .3 + x * 2 * (VISIBLE_MAX_X - VISIBLE_MIN_X);
        gy = 2 * VISIBLE_MIN_Y +      y * 2 * (VISIBLE_MAX_Y - VISIBLE_MIN_Y);
        gz = .6 * VISIBLE_MIN_Z;
    }

	bool					m_mipMapped;
	std::map<int, GLuint>	m_imageMap;
	std::map<int, int>		m_frameCountPerSprite;

	static const int INVALID_SPRITE_ID = -1;
	static const int MAX_IMAGES = 1000;
	static const int MAX_FRAMES_PER_SPRITE = 100;

	int getSpriteID(int imageID, int frame) const
	{
		if (imageID >= MAX_IMAGES || frame >= MAX_FRAMES_PER_SPRITE)
			return INVALID_SPRITE_ID;

		return imageID * MAX_FRAMES_PER_SPRITE + frame;
	}
    
    void makeMipmaps(unsigned char byteCount, unsigned int textureWidth, unsigned int textureHeight, char* imageData)
    {
        int format = (byteCount == 3 ? GL_BGR : GL_BGRA);
#ifdef __APPLE__
        int internalFormat = (byteCount == 3 ? GL_RGB : GL_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
#else
        gluBuild2DMipmaps(GL_TEXTURE_2D, byteCount, textureWidth, textureHeight, format, GL_UNSIGNED_BYTE, imageData);
#endif
    }
};

#endif // SPRITEMANAGER_H_
