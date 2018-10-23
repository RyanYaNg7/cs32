//
//  mazestack.cpp
//  hw2
//
//  Created by 杨子鸣 on 4/28/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//
#include <iostream>
#include <stack>
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
    stack<Coord> coordStack;     // declare a stack of Coords
    
    coordStack.push(Coord(sr,sc));  //push the starting point
    maze[sr][sc] = '+';   //mark it as discovered
    
    while (!coordStack.empty())
    {
        Coord popped = coordStack.top();
        cerr << popped.r() << "," << popped.c() << endl;
        coordStack.pop();
        if (popped.r() == er  &&  popped.c() == ec) //if end point, return true
        {
            return true;
        }
        
        if (maze[popped.r()-1][popped.c()] == '.')  //if NORTH is undiscovered and open
        {
            maze[popped.r()-1][popped.c()] = '+';
            coordStack.push(Coord(popped.r()-1, popped.c()));
        }
        
        if (maze[popped.r()][popped.c()+1] == '.')  //if EAST is undiscovered and open
        {
            maze[popped.r()][popped.c()+1] = '+';
            coordStack.push(Coord(popped.r(), popped.c()+1));
        }

        if (maze[popped.r()+1][popped.c()] == '.')   //if SOUTH is undiscovered and open
        {
            maze[popped.r()+1][popped.c()] = '+';
            coordStack.push(Coord(popped.r()+1, popped.c()));
        }
        if (maze[popped.r()][popped.c()-1] == '.') //if WEST is undiscovered and open
        {
            maze[popped.r()][popped.c()-1] = '+';
            coordStack.push(Coord(popped.r(), popped.c()-1));
        }

    }
    return false;
}



int main()
{
    
    char maze[10][10] = {
//     r  c   0   1   2   3   4   5   6   7   8   9
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','X','.','.','.','.','X','X','X'},
        { 'X','.','X','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    if (pathExists(maze, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
}
 
