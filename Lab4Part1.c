#include <stdio.h>

int main(void)
{
	// declaring variables for number of rows desired, as well as variables to count rows and columns during the for loops
    int rows, rowCounter, columnCounter;
    
    // prompting the user for the number of rows input and then scanning it
    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &rows);
    
    // the for loop within which the whole triangle is drawn
    for(rowCounter = 1; rowCounter <= rows; rowCounter++){
        
        // when it isn't at the final row, printing the current number of spaces as well as the '^' where necessary
        if(rowCounter < rows){
            for(columnCounter = 1; columnCounter <= (2*rows - 1); columnCounter++){
                if(columnCounter == (rows - rowCounter + 1) || columnCounter == (2*rows - 1 - (rows - rowCounter))){
                    printf("^");
                } else if(columnCounter == 2*rows - 1){
                    printf(" \n");
                } else{
                    printf(" ");
                }
            }
            
            // at the final row, printing the correct number of '^' based on the pattern
        } else if(rowCounter == rows){
            for(columnCounter = 1; columnCounter <= (2*rows-1); columnCounter++){
                printf("^");
            }
        }
    }
	return 0;
}
