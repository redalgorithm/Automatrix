//
//  main.cpp
//  8
//
//  Created by Shaaxan on 3/7/19.
//  Copyright (c) 2019 Shaanan. All rights reserved.
//
/*
 
 01 00 00 00 00 00 00 00
 00 00 00 00 00 00 00 00
 00 00 00 00 00 00 00 00
 00 00 00 00 00 00 00 00
 00 00 02 00 00 00 00 00
 00 00 00 00 00 00 00 00
 00 00 00 00 00 00 00 00
 00 00 00 00 00 00 00 00
 
 \
 -1, -1
 +1, +1
 /
 -1, +1
 +1, -1
 
 */

#include <iostream>
using namespace std;

const int d = 8;
int startx = 0, starty = 0;
int x = 0, y = 0;
int counting = 0;

void query(int r, int& x, int& y)
{
    r = rand() % 8;
    x = r;
    r = rand() % 8;
    y = r;
}

void prewind(int& xx, int& yy)
{
    while(xx > -1 || yy > -1)
    {
        if(xx > -1)
        {
            xx--;
        }
        if(yy > -1)
        {
            yy--;
        }
    }
    xx++;
    yy++;
}

void dwind1(int& xx, int& yy)
{
    while(xx > -1 && yy > -1)
    {
        xx--;
        yy--;
    }
    xx++;
    yy++;
}

void dwind2(int& xx, int& yy)
{
    while(xx > -1 && yy < 8)
    {
        xx--;
        yy++;
    }
    xx++;
    yy--;
}

void queenIntersection(int board[d][d], int& xx, int& yy)
{
    // set
    xx = x;
    yy = y;
    
    // PERPENDICULAR INTERSECTION REWIND (+)
    prewind(xx, yy);
    
    // PERPENDICULAR INTERSECTION NEGATE
    while(xx < 8 || yy < 8)
    {
        if(board[xx][y] > 0 || board[xx][y] < 0)
        {
            xx++;
        }
        else if(board[x][yy] > 0 || board[x][yy] < 0)
        {
            yy++;
        }
        else
        {
            if(xx < 8)
            {
                board[xx][y] = -1;
                counting++;
                xx++;
            }
            if(yy < 8)
            {
                board[x][yy] = -1;
                counting++;
                yy++;
            }
        }
        
    }
    
    // reset
    xx = x;
    yy = y;
    
    // DIAGNOL INTERSECTION REWIND (\)
    dwind1(xx, yy);
    
    // DIAGNOL INTERSECTION NEGATE
    while(xx < 8 && yy < 8)
    {
        if(board[xx][yy] > 0 || board[xx][yy] < 0)
        {
            xx++;
            yy++;
        }
        else if(xx < 8 && yy < 8)
        {
            board[xx][yy] = -1;
            counting++;
            xx++;
            yy++;
        }
    }
    
    // reset
    xx = x;
    yy = y;
    
    // DIAGNOL INTERSECTION REWIND (/)
    dwind2(xx, yy);
    
    // DIAGNOL INTERSECTION NEGATE
    while(xx < 8 && yy > -1)
    {
        if(board[xx][yy] > 0 || board[xx][yy] < 0)
        {
            xx++;
            yy--;
        }
        else if(xx < 8 && yy > -1)
        {
            board[xx][yy] = -1;
            counting++;
            xx++;
            yy--;
        }
    }
}

void initBoard(int matrix[d][d])
{
    for(int y=0; y<d; y++)
    {
        for(int x=0; x<d; x++)
        {
            matrix[x][y] = 0;
        }
    }
}

void printBoard(int matrix[d][d])
{
    for(int y=0; y<d; y++)
    {
        for(int x=0; x<d; x++)
        {
            cout << "[";
            if(matrix[x][y] < 10)
            {
                if(matrix[x][y] > -1)
                    cout << "0";
            }
            cout << matrix[x][y] << "] ";
        }
        cout << endl;
    }
}

int main()
{
    // BOARD PROCEDURES
    int board[d][d];
    
    // ADDITIONAL VARIABLES
    int trial = 0;
    int queen = 1;
    int xx, yy;
    
    // PREP FOR RANDOMIZATION
    int r = 0;
    srand(time(NULL));
    
    while(queen < 9)
    {
        initBoard(board);
        
        queen = 1;
        xx = 0;
        yy = 0;
        counting = 0;
        trial++;
        cout << "Trial #" << trial << endl << endl;
        
        // SET START POSITION
        r = rand() % 8;
        startx = r;
        r = rand() % 8;
        starty = r;
        
        x = startx;
        y = starty;
        
        // INITIAL QUEEN PLACEMENT
        board[x][y] = queen;
        counting++;
        queen++;
        queenIntersection(board, xx, yy);   // negate striking zones
        
        while(counting < 64)
        {
            // FIND FREE SPACE
            while(board[x][y] < 0 || board[x][y] > 0)
            {
                query(r, x, y);
            }
            
            // PLACE QUEEN
            board[x][y] = queen;
            counting++;
            queen++;
            queenIntersection(board, xx, yy);
        }
        
        if(queen < 9)
        {
            cout << "Failed at " << queen-1 << " queens" << endl;
            cout << "Spaces left: " << 64-counting << endl << endl;
            printBoard(board);
            cout << "Trying again" << endl;
        }
        else
        {
            cout << "**************SUCCESS!**************" << endl;
            printBoard(board);
            cout << "************************************" << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}
