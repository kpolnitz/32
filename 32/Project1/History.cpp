//
//  History.cpp
//  PROJ1AGAIN
//
//  Created by Kaela Polnitz on 1/14/18.
//  Copyright © 2018 Kaela Polnitz. All rights reserved.
//
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;
#include "City.h"
#include "globals.h"
#include "History.h"


History::History(int nRows, int nCols){
    //initializes city object with nRows and nCols
    m_rows=nRows;
    m_cols=nCols;
    
   
        int a;
        int b;
    for (a = 0; a < m_rows; a++)
        {
     
            for (b = 0; b < m_cols; b++)
                m_display[a+1][b+1] = '@';
     
        }
    
    
}


bool History::record(int r, int c)
{
    //called to notify the History object that a Flatulan was preached to but was not converted at a grid point. The function returns false if row r, column c is not within the City; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the City (e.g., row 1, column 1 is the upper-left-most position).
    
    if ((r <= 0 || r > m_rows) || (c <= 0 || c > m_cols)) //if the number is negative or outside grid
        return false;
    //otherwise, go about normal business
    //how many times did you preach
    //flatulan preached to, didn't get converted
    
    //if the possibility of conversion is false, *ALL LETTERS*
    
    m_display[r][c] += 1;
    //cerr << "You looked at point (" << r << ", " << c << ")." << endl;
    //cerr << "You are printing " << m_display[r][c] << endl;
    
    return true;
}

void History::display() const {
    
    //clear the screen, display the history grid, and write an empty line after the history grid
    //does not display "Press.."
    
    clearScreen(); //from globals
    //display history grid
   
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
            if (m_display[i+1][j+1] == '@')
                cout << '.';
            else
                cout << m_display[i+1][j+1];
        cout << '\n';
        
    }
    
    //write empty line
    cout << '\n';
    
}
