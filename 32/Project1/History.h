//
//  History.hpp
//  PROJ1AGAIN
//
//  Created by Kaela Polnitz on 1/14/18.
//  Copyright © 2018 Kaela Polnitz. All rights reserved.
//

#ifndef History_h
#define History_h

#include <stdio.h>
#include "globals.h"


class History
{
    //no more public members
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    //added
    int m_rows; //corresponding to the ones in the city
    int m_cols;
    //two dimensional grid, two dimensional array
    char m_display[MAXROWS][MAXCOLS];
    //it can draw up to max rows and max cols
};


#endif /* History_hpp */
