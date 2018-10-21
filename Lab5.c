#include <stdio.h>

// declaring the 3 functions to be used later in the code
void triangle (int numRows);
int choose(int n, int r);
long long factorial(int n);

// the main function
int main(void)
{
    // declaring the local variables for the main function
    int rows;
    
    // a do-while loop so that the code keeps running as long as the inputs are valid
    do{
        
        // prompting the user for their input and then scanning it
        printf("Enter the number of rows: ");
        scanf("%d", &rows);
        
        // calling the triangle function to print out Pascal's Triangle with the desired number of rows
        triangle(rows);

    } while(rows >= 0);
    return 0;
}

// the triangle function which actually prints out Pascal's Triangle
void triangle(int numRows)
{
    //intializing the local variables for this function
    int spaceCounter, rowCounter, r, chosen;
    
    // if 0 rows are desired then nothing is printed
    if(numRows == 0){
        return;
    }

    // a for loop to print out the required spaces and numbers for each row
    for(rowCounter = 1; rowCounter <= numRows; rowCounter++){
        
        // a for loop to print out the initial spaces before the numbers
        for(spaceCounter = 0; spaceCounter < ((6*(numRows - 1)+1)/2 + 1) - 3*(rowCounter - 1) - 1; spaceCounter++){
               printf(" ");
        }
        
        // a for loop to print out the numbers as 6 characters: the actual number and then spaces to the right as padding
        for(r = 0; r <= rowCounter - 1; r++){
               chosen = choose(rowCounter - 1, r);
               printf("%-6d", chosen);
        }
        
        // when all the numbers are printed out move to a new line
        printf("\n");
    }
    
    // since this function returns a void, it returns nothing
    return;
}

// the choose function to perform the mathematical operation
int choose(int n, int r)
{
    // initializing the local variable
    int ans;
    
    // computing and returning the answer
    ans = (factorial(n))/((factorial(r))*(factorial(n-r)));
    return ans;
}

// the factorial function to perform the mathematical operation
long long factorial(int n)
{
    // initializing the local variable
    long long factorialAns = 1;
    
    // Computing the answer
    if(n == 0){
        return 1;
    } else{
        for(int counter = 1; counter <= n; counter++){
        factorialAns = factorialAns*counter;
        }
    }
    // returning the answer
    return factorialAns;
}