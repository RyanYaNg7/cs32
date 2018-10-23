//
//  globals.hpp
//  proj1
//
//  Created by 杨子鸣 on 4/9/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <iostream>
class Arena;

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXRATS = 100;           // max number of rats allowed
const int INITIAL_RAT_HEALTH = 2;  // initial rat health
const int POISONED_IDLE_TIME = 1;  // poisoned rat idles this many turns
//   between moves

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;



int randInt(int min, int max);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
int computeDanger(const Arena& a, int r, int c);
void clearScreen();

#endif //GLOBALS_INCLUDED