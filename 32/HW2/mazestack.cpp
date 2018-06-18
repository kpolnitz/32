//
//  mazestack.cpp
//  HW3
//
//  Created by Kaela Polnitz on 2/2/18.
//  Copyright © 2018 Kaela Polnitz. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>
// we are using a stack of coordinates


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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    //sr and sc -- starting coordinates
    //er and ec -- ending coordinates
    //can't go diagonal
    //returns true if there is a path
    // X - wall, . - Walkway
    stack<Coord> aMaze;
    Coord starting(sr,sc);
    Coord ending(er,ec);
    aMaze.push(starting);
    maze[sr][sc] = 'O';
    int r;
    int c;
    Coord current(r,c);
    int i = 1;
    while (!aMaze.empty()) //out of moves
    {
        //keep adding to thes stack, analyze each point, and keep going until you get to the start
        Coord temp = aMaze.top(); //temp that looks at the coordinate
        r = temp.r();
        c = temp.c();
        /*
        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < nCols; j++)
            {
                
                cerr << maze[i][j];
                
                
            }
            cerr << endl;
        }
         */
        
        //cerr << "The coordinate is (" << r << ", " << c << "), iteration " << i << endl;
        i++;
        
        aMaze.pop();
        if(r == er && c == ec)
            return true;

        
        //east
        if(maze[r][c+1] == '.')
        {
            maze[r][c+1] = 'O';
            
            aMaze.push(Coord(r,c+1));
        }
        
        //south
        if(maze[r+1][c] == '.')
        {
            maze[r+1][c] = 'O';
            
            aMaze.push(Coord(r+1,c));
        }
        
        //west
        if(maze[r][c-1] == '.')
        {
            maze[r][c-1] = 'O';
            aMaze.push(Coord(r,c-1));
        }
       
        
        //north
        if (maze[r-1][c] == '.')
        {
            maze[r-1][c] = 'O'; //mark it so that it is no longer a dot, shows that the path has been found
            aMaze.push(Coord(r-1,c));
        }
        


            //r,c+1

        
            
    }
        //if it's the same one then the path exists!
    

    return false;
}



     int main()
     {
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
     }






// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
