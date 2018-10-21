#include <stdio.h>
#include <stdbool.h>

// declaring funtions which will be used in this program
void printBoard(char board[ ][26], int n);
void printColLabels(int n);
bool positionInBounds (int n, char row, char col);
void printValidMoves(char board[ ][26], int n, char colour);
bool checkLegalInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
bool checkValidity(char board[ ][26], int n, char row, char col, char colour);
void flipTiles(char board[ ][26], int n, char row, char col, char colour);
void flipTilesInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);

// the main function
int main(void)
{
    // declaring the local variables for the main function
    int dimension, rowCounter, colCounter;
    char config1, config2, config3;
    char move1, move2, move3;
    int config2int, config3int;
    int move2int, move3int;
    
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
    
    // printing the initial board
    printBoard(board, dimension);
    
    // prompting the user for board configuration
    printf("Enter board configuration:\n");
    do{
        scanf(" %c%c%c", &config1, &config2, &config3);
        config2int = ((int) config2) - 97;
        config3int = ((int) config3) - 97;
        
        // only sets the board to match entered configuration if it is in bounds
        if((positionInBounds(dimension, config2, config3) && (config1 == 'B' || config1 == 'W')) || (config1 == '!' && config2 == '!' && config3 == '!')){
            board[config2int][config3int] = config1;
        } else {
            printf("Invalid move.\n");
        }
    } while(config1 != '!' && config2 != '!' && config3 != '!');
    
    // printing the board and the available moves for each colour
    printBoard(board, dimension);
    printf("Available moves for W:\n");
    printValidMoves(board, dimension, 'W');
    printf("Available moves for B:\n");
    printValidMoves(board, dimension, 'B');
    
    // prompting user to enter the move they'd like
    printf("Enter a move:\n");
    scanf(" %c%c%c", &move1, &move2, &move3);
    move2int = ((int) move2) - 97;
    move3int = ((int) move3) - 97;
    
    // only enter the move into the board if it is valid
    if(checkValidity(board, dimension, move2, move3, move1) && positionInBounds(dimension, move2, move3) && (move1 == 'B' || move1 == 'W')){
        flipTiles(board, dimension, move2, move3, move1);
        board[move2int][move3int] = move1;
        printf("Valid move.\n");
        printBoard(board, dimension);
    } else {
        printf("Invalid move.\n");
        printBoard(board, dimension);
    }
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

// the function which prints out all valid moves for any colour
void printValidMoves(char board[ ][26], int n, char colour)
{
    // declaring local variables
    int rowCounter;
    int colCounter;
    char row;
    char col;
    
    // nested for loops to go through each row and column of the array
    for(rowCounter = 0; rowCounter < n; rowCounter++){
        for(colCounter = 0; colCounter < n; colCounter++){
            row = (char) (rowCounter + 97);
            col = (char) (colCounter + 97);
            
            // only if the board at the spot is empty, it goes on to call another function to check if it's a valid move
            if(board[rowCounter][colCounter] == 'U'){
                if(checkValidity(board, n, row, col, colour)){
                    
                    // if it is valid, it prints out the move
                    printf("%c%c\n", row, col);
                }
            }
        }
    }
}

// the function which checks whether a move in legal in any specific direction from the position
bool checkLegalInDirection(char board[ ][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{
    // declaring and initializing local variables
    int rowInt = (int) row - 97;
    int colInt = (int) col - 97;
    
    // starting at the specified position, going through the tiles in the specified direction
    for(int rowIntCounter = rowInt, colIntCounter = colInt ; 0 <= rowIntCounter && rowIntCounter < n && 0 <= colIntCounter && colIntCounter < n; rowIntCounter = rowIntCounter + deltaRow, colIntCounter = colIntCounter + deltaCol){
        
        // the checking process varies slightly for white or black, so the program is split into 2 depending on the colour
        if(colour == 'W'){
            // the position right after in the specified direction must be the opposite color
            if(board[rowInt + deltaRow][colInt + deltaCol] == 'B'){
                // then if, in that direction, it is still the opposite color, then you need to go through the loop again and do nothing
                // if you get an unfilled in that direction, the move isn't legal after all
                // if you get end up getting a tile of the same color in that direction, then it is a legal move
                if(board[rowIntCounter + deltaRow][colIntCounter + deltaCol] == 'W'){
                    return true;
                } else if(board[rowIntCounter + deltaRow][colIntCounter + deltaCol] == 'U'){
                    return false;
                }
            }
        } else if(colour == 'B'){
            if(board[rowInt + deltaRow][colInt + deltaCol] == 'W'){
                if(board[rowIntCounter + deltaRow][colIntCounter + deltaCol] == 'B'){
                    return true;
                } else if(board[rowIntCounter + deltaRow][colIntCounter + deltaCol] == 'U'){
                    return false;
                }
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

// the function which flips the tiles when a legal move is placed
void flipTiles(char board[][26], int n, char row, char col, char colour)
{
    // calls another function to both check if it can flip tiles in a ertain direction, and then to actually flip them
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
    
    // making sure that spot is unoccupied right now
    if(board[rowInt][colInt] == 'U'){
        // the function carries out the flip operation for a certain colour, so it needs to specify which colour
        if(colour == 'W'){
            // checks if the move is lega in the inputted direction; if not, it does nothing
            if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
                // if legal, a for loop goes through that direction and flips anything of the opposite colour until it reaches a cell of the same colour
                for(counter = 1; ; counter ++){
                    if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == 'B'){
                        board[rowInt + deltaRow*counter][colInt + deltaCol*counter] = 'W';
                    } else if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == 'W'){
                        return;
                    }
                }
            } else {
                // if not legal, it does nothing
                return;
            }
        } else if(colour == 'B'){
            if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
                for(counter = 1; ; counter ++){
                    if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == 'W'){
                        board[rowInt + deltaRow*counter][colInt + deltaCol*counter] = 'B';
                    } else if(board[rowInt + deltaRow*counter][colInt + deltaCol*counter] == 'B'){
                        return;
                    }
                }
            } else {
                return;
            }
        }
    }
    return;
}