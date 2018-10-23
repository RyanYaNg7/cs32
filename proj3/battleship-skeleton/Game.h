#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <string>
#include <cassert>

class Point;
class Player;
class GameImpl;

class Game
{
  public:
    Game(int nRows, int nCols);
    ~Game();
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, std::string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    std::string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, bool shouldPause = true);
      // We prevent a Game object from being copied or assigned
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

  private:
    GameImpl* m_impl;
};

#endif // GAME_INCLUDED
