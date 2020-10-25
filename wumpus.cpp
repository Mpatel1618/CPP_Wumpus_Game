/* ---------------------------------------------------------
wumpus.cpp

Author: Mayur Patel

Description of Program:
The Wumpus game originally made in basic is remade in C++
 -----------------------------------------------------------
*/

#include <iostream>   // use of cout and cin
#include <iomanip>    // use of setw
#include <cstdlib>    // use of random
#include <time.h>     // use of random to seed

using namespace std;

// global variables to keep track of user, arrow, and hazard locations
int userLocation,
    wumpusLocation,
    batLocationFirst,
    batLocationSecond,
    pitLocationFirst,
    pitLocationSecond,
    arrowLocation = -1,   // arrow location initialized to -1 so user starts with arrow
    caveMapping[20][3];   // 2d array to map out the caves

// function to map out the cave
// each row represents one cave and and the three columns are the adjacent caves
void mapCave () {
    caveMapping[0][0] = 2;
    caveMapping[0][1] = 5;
    caveMapping[0][2] = 8;
    
    caveMapping[1][0] = 1;
    caveMapping[1][1] = 3;
    caveMapping[1][2] = 10;
    
    caveMapping[2][0] = 2;
    caveMapping[2][1] = 4;
    caveMapping[2][2] = 12;
    
    caveMapping[3][0] = 3;
    caveMapping[3][1] = 5;
    caveMapping[3][2] = 14;
    
    caveMapping[4][0] = 1;
    caveMapping[4][1] = 4;
    caveMapping[4][2] = 6;
    
    caveMapping[5][0] = 5;
    caveMapping[5][1] = 7;
    caveMapping[5][2] = 15;
    
    caveMapping[6][0] = 6;
    caveMapping[6][1] = 8;
    caveMapping[6][2] = 17;
    
    caveMapping[7][0] = 1;
    caveMapping[7][1] = 7;
    caveMapping[7][2] = 9;
    
    caveMapping[8][0] = 8;
    caveMapping[8][1] = 10;
    caveMapping[8][2] = 18;
    
    caveMapping[9][0] = 2;
    caveMapping[9][1] = 9;
    caveMapping[9][2] = 11;
    
    caveMapping[10][0] = 10;
    caveMapping[10][1] = 12;
    caveMapping[10][2] = 19;
    
    caveMapping[11][0] = 3;
    caveMapping[11][1] = 11;
    caveMapping[11][2] = 13;
    
    caveMapping[12][0] = 12;
    caveMapping[12][1] = 14;
    caveMapping[12][2] = 20;
    
    caveMapping[13][0] = 4;
    caveMapping[13][1] = 13;
    caveMapping[13][2] = 15;
    
    caveMapping[14][0] = 6;
    caveMapping[14][1] = 14;
    caveMapping[14][2] = 16;
    
    caveMapping[15][0] = 15;
    caveMapping[15][1] = 17;
    caveMapping[15][2] = 20;
    
    caveMapping[16][0] = 7;
    caveMapping[16][1] = 16;
    caveMapping[16][2] = 18;
    
    caveMapping[17][0] = 9;
    caveMapping[17][1] = 17;
    caveMapping[17][2] = 19;
    
    caveMapping[18][0] = 11;
    caveMapping[18][1] = 18;
    caveMapping[18][2] = 20;
    
    caveMapping[19][0] = 13;
    caveMapping[19][1] = 16;
    caveMapping[19][2] = 19;
}

// function to initialize the locations of user and hazards with while loops to make sure one location is not the same as the other locations
void initializeLocations () {
    userLocation = (rand() % 20) + 1;           // sets location to any cave from 1-20
    wumpusLocation = (rand() % 20) + 1;         // sets location to any cave from 1-20
    while (wumpusLocation == userLocation) {
        wumpusLocation = (rand() % 20) + 1;     // sets location to any cave from 1-20
    }
    batLocationFirst = (rand() % 20) + 1;       // sets location to any cave from 1-20
    while (batLocationFirst == userLocation || batLocationFirst == wumpusLocation) {
        batLocationFirst = (rand() % 20) + 1;   // sets location to any cave from 1-20
    }
    batLocationSecond = (rand() % 20) + 1;      // sets location to any cave from 1-20
    while (batLocationSecond == batLocationFirst || batLocationSecond == userLocation || batLocationSecond == wumpusLocation) {
        batLocationSecond = (rand() % 20) + 1;  // sets location to any cave from 1-20
    }
    pitLocationFirst = (rand() % 20) + 1;       // sets location to any cave from 1-20
    while (pitLocationFirst == userLocation || pitLocationFirst == batLocationFirst || pitLocationFirst == batLocationSecond || pitLocationFirst == wumpusLocation) {
        pitLocationFirst = (rand() % 20) + 1;   // sets location to any cave from 1-20
    }
    pitLocationSecond = (rand() % 20) + 1;      // sets location to any cave from 1-20
    while (pitLocationSecond == userLocation || pitLocationSecond == pitLocationFirst || pitLocationSecond == batLocationFirst || pitLocationSecond == batLocationSecond || pitLocationSecond == wumpusLocation) {
        pitLocationSecond = (rand() % 20) + 1;  // sets location to any cave from 1-20
    }
}

// function to print the current locations of everything in the game for the purpose of cheating
void printCurrentLocations () {
    cout << "Cheating! Game elements are in the following rooms:\n"
         << "Player" << setw(8) << "Wumpus" << setw(7) << "Bats1" << setw(7) << "Bats2" << setw(6) << "Pit1"
         << setw(6) << "Pit2" << setw(8) << "Arrow\n"
         << setw(4) << userLocation << setw(8) << wumpusLocation << setw(7) << batLocationFirst
         << setw(7) << batLocationSecond << setw(7) << pitLocationFirst << setw(6) << pitLocationSecond
         << setw(7) << arrowLocation << endl << endl;
}

// function to reset the locations of everything in the game to users liking
void resetLocations () {
    cout << "(Remember arrow value of -1 means it is with the person.)\n"
         << "Enter the 7 room locations (1..20) for Player, Wumpus, Bats1, Bats2, Pit1,\n"
         << "Pit2, and arrow:\n";
    
    cin >> userLocation >> wumpusLocation >> batLocationFirst >> batLocationSecond >> pitLocationFirst >> pitLocationSecond >> arrowLocation;
    
    cout << endl;
}

// function to check the adjacent spots of the user to determine how close the user is to a certain hazard
void checkAdjacentSpots () {
    int i;
    
    // checks all three adjacent spots and prints according to what hazard is near
    for (i = 0; i < 3; ++i) {
        if (caveMapping[userLocation - 1][i] == wumpusLocation) {
            cout << "You smell a stench. ";
        }
        if (caveMapping[userLocation - 1][i] == pitLocationFirst || caveMapping[userLocation - 1][i] == pitLocationSecond) {
            cout << "You feel a draft. ";
        }
        if (caveMapping[userLocation - 1][i] == batLocationFirst || caveMapping[userLocation - 1][i] == batLocationSecond) {
            cout << "You hear rustling of bat wings. ";
        }
    }
}

// function to check the user's input and make sure that the place they want to move to is an adjacent spot to the user with parameters that take the user's desired location and move count
void checkValidLocation (int movement, int &i) {
    if (caveMapping[userLocation - 1][0] == movement || caveMapping[userLocation - 1][1] == movement || caveMapping[userLocation - 1][2] == movement) {
        userLocation = movement;     // conditions are met and user moves to desired spot
        // checks if spot has user's arrow and gives it back if it is by assigning arrowLocation to -1
        if (userLocation == arrowLocation) {
            arrowLocation = -1;
            cout << "Congratulations, you found the arrow and can once again shoot.\n";
        }
        ++i;   // move count increases by 1 if conditions are met
    }
    else {
        cout << "Error: Location is not adjacent.\n";   // prints if move is not valid
    }
}

// function to relocate wumpus to smallest adjacent cave by checking all adjacent spots and then assigning the location of wumpus to the smallest cave
void wumpusRelocation () {
    int min;
    
    min = caveMapping[wumpusLocation - 1][0];
    for (int i = 0; i < 3; ++i) {
        if (caveMapping[wumpusLocation - 1][i] < min) {
            min = caveMapping[wumpusLocation - 1][i];
        }
    }
    wumpusLocation = min;
}

// function to check what hazards the user ended up in
void checkCurrentHazards () {
    int holder;   // used to make sure when bats are relocated they do not ended up at previous spot
    
    if (userLocation == wumpusLocation && (userLocation % 2) == 1) {   // Wumpus is relocated if cave is uneven
        wumpusRelocation();
        
        cout << "You hear a slithering sound, as the\nWumpus slips away.\nWhew, that was close!\n";
    }
    else if (userLocation == wumpusLocation) {   // user is killed if user location and Wumpus locations match up
        cout << "You briefly feel a slimy tentacled arm\nas your neck is snapped.\nIt is over.\n"
             << "\nExiting Program...\n";
             exit(0);
    }
    else if (userLocation == batLocationFirst) {   // user is relocated if location is same as bats and then bats are relocated making sure its not the same as other hazard and user locations
        userLocation = (rand() % 20) + 1;   // sets location to any cave from 1-20
        while (userLocation == wumpusLocation || userLocation == batLocationFirst || userLocation == batLocationSecond || userLocation == pitLocationFirst || userLocation == pitLocationSecond) {
            userLocation = (rand() % 20) + 1;   // sets location to any cave from 1-20
        }
        cout << "Woah... you're flying!\nYou've just been transported by bats\nto room " << userLocation << endl;
        
        holder = batLocationFirst;
        batLocationFirst = (rand() % 20) + 1;   // sets location to any cave from 1-20
        while (batLocationFirst == holder || batLocationFirst == userLocation || batLocationFirst == wumpusLocation || batLocationFirst == batLocationSecond || batLocationFirst == pitLocationFirst || batLocationFirst == pitLocationSecond) {
            batLocationFirst = (rand() % 20) + 1;   // sets location to any cave from 1-20
        }
    }
    else if (userLocation == batLocationSecond) {   // user is relocated if location is same as bats and then bats are relocated making sure its not the same as other hazard and user locations
        userLocation = (rand() % 20) + 1;   // sets location to any cave from 1-20
        while (userLocation == wumpusLocation || userLocation == batLocationFirst || userLocation == batLocationSecond || userLocation == pitLocationFirst || userLocation == pitLocationSecond) {
            userLocation = (rand() % 20) + 1;   // sets location to any cave from 1-20
        }
        cout << "Woah... you're flying!\nYou've just been transported by bats\nto room " << userLocation << endl;
        
        holder = batLocationSecond;
        batLocationSecond = (rand() % 20) + 1;   // sets location to any cave from 1-20
        while (batLocationSecond == holder || batLocationSecond == userLocation || batLocationSecond == wumpusLocation || batLocationSecond == batLocationFirst || batLocationSecond == pitLocationFirst || batLocationSecond == pitLocationSecond) {
            batLocationSecond = (rand() % 20) + 1;   // sets location to any cave from 1-20
        }
    }
    else if (userLocation == pitLocationFirst || userLocation == pitLocationSecond) {   // if user location is the same as any pit location, they die and game ends
        cout << "Aaaaaaaaahhhhhh....\nYou fall into a pit and die.\n"
             << "\nExiting Program...\n";
        exit(0);
    }
}

// function to check if the arrow killed anyone after a normal shot
void checkArrowDeath () {
    if (arrowLocation == userLocation) {
        cout << "You just shot yourself.\nMaybe Darwin was right. You're\ndead.\n"
             << "\nExiting Program...\n";
        exit(0);
    }
    else if (arrowLocation == wumpusLocation) {
        cout << "Wumpus has just been pierced by\nyour deadly arrow!\nCongratulations on your victory, you\nawesome hunter.\n"
             << "\nExiting Program...\n";
        exit(0);
    }
}

// function to check if the ricochet killed anyone, either the user, Wumpus, or no one
void checkArrowDeathRicochet () {
    if (arrowLocation == userLocation) {
        cout << "You just shot yourself, and are dying.\nIt didn't take long, you're dead.\n"
             << "\nExiting Program...\n";
        exit(0);
    }
    else if (arrowLocation == wumpusLocation) {
        cout << "Your arrow ricochet killed the\nWumpus, you lucky dog!\nAccidental victory, but still you win!\n"
             << "\nExiting Program...\n";
        exit(0);
    }
}

// function to relocate arrow after ricocheting
// it checks all adjacent rooms and takes the smallest room and puts it in there
void arrowRelocation () {
    int min;
    
    min = caveMapping[arrowLocation - 1][0];
    for (int i = 0; i < 3; ++i) {
        if (caveMapping[userLocation - 1][i] < min) {
            min = caveMapping[arrowLocation - 1][i];
        }
    }
    arrowLocation = min;
}

// function to shoot the user's arrow with parameter to keep track of moves
void shootArrow (int &z) {
    int numberRooms,
        roomFirst,
        roomSecond,
        roomThird,
        min,
        i;
    
    // checks if the user has the arrow
    if (arrowLocation != -1) {
        cout << "Sorry, you can't shoot an arrow you\ndon't have. Go find it.\n";
        return;
    }
    else if (arrowLocation == -1) {
        cout << "Enter the number of rooms (1..3) into\nwhich you want to shoot, followed by\nthe rooms themselves: ";
    }
    
    cin >> numberRooms;   // takes the user input for how many rooms they want to shoot into
    
    // switch case statement to execute for how many rooms the user wants to shoot into
    switch (numberRooms) {
        case 1: cin >> roomFirst;   // gets user input for which room they want to shoot into
                
                // checks if room is adjacent to current room
                if (caveMapping[userLocation - 1][0] == roomFirst || caveMapping[userLocation - 1][1] == roomFirst || caveMapping[userLocation - 1][2] == roomFirst) {
                    arrowLocation = roomFirst;   // makes arrowLocation = to the room that was chosen to be shot into if conditions are true
                    checkArrowDeath();   // checks if the arrow caused any deaths by calling checkArrowDeath function
                }
                else {
                    cout << "Room " << roomFirst << " is not adjacent. Arrow\nricochets...\n";
                    arrowLocation = userLocation;   // if room chosen is not adjacent, the arrow bounces off user's room so it has to = the user's location
                    
                    arrowRelocation();   // relocates arrow 
                    
                    checkArrowDeathRicochet();   // calls checkArrowDeathRicochet to see if ricochet killed anyone
                }
                wumpusRelocation();   // calls wumpusRelocation function since Wumpus moves every time the arrow is shot
                break;
        
        // case 2 is same as case 1 except the same if statements are nested once to check if all rooms are valid
        case 2: cin >> roomFirst >> roomSecond;
            
                if (caveMapping[userLocation - 1][0] == roomFirst || caveMapping[userLocation - 1][1] == roomFirst || caveMapping[userLocation - 1][2] == roomFirst) {
                    arrowLocation = roomFirst;
                    checkArrowDeath();
                    if (caveMapping[roomFirst - 1][0] == roomSecond || caveMapping[roomFirst - 1][1] == roomSecond || caveMapping[roomFirst - 1][2] == roomSecond) {
                        arrowLocation = roomSecond;
                        checkArrowDeath();
                    }
                    else {
                        cout << "Room " << roomSecond << " is not adjacent. Arrow\nricochets...\n";
                        arrowLocation = roomFirst;
                    
                        arrowRelocation();
                    
                        checkArrowDeathRicochet();
                    }
                }
                else {
                    cout << "Room " << roomFirst << " is not adjacent. Arrow\nricochets...\n";
                    arrowLocation = userLocation;
                    
                    arrowRelocation();
                    
                    checkArrowDeathRicochet();
                }
                wumpusRelocation();
                break;
        
        // case 3 is same as case 1 except the same if statements are nested twice to check if all rooms are valid
        case 3: cin >> roomFirst >> roomSecond >> roomThird;
            
                if (caveMapping[userLocation - 1][0] == roomFirst || caveMapping[userLocation - 1][1] == roomFirst || caveMapping[userLocation - 1][2] == roomFirst) {
                    arrowLocation = roomFirst;
                    checkArrowDeath();
                    if (caveMapping[roomFirst - 1][0] == roomSecond || caveMapping[roomFirst - 1][1] == roomSecond || caveMapping[roomFirst - 1][2] == roomSecond) {
                        arrowLocation = roomSecond;
                        checkArrowDeath();
                        if (caveMapping[roomSecond - 1][0] == roomThird || caveMapping[roomSecond - 1][1] == roomThird || caveMapping[roomSecond - 1][2] == roomThird) {
                            arrowLocation = roomThird;
                            checkArrowDeath();
                        }
                        else {
                            cout << "Room " << roomThird << " is not adjacent. Arrow\nricochets...\n";
                            arrowLocation = roomSecond;
                    
                            arrowRelocation();
                    
                            checkArrowDeathRicochet();
                        }
                    }
                    else {
                        cout << "Room " << roomSecond << " is not adjacent. Arrow\nricochets...\n";
                        arrowLocation = roomFirst;
                    
                        arrowRelocation();
                    
                        checkArrowDeathRicochet();
                    }
                }
                else {
                    cout << "Room " << roomFirst << " is not adjacent. Arrow\nricochets...\n";
                    arrowLocation = userLocation;
                    
                    arrowRelocation();
                    
                    checkArrowDeathRicochet();
                }
                wumpusRelocation();
                break;
    }
    ++z;   // each time function is called move count increases by 1
}

// function to print the picture of the maze
void printMaze () {
    cout << endl << setw(23) << "-------18-------\n"
         << setw(6) << "/" << setw(8) << "|" << setw(9) << "\\" << endl
         << setw(5) << "/" << setw(9) << "9" << setw(10) << "\\" << endl
         << setw(4) << "/" << setw(9) << "/" << setw(2) << "\\" << setw(10) << "\\" << endl
         << setw(3) << "/" << setw(9) << "/" << setw(4) << "\\" << setw(10) << "\\" << endl
         << setw(3) << "17" << setw(8) << "8" << setw(6) << "10" << setw(10) << "19" << endl
         << setw(3) << "|\\" << setw(8) << "/\\" << setw(7) << "/\\" << setw(9) << "/|" << endl
         << setw(4) << "| \\" << setw(8) << "/  \\" << setw(7) << "/  \\" << setw(8) << "/ |" << endl
         << setw(2) << "|" << setw(4) << "7" << setw(9) << "1-2" << setw(8) << "11" << setw(4) << "|"<< endl
         << setw(2) << "|" << setw(4) << "|" << setw(6) << "/" << setw(4) << "\\" << setw(6) << "|" << setw(5) << "|"<< endl
         << setw(2) << "|" << setw(10) << "6-----5" << setw(11) << "3-----12" << setw(4) << "|" << endl
         << setw(2) << "|" << setw(4) << "|" << setw(6) << "\\" << setw(4) << "/" << setw(6) << "|" << setw(5) << "|"<< endl
         << setw(2) << "|" << setw(5) << "\\" << setw(7) << "4" << setw(7) << "/" << setw(6) << "|" << endl
         << setw(2) << "|" << setw(6) << "\\" << setw(6) << "|" << setw(6) << "/" << setw(7) << "|" << endl
         << setw(3) << "\\" << setw(17) << "15---14---13" << setw(6) << "/" << endl
         << setw(4) << "\\" << setw(5) << "/" << setw(11) << "\\" << setw(5) << "/" << endl
         << setw(5) << "\\" << setw(3) << "/" << setw(13) << "\\" << setw(3) << "/" << endl
         << setw(24) << "16--------------20\n\n"; 
}

// function to print the directions of the game
void printDirections () {
    printMaze();   // function call to printMaze
    cout << "Hunt the Wumpus:\n"
         << "The Wumpus lives in a completely dark cave of 20 rooms. Each\n"
         << "room has 3 tunnels leading to other rooms.\n\n"
         << "Hazards:\n"
         << "1. Two rooms have bottomless pits in them. If you go there you fail and\n"
         << "die.\n"
         << "2. Two other rooms have super-bats. If you go there, the bats grab you\n"
         << "and fly you to some random room, which could be troublesome. Then those\n"
         << "bats go to a new room different from where thy came from and from the\n"
         << "other bats.\n"
         << "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet\n"
         << "and is too heavy for bats to lift. Usually he is asleep. Two things wake him\n"
         << "up: Anytime you shoot an arrow, or you entering his room. The Wumpus will\n"
         << "move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
         << "When you move into the Wumpus' room, then he wakes and moves if he is in\n"
         << "an odd-numbered room, but stays still otherwise. After that, if he is in your\n"
         << "room, he snaps your neck and you die!\n\n"
         << "Moves:\n"
         << "On each move you can do the following, where input can be upper or\n"
         << "lower-case:\n"
         << "1. Move into an adjacent room. To move enter 'M' followed by a space\n"
         << "and then a room number.\n"
         << "2. Shoot your guided arrow through a list of up to three adjacent rooms,\n"
         << "which you specify. Your arrow ends up in the final room. To shoot enter 'S'\n"
         << "followed by the number of rooms (1..3), and then the list of the desired\n"
         << "number (up to 3) of adjacent room numbers, seperated by spaces. If an\n"
         << "arrow can't go a direction because there is no connecting tunnel, it ricochets\n"
         << "and moves to the lowest-numbered adjacent room and continues doing this\n"
         << "until it has traveled the designated number of rooms. If the arrow hits the\n"
         << "Wumpus, you win! If the arrow hits you, you lose. You automatically pick up\n"
         << "the arrow if you go theough a room with the arrow in it.\n"
         << "3. Enter 'R' to reset the person and hazard locations, useful for testing.\n"
         << "4. Enter 'C' to cheat and display current board positions.\n"
         << "5. Enter 'D' to display this set of instructions.\n"
         << "6. Enter 'P' to print the maze room layout.\n"
         << "7. Enter 'X' to exit the game.\n\n"
         << "Good luck!\n\n";
}

// main function to bring the functions together and run the program
int main () {
    char userInput;      // variable for user's input of move choice
    int i = 1,           // keeps track of the move count
        userSpotChange;  // variable to get spot user wants to move to
    
    srand(time(NULL));   // initializes the random seed with time
    
    initializeLocations();   // calls the initializeLocations function to set up inital postions of user, arrow, and hazards
    mapCave();               // calls mapCave function to map out the cave
    
    // keeps running until user decides to end, wins, or dies
    while (true) {
        cout << "You are in room " << userLocation << ". ";
        checkAdjacentSpots();    // function call of checkAdjacentSpots to check the adjacent spots of user for hazards
            
        cout << endl << endl << i << ". Enter your move (or 'D' for directions): ";
        
        cin >> userInput;
        userInput = toupper(userInput);   // changes user input to uppercase so it is easier to identify
        
        // switch case to run user's desired choice
        switch (userInput) {
            case 'P': printMaze();               // function call to printMaze
                      break;
                
            case 'D': printDirections();         // function call to printDirections
                      break;
                
            case 'C': printCurrentLocations();   // function call to printCurrentLocations
                      break;
                
            case 'R': resetLocations();          // function call to resetLocations
                      break;
                
            case 'M': cin >> userSpotChange;     // input stream to get user's desired spot
                      checkValidLocation(userSpotChange, i);   // function call to checkValidLocation
                      checkCurrentHazards();                   // function call to checkCurrentHazards
                      break;
                
            case 'S': shootArrow(i);             // function call to shootArrow
                      checkCurrentHazards();     // function call to checkCurrentHazards
                      break;
            
            case 'X': cout << "\nExiting Program...\n";        // case to exit the program
                      exit(0);      
        }
    }
     
    return 0;   // returns 0 to let main know that program is over
}