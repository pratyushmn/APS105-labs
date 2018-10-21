#include <stdio.h>

int main(void)
{
    // initializing the variables to be used in this program
	int input;
    int quarters, dimes, nickels, cents;
    
    // prompting for a user input and then scanning it
    printf("Please give an amount in cents less than 100: ");
    scanf("%d", &input);
    
    // a while loop to make sure the code keeps running until an invalid input is entered
    while(input > 0 && input <= 99) {
        
        // printing the first part of the final output statement
        printf("%d cents: ", input);
        
        // figuring out how many quarters, dimes, nickels, and cents will be needed to add up to the input value
        int quarters = input/25;       
        int dimes = (input - quarters*25)/10;
        int nickels = (input - quarters*25 - dimes*10)/5;
        int cents = (input - quarters*25 - dimes*10 - nickels*5);
        
        // if and else statements in order to print an output statement which
        // is correct grammatically and also only includes the coins which are needed
        if(cents == 0 && nickels == 0 && dimes == 0){
            if(quarters == 1){
                printf("%d quarter.", quarters);
            } else if(quarters > 1){
                printf("%d quarters.", quarters);
            }
        } else if(cents == 0 && nickels == 0){
                if(quarters == 1){
                    printf("%d quarter, ", quarters);
                } else if(quarters > 1){
                    printf("%d quarters, ", quarters);
                }  
                if (dimes == 1){
                    printf("%d dime.", dimes);
                } else if(dimes > 1){
                    printf("%d dimes.", dimes);
                }
        } else if(cents == 0){
            if(quarters == 1){
                printf("%d quarter, ", quarters);
            } else if(quarters > 1){
                printf("%d quarters, ", quarters);
            }      
            if(dimes == 1){
                printf("%d dime, ", dimes);
            } else if(dimes > 1){
                printf("%d dimes, ", dimes);
            }        
            if(nickels == 1){
                printf("%d nickel.", nickels);
            } else if(nickels > 1){
                printf("%d nickels.", nickels);
            }            
        } else{
            if(quarters == 1){
                printf("%d quarter, ", quarters);
            } else if(quarters > 1){
                printf("%d quarters, ", quarters);
            }    
            if(dimes == 1){
                printf("%d dime, ", dimes);
            } else if(dimes > 1){
                printf("%d dimes, ", dimes);
            }        
            if(nickels == 1){
                printf("%d nickel, ", nickels);
            } else if(nickels > 1){
                printf("%d nickels, ", nickels);
            }
            if(cents == 1){
                printf("%d cent.", cents);
            } else if(cents > 1){
                printf("%d cents.", cents);
            }
        }
        
        // creating a new line before prompting for another input
        printf("\n");
        
        // prompting the user and scanning for another input
        printf("Please give an amount in cents less than 100: ");
        scanf("%d", &input);
    }
    
    printf("Goodbye.");
	return 0;
}