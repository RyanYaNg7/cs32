//

//
//  Created by 杨子鸣 on 4/28/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//
//#include <iostream>
//using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    if (sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = '+';
    
    if (maze[sr+1][sc] == '.')
        if(pathExists(maze, sr+1, sc, er, ec))
            return true;
    
    if (maze[sr-1][sc] == '.')
        if(pathExists(maze, sr-1, sc, er, ec))
            return true;
    
    if (maze[sr][sc+1] == '.')
        if(pathExists(maze, sr, sc+1, er, ec))
            return true;
    
    if (maze[sr][sc-1] == '.')
        if(pathExists(maze, sr, sc-1, er, ec))
            return true;
    
    return false;
    
}



/*
 int main()
 {
 
 char maze[10][10] = {
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
 
 if (pathExists(maze, 1,8, 8,7))
 cout << "Solvable!" << endl;
 else
 cout << "Out of luck!" << endl;
 
 }

*/