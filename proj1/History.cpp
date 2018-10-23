//
//  history.cpp
//  proj1
//
//  Created by 杨子鸣 on 4/9/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include "History.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 1; r <= nRows; r++)
        for (int c = 1; c <= nCols; c++)
            m_gridOfHistory[r-1][c-1] = '0';
}

bool History::record(int r, int c)
{
    if (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols)
    {
        char& HisGrid = m_gridOfHistory[r-1][c-1];
        switch (HisGrid)
        {
            case '0':
                HisGrid = 'A';
                cerr << "A position is assigned to A!"<<endl;
                cerr << "The corresponding position now is " << m_gridOfHistory[r-1][c-1] << endl;
                break;
            case 'Z':
                cerr << "The position is already Z!"<<endl;
                cerr << "The corresponding position now is " << m_gridOfHistory[r-1][c-1] << endl;
                break;
            default:
                cerr << "This position has been stepped once more" << endl;
                HisGrid++;
                cerr << "The corresponding position now is " << m_gridOfHistory[r-1][c-1] << endl;
        }
        return true;
    }
    else
        return false;
}

void History::display() const
{
        char displayHistory[MAXROWS][MAXCOLS];
        int r, c;
        
        // Fill displayGrid with dots (empty) and letters (times of record)
        for (r = 1; r <= m_rows; r++)
            for (c = 1; c <= m_cols; c++)
            {
                if (m_gridOfHistory[r-1][c-1] == '0')
                {
                    displayHistory[r-1][c-1] = '.';
                }
                else
                {
                    displayHistory[r-1][c-1] = m_gridOfHistory[r-1][c-1];
                }
            }
    
        clearScreen();
        for (r = 1; r <= m_rows; r++)
        {
            for (c = 1; c <= m_cols; c++)
                cout << displayHistory[r-1][c-1];
            cout << endl;
        }
        cout << endl;

}