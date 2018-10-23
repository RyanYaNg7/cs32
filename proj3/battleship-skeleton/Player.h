#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <string>

class Point;
class Board;
class Game;

class Player
{
  public:
    Player(std::string nm, const Game& g)
     : m_name(nm), m_game(g)
    {}

    virtual ~Player() {}

    std::string name() const { return m_name; }
    const Game& game() const { return m_game; }

    virtual bool isHuman() const { return false; }

    virtual bool placeShips(Board& b) = 0;
    virtual Point recommendAttack() = 0;
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId) = 0;
    virtual void recordAttackByOpponent(Point p) = 0;
      // We prevent any kind of Player object from being copied or assigned
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

  private:
    std::string m_name;
    const Game& m_game;
};

Player* createPlayer(std::string type, std::string nm, const Game& g);

#endif // PLAYER_INCLUDED
