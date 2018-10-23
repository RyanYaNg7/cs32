//
//  game.hpp
//  proj1
//
//  Created by 杨子鸣 on 4/9/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <iostream>

class Arena;
class History;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    History* m_history;
    
    // Helper functions
    std::string takePlayerTurn();
};

bool recommendMove(const Arena& a, int r, int c, int& bestDir);

#endif //GAME_INCLUDED