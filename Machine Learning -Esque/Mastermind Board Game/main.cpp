
//  mastermind.cpp
//  Created by Shaanan Curtis on 4/1/19.
//  Copyright © 2019 Shaanan Curtis. All rights reserved.

/*
    OVERVIEW of MASTERMIND PROGRAM:
 
    Mastermind is a code-breaking game for two players.
    Each guess is made by placing a row of code pegs (pins) on the decoding board. Once placed, the
    codemaker provides feedback by placing from one to N key pegs (pegs) in the small holes of the row
    with the guess. A colored or black peg (1) is placed for each pin from the guess which is correct in
    both color and position. A white peg (0) is placed for each pin from the guess which is the correct
    color but found in a different position. All guesses for which a peg is left empty (-1) is considered
    completely incorrect.
 
    This program represents a virtual game of mastermind using the XCode IDE in C++.
    It also reveals the process in the design and implementation of this program.
    Throughout the program, you may notice an array of test cases which are
    commented out and labeled for better readability.  I have attempted to
    increase reliability by incorporating exception handling and preventing leaks
    in memory.
*/

#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <string>
//#include <cstring>
//#include <cstdlib>
using namespace std;

// GLOBAL VARIABLES
const int MAX_HUES = 10;     //total hues available in game
int GAMES = 0;               //max guesses
int user = 0;                //reusable user input
bool flag = 0;               //reusable status flag

// FUNCTIONS

//(1)
// -----------------------------------------------------------
// startMenu()
//
// prints multiple lines of string
// representing the initial start menu
// for the user to interact with via
// the console.
//
// Parameters: NA
// Return: Void
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void startMenu()
{
    cout << "WELCOME TO MASTERMIND\n\n";
    cout << "1: Start Game\n";
    cout << "2: Info\n";
    cout << "3: Exit\n";
    cout << "--------------------------------------------\n";
    cout << "-> ";
    cin >> user;
    cout << "--------------------------------------------\n";
    
    //-------------------------------
    // switch statement summary
    //
    // case 1: start game
    // case 2: print info to console
    // default: do nothing and exit
    //-------------------------------
    switch(user)
    {
        case 1:
            flag = 1;
            break;
        case 2:
            cout << "INFO\n"
            << "This version contains an assortment of 10 total hues to choose from.\n"
            << "The object of the game is to guess the order of hues used in the solution.\n"
            << "The guesses are validated against the solution and pegs are returned with\n"
            << "the solution.  [B] pegs mean there is a pin in the correct order.\n"
            << "[W] pegs mean there is a pin according to the same color in the solution.\n"
            << "Empty pegs mean the pin is incorrect.\n"
            << "The codemaker wins points per guess.  If none of the guesses are correct,\n"
            << "the codemaker wins the number of guesses plus a bonus point.\n"
            << "There may not be more than one pin of the same color in a guess/solution.\n\n";
            cout << "Ready to start?\n";
            cout << "1: Yes\n";
            cout << "2: No, Exit\n";
            cout << "--------------------------------------------\n";
            cout << "-> ";
            cin >> user;
            cout << "--------------------------------------------\n";
            if(user == 1)
                flag = 1;
            break;
    }
    
    //-------------------------------
    // if statement summary
    //
    // case start: display animation
    // default: exit program
    //-------------------------------
    if(flag)
    {
        // simulate startup delay
        cout << endl;
        cout << "Game starting";
        sleep(1);
        cout << ".";
        sleep(1);
        cout << ".";
        sleep(1);
        cout << ".";
        sleep(1);
        cout << endl << endl;
        
        // reset status flag
        flag = 0;
    }
    else
    {
        cout << "Goodbye...\n";
        exit(1);
    }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// -----------------------------------------------------------

//(2)
// -------------------------------------------------------------
// setup()
//
// allows user to modify in-game settings
// and interact via the console.
//
// Parameters: int&, int&, bool&, bool&
// Return: Void
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void setup(int& game_hues, int& pins, bool& unique, bool& CPU)
{
    // repeat initial setup on invalid input
    do{
        //---------------------------------
        // if statement summary
        //
        // case error: print appropriate
        // message and set default values
        // if errors present
        // default: display setup header
        //----------------------------------
        if(flag)
        {
            if(game_hues<1 || pins<1)
            {
                cout << "\"CANNOT PLAY GAME WITHOUT PINS\"\n";
            }
            else if(pins > game_hues)
            {
                cout << "\"PINS MUST BE UNIQUE\"\n"
                << "\"number of available colors must be >= number of pins\"\n\n";
            }
            else
            {
                cout << "\"REACHED MAX HUES\"\n";
            }
            
            cout << "Setting to Default";
            sleep(1);
            cout << ". ";
            sleep(1);
            cout << ". ";
            sleep(1);
            cout << ".\n";
            game_hues = 6;
            pins = 4;
            
            // display changes made and break from loop
            cout << "colors = 6\n";
            cout << "pins = 4\n";
            break;
        }
        else
        {
            cout << "********************************************\n"
                 << setw(30) << "INITIAL SET UP\n"
                 << "********************************************\n";
        }
        
        // Settings - unique pins (repeat until valid)
        do{
            cout << "Play with unique pins?\n"
            << "1. Yes\n"
            << "2. No\n"
            << "3. ?\n\n";
            cout << "--------------------------------------------\n";
            cout << "-> ";
            cin >> user;
            cout << "--------------------------------------------\n";
            
            switch(user)
            {
                case 1: unique = true;
                    break;
                case 2: unique = false;
                    break;
                default:
                         cout << "?:\n\n" << "If yes, pins must be colored differently.\n";
                         cout << "--------------------------------------------\n";
            }
        }while(user!=1 && user!=2);
        
        // Settings - solution master (repeat until valid)
        do{
            cout << "Solution Master:\n"
            << "1. CPU\n"
            << "2. Player 1\n"
            << "3. ?\n\n";
            cout << "--------------------------------------------\n";
            cout << "-> ";
            cin >> user;
            cout << "--------------------------------------------\n";
            
            switch(user)
            {
                case 1: CPU = true;
                    break;
                case 2: CPU = false;
                    break;
                default:
                    cout << "?:\n\n" << "Choose who sets the solution.\n";
                    cout << "--------------------------------------------\n";
            }
        }while(user!=1 && user!=2);
        
        // Settings - general
        cout << endl;
        
        //
        cout << "Number of guesses (default 12): ";
        cin >> user;
        GAMES = user;
        
        cout << "Number of colors made available (max 10): ";
        cin >> user;
        game_hues = user;
        
        cout << "Number of pins in guess/solution";
        if(unique)
            cout << " (max 10): ";
        else
            cout << ": ";
        cin >> user;
        pins = user;
        
        cout << endl;
        
        // setup was initialized once
        flag = 1;
    }while(game_hues > MAX_HUES || (unique && pins>MAX_HUES) || (unique && pins>game_hues) || game_hues<1 || pins<1);
    
    // set number of guesses to default in bkg if invalid
    if(GAMES < 1)
        GAMES = 12;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// -------------------------------------------------------------

//(3)
// ---------------------------------------
// initLegend()
//
// initializes an array of strings with
// a range of colors
// (assortment based on MAX_HUES)
//
// Parameters: string*
// Return: Void
// - - - - - - - - - - - - - - - - - - - -
void initLegend(string* legend)
{
    legend[0] = "RED";
    legend[1] = "ORANGE";
    legend[2] = "YELLOW";
    legend[3] = "GREEN";
    legend[4] = "BLUE";
    legend[5] = "PURPLE";
    legend[6] = "PINK";
    legend[7] = "BROWN";
    legend[8] = "WHITE";
    legend[9] = "BLACK";
}
// - - - - - - - - - - - - - - - - - - - -
// ---------------------------------------

//(4)
// -----------------------------------------------
// setColors()
//
// initializes an array of colors to choose
// from and sets available colors according
// to a number specified by the user
//
// Parameters: string*, int
// Return: Void
// - - - - - - - - - - - - - - - - - - - - - - - -
void setColors(string* colors, int game_hues)
{
    // initialize legend
    string legend[MAX_HUES];
    initLegend(legend);
    
    // map appropriate number of colors to legend
    for(int i=0; i<game_hues; i++)
    {
        colors[i] = legend[i];
    }
}
// - - - - - - - - - - - - - - - - - - - - - - - -
// -----------------------------------------------

//(5)
// -----------------------------------------------------------------
// CPUset()
//
// automatically generates a solution using
// random numbers to indicate the
// relative index associated with an array
// of available colors
//
// Parameters: int*, int, int, bool
// Return: Void
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CPUset(int* solution, int pins, int game_hues, bool unique)
{
    // initialize random number and counter vars
    int r = -1, count1 = 0;
    
    // initialize solution array with -1s (init empty solution)
    for(count1=0; count1<pins; count1++)
    {
        solution[count1] = -1;
    }
    
    // initialize array of reserved indices representing hue availability
    bool chosen[game_hues];
    for(int i=0; i<game_hues; i++)
    {
        chosen[i] = 0;
    }
    
    // automatically generate a solution
    count1 = 0;
    while(count1 < pins)
    {
        //---------------------------------------------
        // if statement summary
        //
        // case unique: ensure solution contains a
        // unique assortment of colored pins
        // default: solution is determined arbitrarily
        //---------------------------------------------
        if(unique)
        {
            r = rand() % game_hues;
            while(chosen[r] == 1)
            {
                r = rand() % game_hues;
            }
        }
        else
        {
            r = rand() % game_hues;
        }
        
        solution[count1] = r;   //set solution at current index
        chosen[r] = 1;          //set index to occupied
        count1++;               //next pin
    }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// -----------------------------------------------------------------

//(6)
// ---------------------------------------------------------------------------------
// PLAYERset()
//
// prompts user to manually enter a solution using
// a legend of available colors
//
// Parameters: int*, int, int, bool
// Return: Void
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void PLAYERset(int* solution, string* colors, int pins, int game_hues, bool unique)
{
    cout << "--------------------------------------------\n";
    cout << "Please set the solution.\n\n";
    cout << "Pins: " << pins << endl;
    cout << "Colors Available:\n";
    
    // case conversion and print colors by index
    for(int i=0; i<game_hues; i++)
    {
        int j=1;
        string temp = colors[i];
        
        while(temp[j])
        {
            temp[j] = tolower(temp[j]);
            j++;
        }
        cout << i+1 << ": " << temp << endl;
    }
    cout << endl;
    
    // initialize array of reserved indices representing hue availability
    // purpose: compatibility with unique pin option
    bool chosen[game_hues];
    for(int i=0; i<game_hues; i++)
    {
        chosen[i] = 0;
    }
    
    // player sets solution
    for(int i=0; i<pins; i++)
    {
        cout << "Pin #" << i+1 << " (Enter digit): ";
        cin >> user;
        
        // user input error checking
        if(user < 1 || user > game_hues || (unique && chosen[user-1]==true))
        {
            if(chosen[user-1] == true)
            {
                cout << "--------------------------------------------\n";
                cout << "INVALID INPUT: Pins must be uniquely placed.\n";
                cout << "--------------------------------------------\n";
            }
            else
            {
                cout << "--------------------------------------------\n";
                cout << "INVALID INPUT: Please refer to color index.\n";
                cout << "--------------------------------------------\n";
            }
            
            i--;    //decrement for retrial
        }
        else
        {
            solution[i] = user-1;   //set as valid guess
            chosen[user-1] = 1;     //set index to occupied
        }
        
    }
    cout << endl;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ---------------------------------------------------------------------------------

//(7)
// ---------------------------------------------------------------------------------------------
// setSolution()
//
// determines whether user or CPU was designated
// to set the solution and calls the appropriate
// function
//
// Parameters: int*, string*, int, int, bool, bool
// Return: Void
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void setSolution(int* solution, string* colors, int pins, int game_hues, bool unique, bool CPU)
{
    if(CPU)
        CPUset(solution, pins, game_hues, unique);
    else
        PLAYERset(solution, colors, pins, game_hues, unique);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ---------------------------------------------------------------------------------------------

// MAIN PROGRAM
int main()
{
    // initialize primary local vars
    bool unique = false;            //unique colors
    bool CPU = false;               //CPU sets solution
    int pins = 0, game_hues = 0;    //pins in solution, available hues in-game
    
    // declare primary local arrays
    string* colors;                 //contains names of colors
    string* pegs;                   //for validation of guess
    int* solution;                  //contains solution
    int* guess;                     //contains guess
    
    // initialize peripheral local vars
    int rand_color = 0;             //random number var
    srand(time(NULL));              //seed random number generator
    int correct = 0;                //represents number of pins guessed correctly (color and position)
    // Game Play -----------------------------------------------------|
    
    // initial setup
    startMenu();                               //display start menu
    setup(game_hues, pins, unique, CPU);       //configuration
    
    // set colors
    colors = new string[game_hues];
    setColors(colors, game_hues);
    
    // set solution
    solution = new int[pins];
    setSolution(solution, colors, pins, game_hues, unique, CPU);
    
    pegs = new string[pins];                   //allocate pegs to memory
    guess = new int[pins];                     //allocate guess to memory
    
    // declare and initialize arrays with "null" values
    int previous[pins];                        //holds previous guess
    for(int i=0; i<pins; i++)
    {
        previous[i] = -1;
        guess[i] = -11;
    }
    
    // start game title
    cout << "********************************************\n";
    cout << setw(29) << "GAME START\n\n";
    
    // guess and validate solution
    int n = 1;                      //iterates guess numbers
    const int N = GAMES + 1;        //max guesses
    do
    {
        //----------------------------------------------
        // if statement summary
        //
        // case CPU set solution: user guesses solution
        // default: CPU guesses solution
        //----------------------------------------------
        if(CPU)
        {
            cout << "Pins: " << pins << endl;
            cout << "Color Index:\n";
            
            // case conversion and print colors by index
            for(int i=0; i<game_hues; i++)
            {
                int j=1;
                string temp = colors[i];
                
                while(temp[j])
                {
                    temp[j] = tolower(temp[j]);
                    j++;
                }
                cout << i+1 << ": " << temp << endl;
            }
            cout << endl;
            
            cout << "ROW " << n << "/" << N-1 << endl;      //display row number
            
            // user guesses pins
            for(int i=0; i<pins; i++)
            {
                cout << "Pin #" << i+1 << " (Enter digit): ";
                cin >> user;
                
                //--------------------------------------------
                // if statement summary
                //
                // case error: display error message
                // default: set as valid guess
                //--------------------------------------------
                if(user < 1 || user > game_hues)
                {
                    cout << "--------------------------------------------\n";
                    cout << "INVALID INPUT: Please refer to color index." << endl;
                    cout << "--------------------------------------------\n";
                    i--;    // retry
                }
                else
                    guess[i] = user-1;
            }
        }
        else
        {
            // initialize array of reserved indices representing hue availability
            // purpose: compatibility with unique pin option
            bool chosen[game_hues];
            for(int i=0; i<game_hues; i++)
            {
                chosen[i] = 0;
            }
            
            cout << "ROW " << n << "/" << N-1 << endl;      //display row number
            
            // CPU guesses pins
            cout << "CPU chose: ";
            for(int i=0; i<pins; i++)
            {
                //---------------------------------------------
                // if statement summary
                //
                // case unique: ensure solution contains a
                // unique assortment of colored pins
                // default: solution is determined arbitrarily
                //---------------------------------------------
                if(unique)
                {
                    rand_color = rand() % game_hues;
                    while(chosen[rand_color] == true)
                    {
                        rand_color = rand() % game_hues;
                    }
                }
                else
                {
                    rand_color = rand() % game_hues;
                }
                
                //------------------------------------------------
                // if statement summary
                //
                // case 1+ guessed correctly: set guess to
                // assumedly correct pin
                // default: make a different guess
                //
                // note: CPU is unaware of correctly guessed pins
                //------------------------------------------------
                if(correct > 0)
                {
                    guess[i] = previous[i];
                    correct--;
                }
                else
                {
                    //------------------------------------------
                    // if statement summary
                    //
                    // case chosen pin is same: ensure guess is
                    // set differently
                    // default: set guess
                    //------------------------------------------
                    if(rand_color == previous[i] && i+1 < pins)
                        guess[i] = previous[i+1];
                    else
                        guess[i] = rand_color;
                }
                
                previous[i] = guess[i];     //save guess into history
                chosen[guess[i]] = 1;       //set pin position as occupied
                
                // map guess to corresponding color and print converted string
                int j = 1;
                string temp = colors[guess[i]];
                while(temp[j])
                {
                    temp[j] = tolower(temp[j]);
                    j++;
                }
                
                cout << temp << " ";
                sleep(1);
            }
        }
        cout << endl;
        
        int count = 0;      //add an additional counter for thorough check
        correct = 0;        //reset number of correctly guessed pins
        
        //----------------------------------------------
        // if statement summary
        //
        // case CPU set solution: CPU validates guess
        // default: user validates guess
        //----------------------------------------------
        if(CPU)
        {
            // validate guess against solution
            // assign result to guess position
            while(count < pins)
            {
                flag = false;                   //reset flag
                for(int i=0; i<pins; i++)
                {
                    //----------------------------------------------
                    // if statement summary
                    //
                    // case pin match: check if correct position
                    // default: do nothing
                    //----------------------------------------------
                    if(guess[count] == solution[i])
                    {
                        flag = true;            //set flag
                        
                        //----------------------------------------------
                        // if statement summary
                        //
                        // case position match: set as black peg
                        // default: set as white peg
                        //----------------------------------------------
                        if(count == i)
                        {
                            correct++;          //increment number correctly guessed
                            guess[count] = 1;   //black peg
                        }
                        else
                        {
                            guess[count] = 0;   //white peg
                        }
                        
                        // problem with break if nonunique ([W] overwrites [B])
                        // if color already matched, treat remaining matches as significant
                        // if already correct position, break to avoid [W] on [B]
                        //------------------------------------------------------------------
                        // if statement summary
                        //
                        // case unique:
                        //      correct: break loop to avoid [W] overwrite [B]
                        // default: do nothing
                        //------------------------------------------------------------------
                        if(unique || guess[count] == 1)
                            break;
                    }
                }
                //----------------------------------------------------------
                // if statement summary
                //
                // case !flag: mark peg position empty
                // default: do nothing
                //----------------------------------------------------------
                if(!flag)
                {
                    guess[count] = -1;
                }
                count++;    //increment to next peg
            }
        }
        else
        {
            cout << endl;
            cout << "--------------------------------------------\n\n";
            cout << "Please validate CPU's guess.\n\n";
            cout << "[B] = 1, [W] = 0, [ ] = -1\n";
            
            // user validates CPU's guess
            for(int i=0; i<pins; i++)
            {
                do{
                    cout << "Peg #" << i+1 << ": ";
                    cin >> user;
                }while(user < -1 || user > 1);
                
                if(user == 1)
                    correct++;      //increment number of correctly guessed pins
                
                guess[i] = user;
            }
        }
        
        
        //------------------------------------------------------------------
        // if statement summary
        //
        // case all correct: display appropriate message
        // default: print line break
        //------------------------------------------------------------------
        if(correct == pins)
        {
            cout << "********************************************\n\n";
            if(CPU)
                cout << setw(39) << "CONGRATULATIONS: YOU WON!!!!\n\n\n";
            else
                cout << setw(29) << "CPU WON\n\n\n";
            user = -444;    //set user to distinct integer for authentication
            n=12;
        }
        else
            cout << "\n--------------------------------------------\n";
        
        // initialize array of reserved indices representing hue availability
        // embedding display pegs
        bool chosen[pins];
        cout << "Pegs: ";
        for(int i=0; i<pins; i++)
        {
            switch(guess[i])
            {
                case 1: pegs[i] = "[B] ";
                    break;
                case 0: pegs[i] = "[W] ";
                    break;
                default:    pegs[i] = "[ ] ";
            }
            chosen[i] = 0;
        }
        
        // randomize peg output
        count = 0;
        while(count < pins)
        {
            rand_color = rand() % pins;
            while(chosen[rand_color] == true)
            {
                rand_color = rand() % pins;
            }
            cout << pegs[rand_color];
            sleep(1);
            count++;
            chosen[rand_color] = true;
        }
        
        cout << endl << endl;
        n++;
    }while(n < N);      //loop up to max guesses >>
    
    // display solution and pegs
    cout << "Solution: ";
    for(int i=0; i<pins; i++)
    {
        cout << colors[solution[i]] << " ";
    }
    cout << endl << endl;
    
    //------------------------------------------------------
    // if statement summary
    //
    // case not winner: display appropriate message
    // default: do nothing
    //------------------------------------------------------
    if(user != -444)
    {
        if(CPU)
            cout << setw(34) << "BETTER LUCK NEXT TIME!\n";
        else
            cout << setw(27) << "CPU LOST\n";
    }
    
    // deallocation (memory leak solution)
    delete[] colors;
    delete[] solution;
    delete[] guess;
    delete[] pegs;
    
    return 0;
}
