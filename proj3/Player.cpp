#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>

using namespace std;
/*
int abs(int a)
{
    if (a >= 0)
        return a;
    else
        return -a;
}


int biggestof4(int la,int ra,int ua,int da)
{
    if (la >= max(max(ra, ua), max(ua, da)))
    {
        return la;
    }
    else if (ra >= max(max(la,ua), max(ua, da)))
    {
        return ra;
    }
    else if (ua >= max(max(la, ra), max(ra, da)))
    {
        return ua;
    }
    else
    {
        return da;
    }
}

Point leastPointOf2(int la,int ra, Point& a, Point& b)
{
    if (la <= min(la,ra))
    {
        return a;
    }
    else
    {
        return b;
    }
}

int AtoB(int la,int ra,    int a,int b)
{
    if (la >= max(la,ra))
    {
        return a;
    }
    else
    {
        return b;
    }
}

Point bestPointOf2(int la,int ra, Point& a, Point& b)
{
    if (la >= max(la,ra))
    {
        return a;
    }
    else
    {
        return b;
    }
}

Point bestPointOf4(int la,int ra,int ua,int da, Point& a, Point& b, Point& c, Point& d)
{
    if (la >= max(max(ra, ua), max(ua, da)))
    {
        return a;
    }
    else if (ra >= max(max(la,ua), max(ua, da)))
    {
        return b;
    }
    else if (ua >= max(max(la, ra), max(ra, da)))
    {
        return c;
    }
    else
    {
        return d;
    }
}


bool attackBefore(Point testP, vector<Point> prevAttack)
{
    vector<Point>::iterator q;
    
    for (q = prevAttack.begin(); q != prevAttack.end(); q++)
    {
        if ((q->r == testP.r) && (q->c == testP.c))
        {
            cerr << "attacked before!" <<endl;
            return true;
        }
    }
    return false;
}
*/

bool isValid(Point p)
{
    return p.r >= 0  &&  p.r < 10  &&  p.c >= 0  &&  p.c < 10;
}

bool tryPlaceShips(Player* p, Board& b, int &numOfShipExist, int &count, Point posOfLastTop = Point(-1,-1))
{
    
    if (count >= 50)
    {
        cerr << "have tried 50 times and all failed!!!" << endl;
        return false;
    }
    if (numOfShipExist == 0)
    {
        cerr << "try all over again!!! " << endl << endl;
        b.unblock();
        b.block();
        count++;
    }
    if (numOfShipExist == p->game().nShips())
        return true;
    //try the first place that can fit the first ship
    //if no such place, we fail, start the function again
    //else
    //try the first place that can fit the second ship
    //if no such place, we fail, start the function again with
    //else
    //try the first place that fit the second ship
    for (int r = 0; r < p->game().rows(); r++)
    {
        for (int c = 0; c < p->game().cols(); c++)
        {
            if (b.placeShip(Point(r,c), numOfShipExist, VERTICAL))  //horizontally place
            {
                numOfShipExist++;
                if (tryPlaceShips(p, b, numOfShipExist, count,  Point(r,c)))
                {
                    cerr << "0000000000................................................" << endl;
                    return true;
                }
            }
            else if (b.placeShip(Point(r,c), numOfShipExist, HORIZONTAL))
            {
                numOfShipExist++;
                if (tryPlaceShips(p, b, numOfShipExist, count, Point(r,c)))
                {
                    cerr << "1111111111111......................................" << endl;
                    return true;
                }
            }
        }
    }
    //when the current ship is not successfully placed, we come to here
    if (numOfShipExist == 0)    //no ship successfully placed
    {
        return tryPlaceShips(p, b, numOfShipExist, count);
    }
    
    if(b.unplaceShip(posOfLastTop, numOfShipExist-1, HORIZONTAL))
        numOfShipExist--;
    if(b.unplaceShip(posOfLastTop, numOfShipExist-1, VERTICAL))
        numOfShipExist--;
    
    cerr << "//////////////////////////////////////////////////////////////unplaced?" << endl;
    return false;
}





//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    virtual bool isHuman() const  { return                                   true; } /////////////check before turnin!
    
private:
    
};

HumanPlayer::HumanPlayer(string nm, const Game& g)
 : Player(nm, g)
{}

void HumanPlayer::recordAttackByOpponent(Point p) {}

void HumanPlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                     bool shipDestroyed, int shipId) {}

bool HumanPlayer::placeShips(Board& b)
{
    //a function that check if the game is big enough to fit ship
    int totalOfLengths = 0;
    for (int s = 0; s < game().nShips(); s++)
    {
        if (game().shipLength(s) > game().rows() || game().shipLength(s) > game().cols())
            return false;
        totalOfLengths += game().shipLength(s);
    }
    if (totalOfLengths > game().rows() * game().cols())
    {
        cerr << "Board is too small to fit all ships" << endl;
        return false;
    }
    
    cout << name() << " must place " << game().nShips() << " ships." << endl;

    
    //place the ships
    char direc = ' ';
    
    for (int k = 0; k < game().nShips(); k++)
    {
        b.display(false);
        do
        {
            char temp;
            cout << "Enter h or v for direction of " << game().shipName(k) << " (length " <<  game().shipLength(k)<< "): ";
            cin >> temp;
            cin.ignore(10000, '\n');
            if (temp != 'h' && temp != 'v')
            {
                cout << "Direction must be h or v." <<endl;
            }
            else
            {
                direc = temp;
            }
        }
        while (direc != 'h' && direc != 'v');
        

        for (;;)
        {
            int row;
            int col;
            if (direc == 'h')
            {
                cout << "Enter row and column of leftmost cell (e.g. 3 5): ";
                getLineWithTwoIntegers(row, col);

                if (!b.placeShip(Point(row, col), k, HORIZONTAL))
                {
                    cout << "The ship can not be placed there." <<endl;
                    continue;
                }
                else
                    break;
                
            }
            
            else if (direc == 'v')
            {
                cout << "Enter row and column of topmost cell (e.g. 3 5): ";
                getLineWithTwoIntegers(row, col);
                
                if (!b.placeShip(Point(row, col), k, VERTICAL))
                {
                    cout << "The ship can not be placed there." <<endl;
                    continue;
                }
                else
                    break;
            }
        }

    }
    
    return true;
}

Point HumanPlayer::recommendAttack()
{
    int row, col;
    cout << "Enter the row and column to attack (e.g, 3 5): ";
    getLineWithTwoIntegers(row, col);
    return Point(row, col);
}


//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class MediocrePlayer : public Player
{
public:
    MediocrePlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    void toState1()
    {
        state = true;
        cerr << "now we are in state 1" <<endl;
    }
    void toState2(){state = false;  cerr << "now we are in state 2" <<endl;}
    bool isState1(){if (state == true) return true; else return false;}
    
private:
    Point randomReturnP();  //for state 1 recommend attack
    Point constrainedRandom(int leftLim, int RightLim, int top, int bottom);  //for state 2 recommend attack
    
    int attackTime;
    bool state;
    char mindBoard[MAXROWS][MAXCOLS];
    Point lastHit;
    //char dir;   // x--->no direction    //u--->up    //d---down     //l--->left    //r--->right
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
: Player(nm, g) , state(true), attackTime(0), lastHit(-1, -1)
{
    for (int n = 0; n < MAXROWS; n++)
    {
        for (int k = 0; k < MAXCOLS; k++)
        {
            mindBoard[n][k] = '.';
        }
    }
}




Point MediocrePlayer::constrainedRandom(int leftLim, int RightLim, int top, int bottom)
{
    Point aim;
    if (randInt(2) == 1)    // if 1, horizontally
    {
        aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
    }
    else    //vertically
    {
        aim = Point(top+randInt(bottom-top+1), lastHit.c);
    }
    
    while (mindBoard[aim.r][aim.c] != '.')  //attacked before
    {
        if (randInt(2) == 1)    // if 1, horizontally
        {
            aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
        }
        else    //vertically
        {
            aim = Point(top+randInt(bottom-top+1), lastHit.c);
        }
    }
    return aim;
}

Point MediocrePlayer::randomReturnP()
{
    Point aim = Point(randInt(10), randInt(10));
    while (mindBoard[aim.r][aim.c] != '.')
    {
        aim = Point(randInt(10), randInt(10));
    }
    return aim;
}



void MediocrePlayer::recordAttackByOpponent(Point p){}  //currently does not do anything

bool MediocrePlayer::placeShips(Board& b)           //currently the place ship function is the same as mediocrePlayer
{
    //TODO:
    int numOfship = 0;
    int count = 0;
    if (tryPlaceShips(this, b, numOfship, count))//if (tryPlaceShips(this, b, 0))
    {
        b.unblock();    //unblock all points
        return true;    //all ships placed
    }
    else
    {
        cerr << "fail to place ship!" << endl;
        return false;
    }
}


Point MediocrePlayer::recommendAttack()
{
    //in state 1
    if (isState1())
    {
        Point temp = randomReturnP();
        mindBoard[temp.r][temp.c] = 'o';
        return temp;
    }
    
    else    //if in state 2
    {
        int leftLim = max(lastHit.c-4, 0);
        int RightLim = min(lastHit.c+4, 9);
        int top = max(lastHit.r-4, 0);
        int bottom = min(lastHit.r+4, 9);
        
        //kind of useless!!!
        attackTime++;
        if (attackTime > (bottom-top+RightLim-leftLim))     //attacked all position point but
        {
            attackTime = 0;
            toState1();
            Point temp = randomReturnP();
            mindBoard[temp.r][temp.c] = 'o';
            return temp;
        }
        Point tmp = constrainedRandom(leftLim, RightLim, top, bottom);
        mindBoard[tmp.r][tmp.c] = 'o';
        return tmp;
    }
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    if (isState1())
    {
        if (!validShot)
        {
            cerr << "invalid shot, do not record!" << endl;
            return;
        }
        if (!shotHit)   //missed
        {
            //mindBoard[p.r][p.c] = 'o';
            return;
        }
        if (shipDestroyed)  //destroyed
        {
            mindBoard[p.r][p.c] = 'X';
            return;
        }
        if (shotHit && !shipDestroyed)  //hit but not destroyed
        {
            mindBoard[p.r][p.c] = 'X';
            lastHit = p;
            toState2();
        }
        
    }
    else
    {
        if (!validShot)
        {
            cerr << "invalid shot, do not record!" << endl;
            return;
        }
        if (!shotHit)   //missed
        {
            //mindBoard[p.r][p.c] = 'o';
            return;
        }
        if (shotHit && !shipDestroyed)  //hit but not destroyed
        {
            mindBoard[p.r][p.c] = 'X';
            return;
        }
        if (shotHit && shipDestroyed)   //hit and destroyed
        {
            mindBoard[p.r][p.c] = 'X';
            attackTime = 0;
            toState1();
        }
    }
    
}


// TODO:  You need to replace this with a real class declaration and
//        implementation.
//typedef AwfulPlayer MediocrePlayer;
// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.




//*********************************************************************
//  GoodPlayer
//*********************************************************************
class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    void toState1(){state = true;  cerr << "now we are in state 1" <<endl;}
    void toState2(){state = false;  cerr << "now we are in state 2" <<endl;}
    
private:
    Point randomReturnP();  //for state 1 recommend attack
    bool checkHori(Point ck)   //check whether a position has the potential to be a ship segment
    {
        int left = 0;
        for (int n = ck.c-1; n >= 0; n--)
        {
            if (mindBoard[ck.r][n] == 'o')
                break;
            left++;
        }
        
        int right = 0;
        for (int n = ck.c+1; n < 10; n++)
        {
            if (mindBoard[ck.r][n] == 'o')
                break;
            right++;
        }

        int limOfShip = (ships.back()).shiplength;
        return (left+right+1) < limOfShip;      //horizontally no ship if true
    }
    
    bool checkVert(Point ck)
    {
        int up = 0;
        for (int n = ck.r-1; n >= 0; n--)
        {
            if (mindBoard[n][ck.c] == 'o')
                break;
            up++;
        }
        
        int down = 0;
        for (int n = ck.r+1; n < 10; n++)
        {
            if (mindBoard[n][ck.c] == 'o')
                break;
            down++;
        }
        
        int limOfShip = (ships.back()).shiplength;
        return (up+down+1) < limOfShip;         //vertically no ship if true
    }
    //Point constrainedRandom(int leftLim, int RightLim, int top, int bottom, char dir = 'x');  //for state 2 recommend attack
    Point advancedTargeting(int leftLim, int RightLim, int top, int bottom, char dir = 'x');

    
    struct Ship
    {
        int shiplength;
        int shipId;
        Ship(int len, int id)
        {
            shiplength = len;
            shipId = id;
        }
    };
    
    int tempTime;
    vector<Ship> ships;
    bool state;
    Point lastHit;
    Point trackHit;
    char mindBoard[MAXROWS][MAXCOLS];
    
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
: Player(nm, g) , state(true), lastHit(-1,-1), tempTime(0), trackHit(-1,-1)
{
    for (int n = 0; n < MAXROWS; n++)
    {
        for (int k = 0; k < MAXCOLS; k++)
        {
            mindBoard[n][k] = '.';
        }
    }
    ships.push_back(Ship(5, 0));
    ships.push_back(Ship(4, 1));
    ships.push_back(Ship(3, 2));
    ships.push_back(Ship(3, 3));
    ships.push_back(Ship(2, 4));
}

Point GoodPlayer::advancedTargeting(int leftLim, int RightLim, int top, int bottom, char dir)
{
    Point aim;
    
    if (dir == 'h') //only horizontally
    {
        //if (isValid(trackHit))  //still on the track
        {
            if (trackHit.c > lastHit.c) //to the right
            {
                aim = Point(trackHit.r, trackHit.c+1);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else if (trackHit.c < lastHit.c) // to the left
            {
                aim = Point(trackHit.r, trackHit.c-1);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else        //trackHit == lastHit
            {
                if (randInt(2) == 1)    // if 1, to right
                {
                    aim = Point(trackHit.r, trackHit.c+1);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r, trackHit.c-1);
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                    }
                }
                else    //if 0, to left
                {
                    aim = Point(trackHit.r, trackHit.c-1);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r, trackHit.c+1);
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                    }
                }

            }
        }
        //else    // not certain about a direction
        /*
        {
            aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
            while (mindBoard[aim.r][aim.c] != '.')
            {
                aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
            }
            return aim;
        }
         */

    }
    else if (dir == 'v')
    {
        //if (isValid(trackHit))  //still on the track
        {
            if (trackHit.r > lastHit.r) //to the bottom
            {
                aim = Point(trackHit.r+1, trackHit.c);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else if (trackHit.r < lastHit.r) // to the top
            {
                aim = Point(trackHit.r-1, trackHit.c);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else        //trackHit == lastHit
            {
                if (randInt(2) == 1)    // if 1, to bottom
                {
                    aim = Point(trackHit.r+1, trackHit.c);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r-1, trackHit.c);
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                    }
                }
                else    //if 0, to top
                {
                    aim = Point(trackHit.r-1, trackHit.c);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r+1, trackHit.c);
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                    }
                }
                
            }
        }
        //else    // not certain about a direction
        /*
        {
            aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
            while (mindBoard[aim.r][aim.c] != '.')
            {
                aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
            }
            return aim;
        }
         */
    }
    
    else    // all direction possible
    {
        //if (isValid(trackHit))
        {
            if (trackHit.c > lastHit.c) //to the right
            {
                aim = Point(trackHit.r, trackHit.c+1);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else if (trackHit.c < lastHit.c) // to the left
            {
                aim = Point(trackHit.r, trackHit.c-1);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else if (trackHit.r > lastHit.r) //to the bottom
            {
                aim = Point(trackHit.r+1, trackHit.c);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else if (trackHit.r < lastHit.r) // to the top
            {
                aim = Point(trackHit.r-1, trackHit.c);
            if (isValid(aim))
                if (mindBoard[aim.r][aim.c] == '.')
                {
                    //mindBoard[aim.r][aim.c] = 'o';
                    return aim;
                }
            }
            else
            {
                int n = randInt(4);
                if (n == 1)    // if 1, to bottom
                {
                    aim = Point(trackHit.r+1, trackHit.c);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r-1, trackHit.c);  //top
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                        else
                        {
                            aim = Point(trackHit.r, trackHit.c+1); //right
                        if (isValid(aim))
                            if (mindBoard[aim.r][aim.c] == '.')
                            {
                                //mindBoard[aim.r][aim.c] = 'o';
                                return aim;
                            }
                            else
                            {
                                aim = Point(trackHit.r, trackHit.c-1);  //left
                            if (isValid(aim))
                                if (mindBoard[aim.r][aim.c] == '.')
                                {
                                    //mindBoard[aim.r][aim.c] = 'o';
                                    return aim;
                                }
                            }
                        }
                    }
                }
                else if (n == 0)   //if 0, to top
                {
                    aim = Point(trackHit.r-1, trackHit.c);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r+1, trackHit.c);  //bottom
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                        else
                        {
                            aim = Point(trackHit.r, trackHit.c+1); //right
                        if (isValid(aim))
                            if (mindBoard[aim.r][aim.c] == '.')
                            {
                                //mindBoard[aim.r][aim.c] = 'o';
                                return aim;
                            }
                            else
                            {
                                aim = Point(trackHit.r, trackHit.c-1);  //left
                            if (isValid(aim))
                                if (mindBoard[aim.r][aim.c] == '.')
                                {
                                    //mindBoard[aim.r][aim.c] = 'o';
                                    return aim;
                                }
                            }
                        }
                    }
                }
                else if (n == 2)    // if 2, to right
                {
                    aim = Point(trackHit.r, trackHit.c+1);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r, trackHit.c-1);  //left
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                        else
                        {
                            aim = Point(trackHit.r-1, trackHit.c);  //top
                        if (isValid(aim))
                            if (mindBoard[aim.r][aim.c] == '.')
                            {
                                //mindBoard[aim.r][aim.c] = 'o';
                                return aim;
                            }
                            else
                            {
                                aim = Point(trackHit.r+1, trackHit.c);  //bottom
                            if (isValid(aim))
                                if (mindBoard[aim.r][aim.c] == '.')
                                {
                                    //mindBoard[aim.r][aim.c] = 'o';
                                    return aim;
                                }
                            }
                        }
                    }
                }
                else   //if 3, to left
                {
                    aim = Point(trackHit.r, trackHit.c-1);
                if (isValid(aim))
                    if (mindBoard[aim.r][aim.c] == '.')
                    {
                        //mindBoard[aim.r][aim.c] = 'o';
                        return aim;
                    }
                    else
                    {
                        aim = Point(trackHit.r, trackHit.c+1);  // to right
                    if (isValid(aim))
                        if (mindBoard[aim.r][aim.c] == '.')
                        {
                            //mindBoard[aim.r][aim.c] = 'o';
                            return aim;
                        }
                        else
                        {
                            aim = Point(trackHit.r-1, trackHit.c);  //top
                        if (isValid(aim))
                            if (mindBoard[aim.r][aim.c] == '.')
                            {
                                //mindBoard[aim.r][aim.c] = 'o';
                                return aim;
                            }
                            else
                            {
                                aim = Point(trackHit.r+1, trackHit.c);  //bottom
                            if (isValid(aim))
                                if (mindBoard[aim.r][aim.c] == '.')
                                {
                                    //mindBoard[aim.r][aim.c] = 'o';
                                    return aim;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //else
    if (randInt(2) == 1)    // if 1, horizontally
    {
        aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
    }
    else    //vertically
    {
        aim = Point(top+randInt(bottom-top+1), lastHit.c);
    }
    
    while (mindBoard[aim.r][aim.c] != '.')  //attacked before
    {
        if (randInt(2) == 1)    // if 1, horizontally
        {
            aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
        }
        else    //vertically
        {
            aim = Point(top+randInt(bottom-top+1), lastHit.c);
        }
    }
    
    //mindBoard[aim.r][aim.c] = 'o';
    return aim;
}
/*

Point GoodPlayer::constrainedRandom(int leftLim, int RightLim, int top, int bottom, char dir)
{
    Point aim;
    if (dir == 'h')     //only find points horizontally
    {
        aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
        while (mindBoard[aim.r][aim.c] != '.')
        {
            aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
        }
        return aim;
    }
    
    else if (dir == 'v')    //only find points vertically
    {
        aim = Point(top+randInt(bottom-top+1), lastHit.c);
        while (mindBoard[aim.r][aim.c] != '.')
        {
            aim = Point(top+randInt(bottom-top+1), lastHit.c);
        }
        return aim;
    }
    
    else    // all direction possible
    {
        if (randInt(2) == 1)    // if 1, horizontally
        {
            aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
        }
        else    //vertically
        {
            aim = Point(top+randInt(bottom-top+1), lastHit.c);
        }
    
        while (mindBoard[aim.r][aim.c] != '.')  //attacked before
        {
            if (randInt(2) == 1)    // if 1, horizontally
            {
                aim = Point(lastHit.r, leftLim+randInt(1+RightLim-leftLim));
            }
            else    //vertically
            {
                aim = Point(top+randInt(bottom-top+1), lastHit.c);
            }
        }
        return aim;
    }
}
*/

Point GoodPlayer::randomReturnP()
{
    if (randInt(2) == 1)
    {
        //all even points first
        Point aim = Point(2*randInt(5), 2*randInt(5));
        int times = 1;
        while (mindBoard[aim.r][aim.c] != '.'  ||  (checkVert(aim) && checkHori(aim)))
        {
            aim = Point(2*randInt(5), 2*randInt(5));
            times++;
            if (times > 80)  //
                break;
        }
        if (mindBoard[aim.r][aim.c] == '.')
            return aim;
    }
    else
    {
    //odd points then
        Point aim = Point(2*randInt(5)+1, 2*randInt(5)+1);
        int times = 1;
        while(mindBoard[aim.r][aim.c] != '.'  ||  (checkVert(aim) && checkHori(aim)))
        {
            aim = Point(2*randInt(5)+1, 2*randInt(5)+1);
            times++;
            if (times > 80)
                break;
        }
        if (mindBoard[aim.r][aim.c] == '.')
            return aim;
    }
    
    //if no odds or even points available, try others
    Point aim = Point(randInt(10), randInt(10));
    while (mindBoard[aim.r][aim.c] != '.'  ||  (checkVert(aim) && checkHori(aim)))
    {
        aim = Point(randInt(10), randInt(10));
        
    }
    return aim;
    
}


void GoodPlayer::recordAttackByOpponent(Point p){}  //does not do anything


bool GoodPlayer::placeShips(Board& b)
{
    //TODO:
    int count = 0;
    int numOfship = 0;
    if (tryPlaceShips(this, b, numOfship, count))
    {
        b.unblock();    //unblock all points
        return true;    //all ships placed
    }
    else
    {
        cerr << "fail to place ship!" << endl;
        return false;
    }
    
}



Point GoodPlayer::recommendAttack()
{
    //in state 1
    if (state)
    {
        Point temp = randomReturnP();
        //mindBoard[temp.r][temp.c] = 'o';
        return temp;
    }
    
    else    //if in state 2
        ///////////////////////////////////////////////////////////////
        //instead of randomly search positions in state2, we could make it go one by one near the target position, up to the attacked position
    {

        int leftLim = max(lastHit.c-4, 0);
        int RightLim = min(lastHit.c+4, 9);
        int top = max(lastHit.r-4, 0);
        int bottom = min(lastHit.r+4, 9);
        
        //kind of useless!!!
        tempTime++;
        if (tempTime > (bottom-top+RightLim-leftLim))     //attacked all position point but
        {
            tempTime = 0;
            toState1();
            Point temp = randomReturnP();
            //mindBoard[temp.r][temp.c] = 'o';
            return temp;
        }
        
        
        Point tmp;
        if (checkHori(lastHit)) //horizontally no ship
        {
            //tmp = constrainedRandom(leftLim, RightLim, top, bottom, 'v');
            tmp = advancedTargeting(leftLim, RightLim, top, bottom, 'v');
        }
        else if (checkVert(lastHit))   //vertically no ship
        {
            //tmp = constrainedRandom(leftLim, RightLim, top, bottom, 'h');
            tmp = advancedTargeting(leftLim, RightLim, top, bottom, 'h');

        }
        else    //horizontally and vertically both could be ship
            //tmp = constrainedRandom(leftLim, RightLim, top, bottom);
            tmp = advancedTargeting(leftLim, RightLim, top, bottom);

    
        //mindBoard[tmp.r][tmp.c] = 'o';
        return tmp;
    }
    
}


void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
//TODO:
    if (state)  //state 1
    {
        if (!validShot)
        {
            cerr << "invalid shot, do not record!" << endl;
            return;
        }
        if (!shotHit)   //missed
        {
            mindBoard[p.r][p.c] = 'o';
            return;
        }
        if (shipDestroyed)  //destroyed
        {
            vector<Ship>::iterator it;
            for (it = ships.begin(); it != ships.end(); it++)
            {
                if (it->shipId == shipId)
                    break;
            }
            if (it != ships.end())
            {
                ships.erase(it);
            }
            
            mindBoard[p.r][p.c] = 'X';
            return;
        }
        if (shotHit && !shipDestroyed)  //hit but not destroyed
        {
            mindBoard[p.r][p.c] = 'X';
            trackHit = p;
            lastHit = p;
            toState2();
        }
        
    }
    else    //state 2
    {
        if (!validShot)
        {
            cerr << "invalid shot, do not record!" << endl;
            return;
        }
        if (!shotHit)   //missed
        {
            mindBoard[p.r][p.c] = 'o';
            trackHit = lastHit;
            return;
        }
        if (shotHit && !shipDestroyed)  //hit but not destroyed
        {
            mindBoard[p.r][p.c] = 'X';
            trackHit = p;
            return;
        }
        if (shotHit && shipDestroyed)   //hit and destroyed
        {
            vector<Ship>::iterator it;
            for (it = ships.begin(); it != ships.end(); it++)
            {
                if (it->shipId == shipId)
                    break;
            }
            if (it != ships.end())
            {
                ships.erase(it);
            }
            trackHit = Point (-1, -1);
            lastHit = Point(-1, -1);
            mindBoard[p.r][p.c] = 'X';
            tempTime = 0;
            toState1();
        }
    }
    
    
}



//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}
