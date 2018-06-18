//
//  maze.cpp
//  actualHW3
//
//  Created by Kaela Polnitz on 2/10/18.
//  Copyright © 2018 Kaela Polnitz. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


//DONE

/*

	If the start location is equal to the ending location, then we've
 solved the maze, so return true.
	Mark the start location as visted.
	For each of the four directions,
 If the location one step in that direction (from the start
 location) is unvisited,
 then call pathExists starting from that location (and
 ending at the same ending location as in the
 current call).
 If that returned true,
 then return true.
	Return false.

*/

//YOU DONT NECESSARILY NEED THE COORD CLASS
 bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = 'O';
    //mark it so that it is no longer a dot, shows that the path has been found
    //you want to keep looking at the next point(s)
    //east
    if(maze[sr][sc+1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
        //aMaze.push(Coord(r,c+1));
    }
    
    //south,
    if(maze[sr+1][sc] == '.')
    {

        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
        //aMaze.push(Coord(sr+1,sc));
    }
    //r+1,c
    
    //west
    if(maze[sr][sc-1] == '.')
    {

        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
        //aMaze.push(Coord(r,c-1));
    }
    //r, c-l
    
    //north
    if (maze[sr-1][sc] == '.')
    {

        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
        //aMaze.push(Coord(sr-1,sc));
    }
    
    return false;
}
/*
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
*/


