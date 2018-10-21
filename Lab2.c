#include <stdio.h>

int main(void)
{
	// Declaring the variables which will be used in this program
    char firstBand;
    char secondBand;
    char multiplier; 
    char tolerance;
    double resistance;
    double uncertainty;
    
    // Prompting the user to input the bands of the resistor
    printf("Please enter the 1st band: \n");
    scanf("%c", &firstBand);
    printf("Please enter the 2nd band: \n");
    scanf(" %c", &secondBand);
    printf("Please enter the multiplier band: \n");
    scanf(" %c", &multiplier);
    printf("Please enter the tolerance band: \n");
    scanf(" %c", &tolerance);
    
    printf("Resistor Bands: ");
    
    // Converting the user input for the resistor's first band into a numerical value, as well as printing out the color of the first band
    if(firstBand == 'K' || firstBand == 'k'){
        resistance = 0*10;
        printf("Black ");
    } else if(firstBand == 'B' || firstBand == 'b'){
        resistance = 1*10;
        printf("Brown ");
    } else if(firstBand == 'R' || firstBand == 'r'){
        resistance = 2*10;
        printf("Red ");
    } else if(firstBand == 'O' || firstBand == 'o'){
        resistance = 3*10;
        printf("Orange ");
    } else if(firstBand == 'E' || firstBand == 'e'){
        resistance = 4*10;
        printf("Yellow ");
    } else if(firstBand == 'G' || firstBand == 'g'){
        resistance = 5*10;
        printf("Green ");
    } else if(firstBand == 'U' || firstBand == 'u'){
        resistance = 6*10;
        printf("Blue ");
    } else if(firstBand == 'V' || firstBand == 'v'){
        resistance = 7*10;
        printf("Violet ");
    } else if(firstBand == 'Y' || firstBand == 'y'){
        resistance = 8*10;
        printf("Grey ");
    } else if(firstBand == 'W' || firstBand == 'w'){
        resistance = 9*10;
        printf("White ");
    } else{
        printf("\nThe input for the first resistor band was invalid. Please restart the program and try again.\n");
        return 0;
    }
    
    // Converting the user input for the resistor's second band into a numerical value, as well as printing out the color of the second band
    if(secondBand == 'K' || secondBand == 'k'){
        resistance = resistance + 0;
        printf("Black ");
    } else if(secondBand == 'B' || secondBand == 'b'){
        resistance = resistance + 1;
        printf("Brown ");
    } else if(secondBand == 'R' || secondBand == 'r'){
        resistance = resistance + 2;
        printf("Red ");
    } else if(secondBand == 'O' || secondBand == 'o'){
        resistance = resistance + 3;
        printf("Orange ");
    } else if(secondBand == 'E' || secondBand == 'e'){
        resistance = resistance + 4;
        printf("Yellow ");
    } else if(secondBand == 'G' || secondBand == 'g'){
        resistance = resistance + 5;
        printf("Green ");
    } else if(secondBand == 'U' || secondBand == 'u'){
        resistance = resistance + 6;
        printf("Blue ");
    } else if(secondBand == 'V' || secondBand == 'v'){
        resistance = resistance + 7;
        printf("Violet ");
    } else if(secondBand == 'Y' || secondBand == 'y'){
        resistance = resistance + 8;
        printf("Grey ");
    } else if(secondBand == 'W' || secondBand == 'w'){
        resistance = resistance + 9;
        printf("White ");
    } else{
        printf("\nThe input for the second resistor band was invalid. Please restart the program and try again.\n");
        return 0;
    }    
    
    // Converting the user input for the resistor's multiplier band into a numerical value, as well as printing out the color of the multiplier band
    if(multiplier == 'K' || multiplier == 'k'){
        resistance = resistance;
        printf("Black ");
    } else if(multiplier == 'B' || multiplier == 'b'){
        resistance = resistance*10;
        printf("Brown ");
    } else if(multiplier == 'R' || multiplier == 'r'){
        resistance = resistance*100;
        printf("Red ");
    } else if(multiplier == 'O' || multiplier == 'o'){
        resistance = resistance*1000;
        printf("Orange ");
    } else if(multiplier == 'E' || multiplier == 'e'){
        resistance = resistance*10000;
        printf("Yellow ");
    } else if(multiplier == 'G' || multiplier == 'g'){
        resistance = resistance*100000;
        printf("Green ");
    } else if(multiplier == 'U' || multiplier == 'u'){
        resistance = resistance*1000000;
        printf("Blue ");
    } else if(multiplier == 'V' || multiplier == 'v'){
        resistance = resistance*10000000;
        printf("Violet ");
    } else if(multiplier == 'L' || multiplier == 'l'){
        resistance = resistance*0.1;
        printf("Gold ");
    } else if(multiplier == 'S' || multiplier == 's'){
        resistance = resistance*0.01;
        printf("Silver ");
    } else{
        printf("\nThe input for the multiplier resistor band was invalid. Please restart the program and try again.\n");
        return 0;
    }
    
    // Converting the user input for the resistor's tolerance band into a numerical value, as well as printing out the color of the tolerance band
    if(tolerance == 'B' || tolerance == 'b'){
        uncertainty = 1;
        printf("Brown ");
    } else if(tolerance == 'R' || tolerance == 'r'){
        uncertainty = 2;
        printf("Red ");
    } else if(tolerance == 'G' || tolerance == 'g'){
        uncertainty = 0.5;
        printf("Green ");
    } else if(tolerance == 'U' || tolerance == 'u'){
        uncertainty = 0.25;
        printf("Blue ");
    } else if(tolerance == 'V' || tolerance == 'v'){
        uncertainty = 0.10;
        printf("Violet ");
    } else if(tolerance == 'Y' || tolerance == 'y'){
        uncertainty = 0.05;
        printf("Grey "); 
    } else if(tolerance == 'L' || tolerance == 'l'){
        uncertainty = 5;
        printf("Gold ");
    } else if(tolerance == 'S' || tolerance == 's'){
        uncertainty = 10;
        printf("Silver ");
    } else{
        printf("\nThe input for the tolerance resistor band was invalid. Please restart the program and try again.\n");
        return 0;
    }    
    
    printf("\n");
    
    // Printing out the final resistance and uncertainty values, as well as figuring out whether to use MOhms, KOhms, or just Ohms for the units
    if(resistance >= 1000000){
        resistance = resistance/1000000;
        printf("Resistance: %.2lf MOhms +/- %.2lf%%", resistance, uncertainty);
    } else if(resistance >= 1000){
        resistance = resistance/1000;
        printf("Resistance: %.2lf KOhms +/- %.2lf%%", resistance, uncertainty);
    } else{
        printf("Resistance: %.2lf Ohms +/- %.2lf%%", resistance, uncertainty);
    }
	return 0;
}