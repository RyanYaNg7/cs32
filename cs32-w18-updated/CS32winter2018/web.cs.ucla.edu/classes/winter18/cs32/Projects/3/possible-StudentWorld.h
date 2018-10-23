// A possible interface for StudentWorld.  You may use all, some, or none
// of this, as you wish.

#ifndef STUDENTWORLD_INCLUDED
#define STUDENTWORLD_INCLUDED

#include "GameWorld.h"
#include <string>

class Actor;
class Player;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();

      // If there's at least one alien that's collided with a, return
      // a pointer to one of them; otherwise, return a null pointer.
    Actor* getOneCollidingAlien(const Actor* a) const;

      // If the player has collided with a, return a pointer to the player;
      // otherwise, return a null pointer.
    Player* getCollidingPlayer(const Actor* a) const;

      // Is the player in the line of fire of a, which might cause a to attack?
    bool playerInLineOfFire(const Actor* a) const;

      // Add an actor to the world.
    void addActor(Actor* a);

      // Record that one more alien on the current level has been destroyed.
    void recordAlienDestroyed();
};

#endif // STUDENTWORLD_INCLUDED
