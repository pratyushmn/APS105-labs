#include <stdio.h>
#include <stdbool.h>

// declaring functions which will be used in this program
void printBoard(char board[ ][26], int n);
void printColLabels(int n);
bool positionInBounds (int n, char row, char col);
bool checkLegalInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
bool checkValidity(char board[ ][26], int n, char row, char col, char colour);
bool areMovesAvailable(char board[ ][26], int n, char colour);
void flipTiles(char board[ ][26], int n, char row, char col, char colour);
void flipTilesInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
void makeMoveAI(char board[ ][26], int n, char colour);
int scoreMoveInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
int scoreMove(char board[ ][26], int n, char row, char col, char colour);
void didPlayerWin(char board[ ][26], int n, char playerColour);

// the main function
int main(void)
{
    // declaring the local variables for the main function
    int dimension, rowCounter, colCounter;
    char compColour, playerColour;
    char moveRow, moveCol;
    int moveRowInt, moveColInt;
    
    // prompting user for board dimensions
	printf("Enter the board dimension: ");
    scanf("%d", &dimension);
    char board[26][26];
    
    // setting the board so that it matches initial conditions of a Reversi game
    for(rowCounter = 0; rowCounter < dimension; rowCounter++){
        for(colCounter = 0; colCounter < dimension; colCounter++){
            board[rowCounter][colCounter] = 'U';
        }
    }
    board[(dimension-1)/2][(dimension-1)/2] = 'W';
    board[(dimension+1)/2][(dimension+1)/2] = 'W';
    board[(dimension-1)/2][(dimension+1)/2] = 'B';
    board[(dimension+1)/2][(dimension-1)/2] = 'B';
    
    // prompting the player for what colour the AI will play as
    printf("Computer plays (B/W) : ");
    scanf(" %c", &compColour);
    
    // assigning the player's colour
    if(compColour == 'B') {
        playerColour = 'W';
        printBoard(board, dimension);
        makeMoveAI(board, dimension, compColour);
    } else if(compColour == 'W') {
        playerColour = 'B';
    } else {
        printf("Invalid colour.\nPlease restart the program and retry.");
        return 0;
    }
    
    // printing the board befre the player's first move
    printBoard(board, dimension);
    
    // prompting the player and then the AI for moves as long as they both have available moves
    do {
        if(areMovesAvailable(board, dimension, playerColour)) {
            // prompting user to enter the move they'd like only if they have one available
            printf("Enter move for colour %c (RowCol): ", playerColour);
            scanf(" %c%c", &moveRow, &moveCol);
            moveRowInt = ((int) moveRow) - 97;
            moveColInt = ((int) moveCol) - 97;
            
            // only enter the move into the board if it is valid
            if(checkValidity(board, dimension, moveRow, moveCol, playerColour) && positionInBounds(dimension, moveRow, moveCol)){
                flipTiles(board, dimension, moveRow, moveCol, playerColour);
                board[moveRowInt][moveColInt] = playerColour;
                printBoard(board, dimension);
            } else {
                // if not valid, the computer wins
                printf("Invalid move.\n%c player wins.", compColour);
                return 0;
            }
        } else if(areMovesAvailable(board, dimension, compColour)){
            // if no valid moves available, a message is printed to the player
            printf("%c player has no valid move.\n", playerColour);
        }
        
        if(areMovesAvailable(board, dimension, compColour)) {
            // the AI makes a move if it has an available move
            makeMoveAI(board, dimension, compColour);
            printBoard(board, dimension);
        } else if(areMovesAvailable(board, dimension, playerColour)) {
            // if not, a message is printed to inform the player
            printf("%c player has no valid move.\n", compColour);
        }
    } while(areMovesAvailable(board, dimension, playerColour) || areMovesAvailable(board, dimension, compColour));
    
    // the function is called to decide and inform the player as to who won the game
    didPlayerWin(board, dimension, playerColour);
	return 0;
}

// the function which prints out the board
void printBoard(char board[ ][26], int n)
{
    // declaring local variables
    int rowCounter, colCounter;
    
    // calls another function to print out the labels for each column
    printColLabels(n);
    
    // two nested for loops to go through each column and each row to print the contents of each cell in the array
    for(rowCounter = 0; rowCounter < n; rowCounter++){
         printf("%c " , (char) (97+rowCounter));
         for(colCounter = 0; colCounter < n; colCounter++){
             printf("%c", board[rowCounter][colCounter]);
         }
        printf("\n");
    }
}

// the function which prints the labels for each column
void printColLabels(int n)
{
    // declaring local variables
    int counter;
    printf("  ");
    
    // for loop to print each letter above the board
    for(counter = 0; counter < n; counter++){
        printf("%c", (char) (97+counter));
    }
    printf("\n");
    return;
}

// the function which checks whether an entered position is in bounds of the board
bool positionInBounds (int n, char row, char col)
{
    // converting the character inputs into integers, and checking if they are less than the dimension of the board
    if(((int) row - 97) < n && ((int) col - 97) < n){
        return true;
    } else{
        return false;
    }
}

// the function which checks whether a move in legal in any specific direction from the position
bool checkLegalInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{
    // declaring and initializing local variables
    int rowInt = (int) row - 97;
    int colInt = (int) col - 97;
    char oppColour;
    if(colour == 'W') {
        oppColour = 'B';
    } else if(colour == 'B') {
        oppColour = 'W';
    }
    
    // starting at the specified position, going through the tiles in the specified direction
    for(int rowIntCounter = rowInt, colIntCounter = colInt ; 0 <= rowIntCounter && rowIntCounter < n && 0 <= colIntCounter && colIntCounter < n; rowIntCounter = rowIntCounter + deltaRow, colIntCounter = colIntCounter + deltaCol){
        // the position right after in the specified direction must be the opposite color
        if(board[rowInt + deltaRow][colInt + deltaCol] == oppColour){
            // then if, in that direction, it is still the opposite color, then you need to go through the loop again and do nothing
            // if you get an unfilled in that direction, the move isn't legal after all
            // if you get end up getting a tile of the same color in that direction, then it is a legal move
            if(board[rowIntCounter + deltaRow][colIntCounter + deltaCol] == colour){
                return true;
            } else if(board[rowIntCounter + deltaRow][colIntCounter + deltaCol] == 'U'){
                return false;
            }
        }
    }
    return false;
}

// the function which checks if a certain move is valid or not
bool checkValidity(char board[ ][26], int n, char row, char col, char colour)
{
    // checks if that spot is unfilled
    if(board[(int)row - 97][(int) col - 97] == 'U'){
        // if it is, then it checks to see if it is legal in any one of the 8 directions, returning true if it is legal in at least one
        if(checkLegalInDirection(board, n, row, col, colour, -1, -1)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, -1, 0)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, -1, 1)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, 0, -1)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, 0, 1)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, 1, -1)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, 1, 0)){
            return true;
        } else if(checkLegalInDirection(board, n, row, col, colour, 1, 1)){
            return true;
        } else{
            return false;
        }
    } else{
        return false;
    }
}

// the function which checks if a certain colour has any available moves
bool areMovesAvailable(char board[ ][26], int n, char colour)
{
    // declaring local variables
    int rowCounter, colCounter;
    // going through the board and checking if there's at least one cell which is a valid move
    for(rowCounter = 0; rowCounter < n; rowCounter++) {
        for(colCounter = 0; colCounter < n; colCounter++) {
            if(checkValidity(board, n, rowCounter + 'a', colCounter + 'a', colour)) {
                return true;
            }
        }
    }
    return false;
}

// the function which flips the tiles when a legal move is placed
void flipTiles(char board[][26], int n, char row, char col, char colour)
{
    // calls another function to both check if it can flip tiles in a certain direction, and then to actually flip them
    flipTilesInDirection(board, n, row, col, colour, -1, -1);
    flipTilesInDirection(board, n, row, col, colour, -1, 0);
    flipTilesInDirection(board, n, row, col, colour, -1, 1);
    flipTilesInDirection(board, n, row, col, colour, 0, -1);
    flipTilesInDirection(board, n, row, col, colour, 0, 1);
    flipTilesInDirection(board, n, row, col, colour, 1, -1);
    flipTilesInDirection(board, n, row, col, colour, 1, 0);
    flipTilesInDirection(board, n, row, col, colour, 1, 1);    
}

void flipTilesInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{
    // declaring local variables 
    int rowInt = ((int) row) - 97;
    int colInt = ((int) col) - 97;
    int counter;
    char oppColour;
    
    if(colour == 'W') {
        oppColour = 'B';
    } else if(colour == 'B') {
        oppColour = 'W';
    }
    
    // making sure that spot is unoccupied right now
    if(board[rowInt][colInt] == 'U'){
        // checks if the move is legal in the inputted direction; if not, it does nothing
        if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
            // if legal, a for loop goes through that direction and flips anything of the opposite colour until it reaches a cell of the same colour
            for(counter = 1; ; counter ++){
                if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == oppColour){
                    board[rowInt + deltaRow*counter][colInt + deltaCol*counter] = colour;
                } else if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == colour){
                    return;
                }
            }
        } else {
            // if not legal, it does nothing
            return;
        }
    }
    return;
}

// the function which acts as the AI, choosing which spot to place a tile in
void makeMoveAI(char board[ ][26], int n, char colour)
{
    // declaring local variables
    int rowCounter, colCounter, score = 0, bestRow = 0, bestCol = 0;
    int maxScore = 0;
    // going through the board and computing a score for each cell which is a valid move
    for(rowCounter = 0; rowCounter < n; rowCounter++) {
        for(colCounter = 0; colCounter < n; colCounter++) {
            if(board[rowCounter][colCounter] == 'U' && checkValidity(board, n, rowCounter + 'a', colCounter + 'a', colour)) {
                score = scoreMove(board, n, rowCounter + 'a', colCounter + 'a', colour);
                // saving the index only if that position is the best scoring position so far
                if(score > maxScore) {
                    maxScore = score;
                    bestRow = rowCounter;
                    bestCol = colCounter;
                }
            }
        }
    }
    // flipping the tiles in the best scoring position, and then informing the player
    flipTiles(board, n, bestRow + 'a', bestCol + 'a', colour);
    board[bestRow][bestCol] = colour;
    printf("Computer places %c at %c%c.\n", colour, bestRow + 'a', bestCol + 'a');
}

// the function which scores a move in a certain direction
int scoreMoveInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{
    // declaring local variables 
    int rowInt = ((int) row) - 97;
    int colInt = ((int) col) - 97;
    int counter;
    int score = 0;
    char oppColour;
    
    // assigning colours
    if(colour == 'W') {
        oppColour = 'B';
    } else if(colour == 'B') {
        oppColour = 'W';
    }
    
    // making sure that spot is unoccupied right now
    if(board[rowInt][colInt] == 'U'){
        // checks if the move is legal in the inputted direction; if not, it does nothing
        if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
            // if legal, a for loop goes through that direction and adds 1 to the score if it sees a tile of the opposite colour until it reaches a cell of the same colour
            for(counter = 1; ; counter ++){
                if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == oppColour){
                    score++;
                } else if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == colour){
                    return score;
                }
            }
        } else {
            // if not legal, it does nothing
            return 0;
        }
    }
    return 0;
}

// the function which scores a move in all directions
int scoreMove(char board[ ][26], int n, char row, char col, char colour)
{
    // the score is the sum of the score in each individual direction
    int score;
    score = scoreMoveInDirection(board, n, row, col, colour, -1, -1) +
    scoreMoveInDirection(board, n, row, col, colour, -1, 0) +
    scoreMoveInDirection(board, n, row, col, colour, -1, 1) +
    scoreMoveInDirection(board, n, row, col, colour, 0, -1) +
    scoreMoveInDirection(board, n, row, col, colour, 0, 1) +
    scoreMoveInDirection(board, n, row, col, colour, 1, -1) +
    scoreMoveInDirection(board, n, row, col, colour, 1, 0) +
    scoreMoveInDirection(board, n, row, col, colour, 1, 1);
    return score;
}

// the function which decides who won
void didPlayerWin(char board[ ][26], int n, char playerColour)
{
    // declaring local variables
    int playerScore = 0, compScore = 0;
    char compColour;
    
    // assigning colours
    if(playerColour == 'B') {
        compColour = 'W';
    } else if(playerColour == 'W') {
        compColour = 'B';
    }
    
    // going through the board and adding to the score of either the player or computer based on the tile colour
    for(int rowCounter = 0; rowCounter < n; rowCounter++) {
        for(int colCounter = 0; colCounter < n; colCounter++) {
            if(board[rowCounter][colCounter] == playerColour) {
                playerScore++;
            } else if(board[rowCounter][colCounter] == compColour) {
                compScore++;
            }
        }
    }
    // deciding and informing the player who won
    if(playerScore > compScore) {
        printf("%c player wins.", playerColour);
        return;
    } else if(playerScore == compScore) {
        printf("The game ended in a tie.");
        return;
    } else {
        printf("%c player wins.", compColour);
        return;
    }
    return;
}