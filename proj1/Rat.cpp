//
//  rat.cpp
//  proj1
//
//  Created by 杨子鸣 on 4/9/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include "Rat.h"
#include "Arena.h"
#include <iostream>
using namespace std;


class History;

Rat::Rat(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rat must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Rat created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = INITIAL_RAT_HEALTH;
    m_idleTurnsRemaining = 0;
}

int Rat::row() const
{
    return m_row;
}

int Rat::col() const
{
    return m_col;
}

bool Rat::isDead() const
{
    return m_health == 0;
}

void Rat::move()
{
    History& H = m_arena->history();        /////////////////////////////////////////////////////////////
    if (m_idleTurnsRemaining > 0)
    {
        m_idleTurnsRemaining--;
        if(H.record(m_row, m_col))       //ok?
        {
            cerr << "This Rat is staying because of the poison.";
        }
        return;
    }
    
    // Attempt to move in a random direction; if we can't move, don't move
    if (attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col))
    {
        if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row, m_col, EMPTY);
            m_health--;
        }
    }
    
    if (m_health < INITIAL_RAT_HEALTH)
    {
        m_idleTurnsRemaining = POISONED_IDLE_TIME;
        if(H.record(m_row,m_col))          //ok?
        {
            cerr << "This Rat moved is poisoned and cannot move the next time.";
        }
        
    }
}
