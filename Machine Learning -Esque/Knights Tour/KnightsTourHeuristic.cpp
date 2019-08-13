//
//  main.cpp
//  KTourHeuro
//
//  Created by Shaanan on 2/7/19.
//  Copyright © 2019 Shaanan. All rights reserved.
// decrement all possible moves from original position by 1 from accessility pov after move

#include <iostream>
using namespace std;

void initMatrix(int matrix[8][8], const int d)
{
    //INITIALIZE matrix WITH 0s
    for(int y=0; y<d; y++)
    {
        for(int x=0; x<d; x++)
        {
            matrix[x][y]=0;
        }
    }
}

void initAccessibility(int legend[8][8], const int d)
{
    //INIT LEGEND (heuristic)
    for(int y=0; y<d; y++)
    {
        for(int x=0; x<d; x++)
        {
            if(x>1 && x<6 && y>1 && y<6)
            {
                legend[x][y] = 8;
            }
            else if((x>1 && x<6 && (y==1 || y==6)) || (y>1 && y<6 && (x==1 || x==6)))
            {
                legend[x][y] = 6;
            }
            else if(((x==1 || x==6) && (y==0 || y==7)) || ((y==1 || y==6) && (x==0 || x==7)))
            {
                legend[x][y] = 3;
            }
            else if((x==0 || x==7) && (y==0 || y==7))
            {
                legend[x][y] = 2;
            }
            else
            {
                legend[x][y] = 4;
            }
        }
    }
}

int main()
{
    int r=0;
    srand(time(NULL));
    
    int trial=1;
    
    // THE BOARD
    const int d = 8;                            // dimensions
    int matrix[d][d];                           // board
    int accessibility[d][d];                    // heuristic

    // MOVEMENT
    const int horizontal[d] = {2,1,-1,-2,-2,-1,1,2};  // horizontal movement
    const int vertical[d] = {-1,-2,-2,-1,1,2,2,1};    // vertical movement
    
    // INITIAL START
    const int sx=0, sy=0;                             // init starting point
    int count=1;                                      // init count
    int orix=0, oriy=0, x=0, y=0, tx=0, ty=0;         // init x y vals
    
    // COUNTERS
    int i=0;
    int j=0;
    
    // INITIALIZE BOARDS
    initMatrix(matrix, d);
    initAccessibility(accessibility, d);
    
    // SET START
    matrix[sx][sy] = count;
    count++;
    
    // REMEMBER PREVIOUS COORDINATES
    orix = sx;
    oriy = sy;
    
    // DEFINE FLAGS
    bool taken = false;         // position is taken
    bool gameover = false;      // no more moves available
    while(count<65)
    {
        cout << "Trial " << trial++ << endl;

        taken=false;
        gameover=false;
        count = 1;
        orix = sx;
        oriy = sy;
        initMatrix(matrix, d);
        matrix[sx][sy] = count;
        count++;
        i=0;
        j=0;
    // GAME START
    while(count<65)
    {
        // SET X & Y COORDINATES TO MOVE TO A POSITION
        x = orix + horizontal[i];
        y = oriy + vertical[i];
        i++;
        
        // POSITION IS TAKEN?
        if(matrix[x][y] != 0)
        {
            taken = true;
            //cout << "[" << x << ", " << y << "] Taken" << endl;
        }
        
        // POSITION NOT AVAILABLE: Out of bounds or taken
        while((x<0 || x>7 || y<0 || y>7) || taken==true)
        {
            // SEARCHED ALL MOVES AND FOUND NONE AVAILABLE? (Gameover)
            if(i==d)
            {
                gameover = true;
                break;
            }
            
            // TRY MOVING TO THIS POSITION
            x = orix + horizontal[i];
            y = oriy + vertical[i];
            //cout << "i: " << i << endl;
            i++;
            
            // IN BOUNDS BUT POSITION IS TAKEN?
            if((matrix[x][y]!=0) && !(x<0 || x>7 || y<0 || y>7))
            {
                taken=true;
                //cout << "[" << x << ", " << y << "] Taken" << endl;
            }
            else
            {
                taken=false;
            }
        }
        
        // NO MORE MOVES?
        if(gameover)
        {
            break;
        }
        
        // AVAILABLE POSITION WAS FOUND: COMPARE WITH REMAINING AVAILABILITIES FOR BEST DECISION
        //cout << "chose x,y: [" << x << "," << y << "]" << endl;
        j=i;
        while(j<d)
        {
            //cout << "orix: " << orix << " " << "oriy: " << oriy << endl;
            
            // SET TX AND TY COORDINATES TO NEXT MOVE POSITION
            tx = orix + horizontal[j];
            ty = oriy + vertical[j];
            j++;
            
            // POSITION NOT AVAILABLE: Out of bounds
            while(tx<0 || tx>7 || ty<0 || ty>7)
            {
                // REACHED END OF MOVES LIST: NO MORE AVAILABLE POSITIONS
                if(j==d)
                {
                    tx = x;
                    ty = y;
                    break;
                }
                
                // TRY MOVING TO THIS POSITION
                tx = orix + horizontal[j];
                ty = oriy + vertical[j];
                //cout << "j: " << j << endl;
                j++;
            }
            
            
            //cout << "chose tx,ty: [" << tx << "," << ty << "]" << endl;
            
            // SET X Y COORDINATES TO HIGHEST PRIORITY POSITION FOR EACH CHECK (lowest on accessibility)
            if(accessibility[x][y] > accessibility[tx][ty])
            {
                //cout << x << "," << y << " > " << tx << "," << ty << endl;
                //cout << accessibility[x][y] << " > " << accessibility[tx][ty] << endl;
                
                // SET X AND Y TO TX AND TY ONLY IF POSITION IS NOT TAKEN
                if(matrix[tx][ty]==0)
                {
                    x = tx;
                    y = ty;
                }
                else
                {
                    //cout << "[" << tx << ", " << ty << "] Taken2" << endl;
                }
            }
            else if(accessibility[x][y] < accessibility[tx][ty])
            {
                //cout << x << "," << y << " < " << tx << "," << ty << endl;
                //cout << accessibility[x][y] << " < " << accessibility[tx][ty] << endl;
            }
            else
            {
                if(matrix[tx][ty]==0)
                {
                    //cout << "ox: " << x << ", oy: " << y << ", otx: " << tx << ", oty: " << ty << endl;
                    
                    r = rand() % 2;
                    switch(r)
                    {
                        case 0: x=x; y=y;
                            break;
                        default: x=tx; y=ty;
                    }
                    //cout << "x: " << x << ", y: " << y << endl;
                }
            }
            
            // keep checking until the end of moves list for the highest priority position
         }
        
        //if(x<0 || x>7 || y<0 || y>7)
        //{
            //cout << "STALE MATE: Out of moves that are in bounds" << endl;
            //break;
        //}
        //else
        //{
            //if(matrix[x][y]==0)
            //{
        
         // SET BOARD TO NEW POSITION
         matrix[x][y] = count;
         count++;
         //cout << "moved to " << x << " " << y << endl;
        
         // ORIGINATE NEW COORDINATES
         orix = x;
         oriy = y;
        
            //}
            //else
            //{
                //cout << "STALE MATE:  Out of moves" << endl;
                //break;
            //}
        //}
        
         // seek surrounding positions
         i=0;
         while(i<d)
         {
             x = orix + horizontal[i];
             y = oriy + vertical[i];
             i++;
             while(x<0 || x>7 || y<0 || y>7)
             {
                 x = orix + horizontal[i];
                 y = oriy + vertical[i];
                 i++;
             }
             // one found, decrement accessibility by 1
             accessibility[x][y]--;
         }
        
         // RESET ITERATORS FOR MOVE ARRAYS
         i=0;
         j=0;
     }
    
    // RAN OUT OF MOVES?
    if(gameover)
    {
        //cout << "STALE MATE: Out of moves" << endl;
    }
        cout << "Count " << count << endl << endl;
    }
    // PRINT RESULT
    for(int y=0; y<d; y++)
    {
        for(int x=0; x<d; x++)
        {
            cout << "[";
            if(matrix[x][y] < 10)
            {
                cout << "0";
            }
            cout << matrix[x][y] << "] ";
        }
        cout << endl;
    }
    
    //cout << "Count: " << count << endl;
    // update x y as next count only if the position is not taken
    // if it is taken, set flag to true for a repetition discounting the taken position
    
    /*
    //SEED RANDOM NUMBER GENERATOR
    srand(time(NULL));
    int trial = 1;
    //int tempx=0, tempy=0;
    while(count < 65)
    {
        count = 1;
        orix=sx;
        oriy=sy;
        x=sx;
        y=sy;
        initMatrix(matrix, d);
        matrix[x][y] = count;
        count++;
        while(count < 65)
        {
            i=0;
            // while the position is not available, keep randomizing selection
            while(matrix[x][y] != 0)
            {
                r = rand()%8;
                x = orix+horizontal[r];
                y = oriy+vertical[r];
                // while position is out of bounds, keep randomizing selection
                while((x<0)||(x>7)||(y<0)||(y>7))
                {
                    r = rand()%8;
                    x = orix+horizontal[r];
                    y = oriy+vertical[r];
                }
                // broke out of loop so in bounds
                
                i++;
                if(i>49)
                {
                    break;
                }
            }
            // broke out of loop so found a position or stale mate
            // 100% positive nothing is available, break out and restart
            if(i>49)
            {
                cout << "Trial #" << trial << " STALE MATE" << endl;
                trial++;
                break;
            }
            
            // found a position, so set orix and oriy to newfound position
            orix = x;
            oriy = y;
            
            matrix[x][y] = count;
            count++;
        }
        // broke out of loop so either no available moves or successfully hit 64
        if(count > 63)
        {
            cout << "SUCCESS" << endl;
            break;
        }
    }
    
    cout << count-1 << " moves" << endl;
    for(int y=0; y<d; y++)
    {
        for(int x=0; x<d; x++)
        {
            cout << "[";
            if(matrix[x][y]<10)
            {
                cout << "0";
            }
            cout << matrix[x][y] << "] ";
        }
        cout << endl;
    }
    */
    return 0;
}

