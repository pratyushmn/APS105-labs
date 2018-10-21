#include <stdio.h>
#include <math.h>

// declaring the two function which will be called in the main function
long convertDecimalToBinary(long decimalInput);
long convertBinaryToDecimal(long binaryInput);

int main(void)
{
    // declaring the variables used in the main function
    char conversion;
    long input;
    long output;
    
    // prompting the user to choose which direction the conversion will take and which number will be converted
    printf("Enter B for conversion of Binary to Decimal, OR\nEnter D for conversion of Decimal to Binary: ");
    scanf("%c", &conversion);
    printf("Enter your number: ");
    scanf("%ld", &input);
    
    // deciding whether to convert from Binary to Decimal or Decimal to Binary based on user's input
    // calling the other function to do the conversion
    // printing out the original number as well as the converted number
    if(conversion == 'B'){
        output = (int)convertBinaryToDecimal(input);
        printf("%ld in binary = %ld in decimal", input, output);
    } else if(conversion == 'D'){
        output = (int)convertDecimalToBinary(input);
        printf("%ld in decimal = %ld in binary", input, output);
    } else{
        printf("Invalid input; Goodbye");
    }

	return 0;
}

// function to convert decimal to binary
long convertDecimalToBinary(long decimalInput)
{
    // declaring variables which will be used in this function
    long remainder = 0, binary = 0, decimalCounter = 0;
    int powerCounter = 0;
    
    // the for loop goes through the method used for converting decimals to binary
    for(decimalCounter = decimalInput; decimalCounter >= 1; decimalCounter = decimalCounter/2){
            remainder = (long) fmod((double) decimalCounter, 2.0);
            binary = binary + remainder*pow(10.0, (double) powerCounter);
            powerCounter = powerCounter + 1;
        }
        
        // returning the binary number
        return (long) binary;
}

// function to convert binary to decimal
long convertBinaryToDecimal(long binaryInput)
{
    // declaring variables which will be used in this function
    long remainder = 0, decimal = 0, binaryCounter = 0;
    int powerCounter = 0;
    
    // the for loop goes through the method used for converting binary to decimals
    for(binaryCounter = binaryInput; binaryCounter >= 1; binaryCounter = binaryCounter/10){
            remainder = (long) fmod((double) binaryCounter, 10.0);
            decimal = decimal + remainder*pow(2.0, (double) powerCounter);
            powerCounter = powerCounter + 1;
        }
        
        // returning the decimal number
        return (long) decimal;
}