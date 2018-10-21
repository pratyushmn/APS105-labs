#include <stdio.h>

int main(void)
{
    // initializing the variables to be used in the program
	double firstNumber, secondNumber, ans;
    char operation;
    
    // scanning for the required inputs from the user
    printf("Enter first number: ");
    scanf("%lf", &firstNumber);
    printf("Enter second number: ");
    scanf("%lf", &secondNumber);
    printf("Enter calculation command (one of a, s, m, or d): ");
    scanf(" %c", &operation);
    
    // using if and else statements to decide which operation to carry out based on the user input    
    if(operation == 'a') {
        ans = firstNumber + secondNumber;
        printf("Sum of %.2lf and %.2lf is %.2lf\n", firstNumber, secondNumber, ans);
    } else if(operation == 's') {
        ans = firstNumber - secondNumber;
        printf("Difference of %.2lf from %.2lf is %.2lf\n", firstNumber, secondNumber, ans);
    } else if(operation == 'm') {
        ans = firstNumber * secondNumber;
        printf("Product of %.2lf and %.2lf is %.2lf\n", firstNumber, secondNumber, ans);
    } else if(operation == 'd') {
        if(secondNumber == 0) {
            printf("Error, trying to divide by zero\n");
        }
        else {
            ans = firstNumber / secondNumber;
            printf("Division of %.2lf by %.2lf is %.2lf\n", firstNumber, secondNumber, ans);
        }
    } else {
        printf("Error, unknown calculation command given\n");
        return 0;
   }
        
	return 0;
}
