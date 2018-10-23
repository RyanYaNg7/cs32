//
//  mazequeue.cpp
//  hw2
//
//  Created by 杨子鸣 on 4/28/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    queue<Coord> coordqueue;    //declare a queue
    
    coordqueue.push(Coord(sr,sc));  //push the start point
    maze[sr][sc] = '+'; //mark as "discovered"
    
    while(!coordqueue.empty())
    {
        Coord popped = coordqueue.front();
        coordqueue.pop();
        if (popped.r() == er  &&  popped.c() == ec) //if end point, return true
        {
            return true;
        }
        
        if (maze[popped.r()-1][popped.c()] == '.')  //if NORTH is undiscovered and open
        {
            maze[popped.r()-1][popped.c()] = '+';
            coordqueue.push(Coord(popped.r()-1, popped.c()));
        }
        
        if (maze[popped.r()][popped.c()+1] == '.')  //if EAST is undiscovered and open
        {
            maze[popped.r()][popped.c()+1] = '+';
            coordqueue.push(Coord(popped.r(), popped.c()+1));
        }
        
        if (maze[popped.r()+1][popped.c()] == '.')   //if SOUTH is undiscovered and open
        {
            maze[popped.r()+1][popped.c()] = '+';
            coordqueue.push(Coord(popped.r()+1, popped.c()));
        }
        if (maze[popped.r()][popped.c()-1] == '.') //if WEST is undiscovered and open
        {
            maze[popped.r()][popped.c()-1] = '+';
            coordqueue.push(Coord(popped.r(), popped.c()-1));
        }

    }
    return false;
}



/*
 int main()
 {
 
 char maze[10][10] = {
 / r  c   0   1   2   3   4   5   6   7   8   9
 /*0   { 'X','X','X','X','X','X','X','X','X','X'},
 /*1   { 'X','e','.','.','+','.','.','.','.','X'},
 /*2   { 'X','X','.','X','+','X','X','X','X','X'},
 /*3   { 'X','.','.','X','+','X','.','.','.','X'},
 /*4   { 'X','.','.','X','+','+','+','X','.','X'},
 /*5   { 'X','X','X','X','+','X','X','X','.','X'},
 /*6   { 'X','.','X','+','s','+','+','X','X','X'},
 /*7   { 'X','.','X','X','X','+','X','X','.','X'},
 /*8   { 'X','.','.','.','X','+','+','.','.','X'},
 /*9   { 'X','X','X','X','X','X','X','X','X','X'}
 };
 
 if (pathExists(maze, 6,4, 1,1))
 cout << "Solvable!" << endl;
 else
 cout << "Out of luck!" << endl;
 
 }
 */
