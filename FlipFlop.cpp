#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define MAX_ARRAY_SIZE 24
#define MIN_ARRAY_SIZE 8

const int NOPLAYER = 0;
const int WHITEPLAYER = 1;
const int BLACKPLAYER = 2;
const int FIRST_PIECE = 1;
const int SECOND_PIECE = 2;


bool PlacePiece(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int squarePlayed,
    int whichPiece, int& numberCaptured);
bool DisplayBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard);
bool InitialiizeBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard);
bool CheckLine(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int squarePlayed,
    int xDirection, int yDirection, int& numCaptured);
bool IsAnyMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int whichPiece);
bool IsThisMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int squarePlayed, int whichPiece);



int main()
{
    int numrowsinboard = 0;
    int REMAINDER = 1;
    int EVEN = 2;
    int inputerror = 0;
    int movenumber = 1;
    int player = 1;
    int captured = 0;
    int squareplayed = 0;
    int totalcaptured = 0;
    int totalmoves = 0;
    int y_index = 0;
    int x_index = 0; 
    int squaresinboard = 0;
    int playerinloop = 1;
    string playername;
    string firstorsecondmove;
    string answer;


    //player 1 is white, player 2 is black
    
    int myFlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    // ADD CODE FOR MAIN FUNCTION HERE
 
    for (int count = 0; count < 3; count++) {
        cout << "enter the size of the board:";
        cin >> numrowsinboard;

        if (numrowsinboard < MIN_ARRAY_SIZE) {
            cout << endl << "Board size too small " << endl;
            cout << "valid values are even numbers between " << MIN_ARRAY_SIZE << " and " << MAX_ARRAY_SIZE << "." << endl;
            inputerror = 1;
        }
        else if (numrowsinboard > MAX_ARRAY_SIZE) {
            cout << "Board size too large" << endl;
            cout << "valid values are even numbers between " << MIN_ARRAY_SIZE << " and " << MAX_ARRAY_SIZE << "." << endl;
            inputerror = 1;
        }
        else if ((numrowsinboard % EVEN) == REMAINDER) {
            cout << "Board size odd" << endl;
            cout << "valid values are even numbers between " << MIN_ARRAY_SIZE << " and " << MAX_ARRAY_SIZE << "." << endl;
            inputerror = 1;
        }
        else if (cin.fail()) {
            cout << "Board size is not an integer" << endl; // fix this it doesnt work
            inputerror = 1;
        }
        else {
            inputerror = 0;
            count = 3;
            squaresinboard = numrowsinboard * numrowsinboard;
        }
    } if (inputerror == 1) {
        cout << "ERROR: Too many errors entering the size of the board" << endl;
        exit;
    }
    InitialiizeBoard(myFlipFlopBoard, numrowsinboard);
    DisplayBoard(myFlipFlopBoard, numrowsinboard);
    totalmoves = (((numrowsinboard * numrowsinboard) - 4)/2);
    while (IsAnyMoveValid(myFlipFlopBoard, numrowsinboard, player, movenumber) == true) {
        movenumber = 1;
        firstorsecondmove = "first piece";
        if (playerinloop % 2 == 0) {
            player = 2;
            playername = "Black";

        }
        else {
            player = 1;
            playername = "White";
        }

        //for (int i = 0; i < totalmoves; i++) {
            //player = 1;
           // if (IsAnyMoveValid(myFlipFlopBoard, numrowsinboard, player, movenumber) == true){
        for (int count = 0; count < 3; count++) {
            cout << playername << " enter the square number of the square you want to put your "<< firstorsecondmove<< " on : ";
            cin >> squareplayed;
            if (squareplayed < 0 || squareplayed> squaresinboard) {
                cout << "ERROR: that square is not on the board." << endl << "Try again" << endl;
            }
            else if (myFlipFlopBoard[y_index][x_index] != 0) {
                cout << "ERROR: that square is already occupied." << endl << "Try again" << endl;
            }

            else if (IsThisMoveValid(myFlipFlopBoard, numrowsinboard, player, squareplayed, movenumber) == false) {
                cout << "ERROR: illegal move " << endl << "Try again" << endl;
                inputerror = 1;
            }
            else {
                inputerror = 0;
                count = 3;
            }
        }
        if (inputerror == 1) {
            cout << "Player has fortfieted a turn" << endl;
        }
        else {
            if (PlacePiece(myFlipFlopBoard, numrowsinboard, player, squareplayed, movenumber, totalcaptured) == true) {
                cout << "Your " << firstorsecondmove <<" captured " << totalcaptured << " opponent's pieces" << endl;
                DisplayBoard(myFlipFlopBoard, numrowsinboard);
            }
        }
        if (totalcaptured > 1) {
            cout << "You've captured more than one piece, would you like a second piece?";
            cin >> answer;
            cout << endl;
            if (answer == "yes") {
                movenumber = 2;
                firstorsecondmove = "second piece";
                for (int count = 0; count < 3; count++) {
                    cout << playername << " enter the square number of the square you want to put your " << firstorsecondmove << " on : ";
                    cin >> squareplayed;
                    if (squareplayed < 0 || squareplayed> squaresinboard) {
                        cout << "ERROR: that square is not on the board." << endl << "Try again" << endl;
                    }
                    else if (myFlipFlopBoard[y_index][x_index] != 0) {
                        cout << "ERROR: that square is already occupied." << endl << "Try again" << endl;
                    }

                    else if (IsThisMoveValid(myFlipFlopBoard, numrowsinboard, player, squareplayed, movenumber) == false) {
                        cout << "ERROR: illegal move " << endl << "Try again" << endl;
                        inputerror = 1;
                    }
                    else {
                        inputerror = 0;
                        count = 3;
                    }
                }
                if (inputerror == 1) {
                    cout << "Player has fortfieted a turn" << endl;
                }
                else {
                    if (PlacePiece(myFlipFlopBoard, numrowsinboard, player, squareplayed, movenumber, totalcaptured) == true) {
                        cout << "Your " << firstorsecondmove << " captured " << totalcaptured << " opponent's pieces" << endl;
                        DisplayBoard(myFlipFlopBoard, numrowsinboard);
                    }
                }
            }
        }
        else {
            playerinloop++;
        }
    }
    
        cout << "no valid moves" << endl;
    
    return 0;
}

bool InitialiizeBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard)
{
    int horizontal = 0;
    int vertical = 0;
    //FlipFlopBoard = { 0 };
    for (int i = 0; i < numRowsInBoard; i++) {
        for (int j = 0; j < numRowsInBoard; j++) {
            FlipFlopBoard[i][j] = 0;
        }
   }
    horizontal = numRowsInBoard / 2;
    vertical = numRowsInBoard / 2;
    FlipFlopBoard[vertical-1][horizontal-1] = 1;
    FlipFlopBoard[vertical - 1][horizontal] = 2;
    FlipFlopBoard[vertical][horizontal - 1] = 2;
    FlipFlopBoard[vertical][horizontal] = 1; 

    /*for (int i = 0; i < numRowsInBoard; i++) {
        for (int j = 0; j < numRowsInBoard; j++) {
            cout << FlipFlopBoard[i][j] << " ";
        }
        cout << endl;
    }*/
    
    return false; 
}

bool DisplayBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard) {
    int placeholder = 0;
    for (int i = 0; i < numRowsInBoard; i++) {
        for (int j = 0; j < numRowsInBoard; j++) {
            if (FlipFlopBoard[i][j] == 1) {
                cout <<fixed << setw(4) << "W";
            }
           else if (FlipFlopBoard[i][j] == 2) {
                cout <<fixed << setw(4) << "B";
            }
            else {
                cout <<fixed<< setw(4)<< placeholder;
           }
            placeholder++;
            //cout << FlipFlopBoard[i][j] << " ";
        }
        cout << endl;
    }
    return false;
}

bool IsAnyMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int whichPiece) {
    int x = 0;
    int y = 0;
    int y_index = 0;
    int x_index = 0;
    int numberCaptured = 0;
    int totalcaptured = 0;
    int possiblesquare = 0;

    for (int i = 0; i < numRowsInBoard; i++) {
        for (int j = 0; j < numRowsInBoard; j++) {
            if (whichPiece == 1) {
                //check vertically
                x = 0;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check horizontally
                x = 1;
                y = 0;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check negative vertically
                x = 0;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check negative horizontally
                x = -1;
                y = 0;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                possiblesquare++;
            }
            else if (whichPiece == 2) {
                //check diagonally
                x = 1;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check negative diagonally
                x = -1;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                x = 1;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                x = -1;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, possiblesquare,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                possiblesquare++;
            }
        }
    }
    
    if (totalcaptured > 0) {
        return true;
    }
    else {

        return false;
    }
}

bool PlacePiece(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int squarePlayed,
    int whichPiece, int& numberCaptured) {
    int x = 0;
    int y = 0;
    int y_index = 0;
    int x_index = 0;
    int totalcaptured = 0;
    int otherplayer = 0;
    y_index = squarePlayed / numRowsInBoard;
    x_index = squarePlayed % numRowsInBoard;

    if (player == 1) {
        otherplayer = 2;
    }
    else if (player == 2) {
        otherplayer = 1;
    }
    //FlipFlopBoard[x_index][y_index];
            if (whichPiece == 1) {
                //check vertically
                x = 0;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player; 
                    }
                }
                //check horizontally
                x = 1;
                y = 0;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
                //check negative vertically
                x = 0;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
                //check negative horizontally
                x = -1;
                y = 0;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
            }
            else if (whichPiece == 2) {
                //check diagonally
                x = 1;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
                //check negative diagonally
                x = -1;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
                x = 1;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
                x = -1;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                    if (FlipFlopBoard[y_index + y][x_index + x] = otherplayer) {
                        FlipFlopBoard[y_index + y][x_index + x] = player;
                    }
                }
            }


    
    if (totalcaptured > 0) {

        FlipFlopBoard[y_index][x_index] = player; 
        return true;

    }
    else {

        return false;
    }
}

bool IsThisMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
    int numRowsInBoard, int player, int squarePlayed, int whichPiece) {
    int x = 0;
    int y = 0;
    int y_index = 0;
    int x_index = 0;
    int numberCaptured = 0;
    int totalcaptured = 0;

            if (whichPiece == 1) {
                //check vertically
                x = 0;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check horizontally
                x = 1;
                y = 0;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check negative vertically
                x = 0;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check negative horizontally
                x = -1;
                y = 0;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
            }
            else if (whichPiece == 2) {
                //check diagonally
                x = 1;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                //check negative diagonally
                x = -1;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                x = 1;
                y = -1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
                x = -1;
                y = 1;
                if (CheckLine(FlipFlopBoard, numRowsInBoard,
                    player, squarePlayed,
                    x, y, numberCaptured) == true) {
                    totalcaptured = totalcaptured + numberCaptured;
                }
            }
        
    
    if (totalcaptured > 0) {
        return true;
    }
    else {

        return false;
    }
}

bool CheckLine(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard,
    int player, int squarePlayed,
    int xDirection, int yDirection, int& numCaptured)
{
    // This function takes the FlipFlopBoard and calculates
    // how the board changes when player player
    // (player=1 for white, player=2 for black)
    // This function checks along a row in one direction for
    // al legal move. If no legal move is found this function
    // returns false, if a legal move is found this function
    // returns true.
    // Author Janice Regan; 2022
    int otherPlayer;
    char piece = 2;           // to compare for otherPlayers
    int xIndex = 0;
    int yIndex = 0;
    int xCoordinate = 0;
    int yCoordinate = 0;
    bool edge = true;
    numCaptured = 0;

    otherPlayer = WHITEPLAYER;
    if (player == WHITEPLAYER)
    {
        otherPlayer = BLACKPLAYER;
    }

    // find row and column were new piece may be placed
    xCoordinate = squarePlayed % numRowsInBoard;
    yCoordinate = squarePlayed / numRowsInBoard;

    //if the square selected is occupied return false
    if (FlipFlopBoard[yCoordinate][xCoordinate] == player ||
        FlipFlopBoard[yCoordinate][xCoordinate] == otherPlayer)
    {
        return false;
    }


    // find the square next to the location the piece may
    // be played. Next in the direction (xDirection,yDirection)
    yIndex = yCoordinate + yDirection;
    xIndex = xCoordinate + xDirection;

    // while the square to be checked is on the board 
    // continue looking for a legal move
    // If the square is not on the board then return false
    // there is no legal move in the indicated direction
    while ((xIndex < numRowsInBoard &&
        yIndex < numRowsInBoard) &&
        (xIndex >= 0 && yIndex >= 0))
    {
        //if the location where the piece is to be placed
        //is next to an empty square or to another of the
        //player's pieces, then the there is no legal
        // move in the direction indicated 
        // return false
        if (FlipFlopBoard[yIndex][xIndex] == NOPLAYER ||
            FlipFlopBoard[yIndex][xIndex] == player)
        {
            return false;
        }
        else
        {
            // The next piece in the direction indicated is a
            // opponent's piece. The move may be legal, proceed
            // in the indicated direction and try to find a players
            // piece.  If one is found before the edge of the board
            // is reached the move is legal
            // If a legal move is found, count the number of pieces
            // captured,  then return true.
            edge = true;
            while (yIndex < numRowsInBoard &&
                xIndex < numRowsInBoard &&
                yIndex >= 0 && xIndex >= 0)
            {
                edge = false;
                if (FlipFlopBoard[yIndex][xIndex] == NOPLAYER)
                {
                    //next square along the indicated direction is empty
                    //move is illegal
                    return false;
                }
                if (FlipFlopBoard[yIndex][xIndex] == player)
                {
                    //next square along the direction indicated hold
                    //one of the players pieces.  The move is legal
                    break;
                }
                else
                {
                    //next square along the direction indicated holds
                    //an opponents piece, continue along the same 
                    //direction and try the next square
                    numCaptured++;
                    xIndex += xDirection;
                    yIndex += yDirection;
                    edge = true;
                }
            }


            if (edge == true)
            {
                //The edge of the board has been reached without 
                //finding a players piece, move is not legal
                return false;
            }
            return true;
        }
    }
    //The edge of the board has been reached,
    //no legal move.  return false
    return false;
}


