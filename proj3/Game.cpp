#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

#include <algorithm>
#include <vector>
using namespace std;
Player* playGame(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);

class Ship
{
public:
    Ship(int length,char symbol, string name)
    {
        LenS = length;
        SmbS = symbol;
        NmS = name;
    }
    int LenS;
    string NmS;
    char SmbS;
};

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
    
private:
    int m_row;
    int m_col;
    int numOfShips;
    vector<Ship> Ships;
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
{
    m_row = nRows;
    m_col = nCols;
    numOfShips = 0;
    
    // This compiles but may not be correct
}

int GameImpl::rows() const
{
    return m_row;
}

int GameImpl::cols() const
{
    return m_col;
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    //if not
    //add a new type of ship to the game
    Ship S(length, symbol, name);
    Ships.push_back(S);
    numOfShips++;
    return true;
}

int GameImpl::nShips() const
{
    return numOfShips;
}

int GameImpl::shipLength(int shipId) const
{
    return Ships[shipId].LenS;
    
}

char GameImpl::shipSymbol(int shipId) const
{
    return Ships[shipId].SmbS;
}

string GameImpl::shipName(int shipId) const
{
    return Ships[shipId].NmS;
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    b1.clear();
    b2.clear();
    if (!p1->placeShips(b1))
    {
        cerr << "player one fail to place the ship" << endl;
        return nullptr;
    }
    
    if (!p2->placeShips(b2))
    {
        cerr << "player two fail to place the ship" << endl;
        return nullptr;
    }
    
    //let's play the game
    Player* winner = playGame(p1, p2, b1, b2, shouldPause);
    cout << winner->name() << " wins!" <<endl;
    cout << "logout" << endl;
    cout << "Saving session..." << endl;
    cout << "...copying shared history..." << endl;
    cout << "...saving history...truncating history files..." << endl;
    cout << "...completed." << endl;

    return winner;
}

Player* playGame(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    bool shotH = false;
    bool shipDs = false;
    int shipDsID = -1;
    
    cout << p1->name() << "'s turn. Board for " << p2->name() <<endl;
    b2.display(p1->isHuman());
    
    for(;;)
    {
        Point a = p1->recommendAttack();
        bool attackresult = b2.attack(a, shotH, shipDs, shipDsID);
        p1->recordAttackResult(a, attackresult, shotH, shipDs, shipDsID);
        if(attackresult)
        {
            if (!shotH) // is missed
            {
                cout << p1->name() << " attack (" << a.r << "," << a.c << ") and missed, resulting in:" <<endl;
                b2.display(p1->isHuman());
                if (shouldPause)
                {
                    cout << "Press enter to continue: ";
                    string j;
                    getline(cin,j);
                }
                break;
            }
            else    //is hit something
            {
                if (shipDs)
                {
                    cout << p1->name() << " attack (" << a.r << "," << a.c << ") and destroyed the " << (p1->game()).shipName(shipDsID) << ", resulting in:" <<endl;
                    b2.display(p1->isHuman());
                    if (b2.allShipsDestroyed())
                    {
                        if (p2->isHuman())
                        {
                            b1.display(p1->isHuman());
                        }
                        return p1;
                    }
                    
                    if (shouldPause)
                    {
                        cout << "Press enter to continue: ";
                        string j;
                        getline(cin,j);
                    }
                    break;
                    
                }
                else
                {
                    cout << p1->name() << " attack (" << a.r << "," << a.c << ") and hit something, resulting in:" <<endl;
                    b2.display(p1->isHuman());
                    if (shouldPause)
                    {
                        cout << "Press enter to continue: ";
                        string j;
                        getline(cin,j);
                    }
                    break;
                }
            }
        }
        else
        {
            cout << p1->name() << " wasted a shot at (" << a.r << "," << a.c << ")." << endl;
            break;
        }
    }
    // when the attack is finished and no pointer is returned
    return playGame(p2, p1, b2, b1, shouldPause);
    
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())       //length requirement
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))     //printable
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')        //aliasing
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

