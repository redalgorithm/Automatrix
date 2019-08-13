//
//  main.cpp
//  KTour
//
//  Created by Shaanan Curtis on 2/5/19.
//  Copyright © 2019 Shaanan. All rights reserved.
//

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

int main()
{
    const int d = 8;
    int matrix[d][d];
    int horizontal[d] = {2,1,-1,-2,-2,-1,1,2};
    int vertical[d] = {-1,-2,-2,-1,1,2,2,1};
    int count=0;
    const int sx=0, sy=0;
    int orix=0,oriy=0,x=0,y=0,r=0,i=0;
    
    initMatrix(matrix, d);
    
    //SEED RANDOM NUMBER GENERATOR
    srand(time(NULL));
    int trial = 1;
    //int tempx=0, tempy=0;
    
    // TEST #1
    // MAKE SURE IT CAN ACTUALLY MAKE A SUCCESSFUL ATTEMPT
    // RESULT: IT WORKS
    
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
        if(count > 64)
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
    
    /*
    // TEST #2
    // NOW DO WHAT THIS PROGRAM WAS MEANT FOR
    // FIRST TRY WHAT WAS THE RESULT?
    // comment this out when done testing
    int firsttry = 0;
    while(firsttry < 1)
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
        firsttry++;
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
