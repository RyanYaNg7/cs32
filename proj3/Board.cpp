#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;

  private:
      // TODO:  Decide what private members you need.  Here's one that's likely
      //        to be useful:
    const Game& m_game;
    char board[MAXROWS][MAXCOLS];
    
};

BoardImpl::BoardImpl(const Game& g)
 : m_game(g)
{
    for (int r = 0; r < MAXROWS; r++)
        for (int c = 0; c < MAXCOLS; c++)
            board[r][c] = '.';
}

void BoardImpl::clear()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            board[r][c] = '.';
}

void BoardImpl::block()
{
      // Block cells with 50% probability
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (randInt(2) == 0)
            {
                board[r][c] = '_'; // code to block cell (r,c)
            }
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
        {
            // code to unblock cell (r,c) if blocked
            if (board[r][c] == '_')
                board[r][c] = '.';
        }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    char sym = m_game.shipSymbol(shipId);
    int len = m_game.shipLength(shipId);
    if(shipId < 0  ||  shipId >= m_game.nShips())
    {
        cerr << "ship id is not valid!" << endl;
        return false;
    }
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (sym == board[r][c])   //already exist
            {
                cerr << "ship symbol already exsists!" << endl;
                return false;
            }
    
    if (!m_game.isValid(topOrLeft))
    {
        cerr << "toporleft position not valid!" <<endl;
        return false;
    }
    if (dir == HORIZONTAL)
    {
        if (topOrLeft.c+len > m_game.cols())
        {
            cerr << "ship would be out of boundary!" << endl;
            return false;
        }
        for (int n = topOrLeft.c; n < topOrLeft.c + len; n++)
        {
            if (board[topOrLeft.r][n] != '.')
            {
                cerr << "the position is occupied by something or blocked!" << endl;
                return false;
            }
        }
        
        for (int n = topOrLeft.c; n < topOrLeft.c + len; n++)
        {
            cerr << "successfully placed!" <<endl;
            board[topOrLeft.r][n] = sym;
        }
        return true;
    }
    else if (dir == VERTICAL)
    {
        if (topOrLeft.r+len > m_game.rows())
        {
            cerr << "ship would be out of boundary!" << endl;
            return false;
        }
        for (int n = topOrLeft.r; n < topOrLeft.r+len; n++)
        {
            if (board[n][topOrLeft.c] != '.')
            {
                cerr << "the position is occupied by something or blocked!" << endl;
                return false;
            }
        }
        
        for (int n = topOrLeft.r; n < topOrLeft.r + len; n++)
        {
            cerr << "successfully placed!" <<endl;
            board[n][topOrLeft.c] = sym;
        }
        return true;
    }
    else
    {
        cerr << "dir is not valid!"<<endl;
        return false;
    }
        
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    if(shipId < 0  ||  shipId >= m_game.nShips())
    {
        cerr << "ship id is not valid!" << endl;
        return false;
    }
    
    //not contain the entire ship
    if (!m_game.isValid(topOrLeft))
    {
        cerr << "toporleft position not valid!" <<endl;
        return false;
    }

    if (dir == HORIZONTAL)
    {
        for (int n = topOrLeft.c; n < topOrLeft.c+m_game.shipLength(shipId); n++)
        {
            if (board[topOrLeft.r][n] != m_game.shipSymbol(shipId))
                return false;
        }
    }
    else if (dir == VERTICAL)
    {
        for (int n = topOrLeft.r; n < topOrLeft.r+m_game.shipLength(shipId); n++)
        {
            if (board[n][topOrLeft.c] != m_game.shipSymbol(shipId))
                return false;
        }
    }
    else
    {
        cerr << "wrong direction" <<endl;
        return false;
    }
    
    //remove the ship
    cerr << "the ship will be successfully removed."<<endl;
    if (dir == HORIZONTAL)
    {
        for (int n = topOrLeft.c; n < topOrLeft.c+m_game.shipLength(shipId); n++)
        {
            board[topOrLeft.r][n] = '.';
        }
        return true;
    }
    else
    {
        for (int n = topOrLeft.r; n < topOrLeft.r+m_game.shipLength(shipId); n++)
        {
            board[n][topOrLeft.c] = '.';
        }
        return true;
    }

}

void BoardImpl::display(bool shotsOnly) const
{
    //first line
    cout << "  ";
    for (int n = 0; n < m_game.cols(); n++)
        cout << n;
    cout << endl;
    
    //the rest
    for (int n = 0; n < m_game.rows(); n++)
    {
        cout << n << " ";
        if (!shotsOnly)
        {
            for (int k = 0; k < m_game.cols(); k++)
                cout << board[n][k];
        }
        else
        {
            for (int k = 0; k < m_game.cols(); k++)
            {
                int test = 0;
                for (int i = 0; i < m_game.nShips(); i++)
                {
                    if (board[n][k] == m_game.shipSymbol(i))
                    {
                        cout << '.';
                        test++;
                        break;
                    }
                }
                if (test == 1)
                    continue;
                else
                    cout << board[n][k];
            }
        }
        cout << endl;
    }
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    //check the validity of attack
    if(!m_game.isValid(p))
    {
        cerr << "attacking position not valid!";
        return false;
    }
    if(board[p.r][p.c] == 'X' || board[p.r][p.c] == 'o')
    {
        cerr << "attaking position has been attacked before!";
        return false;
    }
    
    //make attack
    char storeId = -1;
    for (int n = 0; n < m_game.nShips(); n++)
    {
        if (board[p.r][p.c] == m_game.shipSymbol(n))
        {
            shotHit = true;
            storeId = m_game.shipSymbol(n);
            board[p.r][p.c] = 'X';
            break;
        }
    }
    
    if (board[p.r][p.c] == 'X')         //if attacked on a undamaged ship segment
    {
        int left = 0;
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (board[p.r][c] == storeId)
            {
                left++;
            }
        }
        for (int r = 0; r < m_game.rows(); r++)
        {
            if (board[r][p.c] == storeId)
            {
                left++;
            }
        }
        
        if (left == 0)  //nothing left of the ship
        {
            cerr << "the ship is destroyed!" <<endl;
            shipDestroyed = true;
            for (int i = 0; i < m_game.nShips(); i++)
            {
                if (storeId == m_game.shipSymbol(i))
                {
                    shipId = i;
                    break;
                }
            }

            return true;
        }
        else
        {
            cerr << "the ship has not been totally destroyed." <<endl;
            shipDestroyed = false;
            return true;
        }
    }
    else
    {
        board[p.r][p.c] = 'o';
        cerr << "attack missed!" <<endl;
        shotHit = false;
        return true;
    }
    
}

bool BoardImpl::allShipsDestroyed() const
{
    for (int n = 0; n < m_game.nShips(); n++)
    {
        for (int r = 0; r < m_game.rows(); r++)
        {
            for (int c = 0; c < m_game.cols(); c++)
            {
                if (board[r][c] == m_game.shipSymbol(n))
                    return false;
            }
        }
    }
    cerr << "all ships are destroyed!" <<endl;
    return true;
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
