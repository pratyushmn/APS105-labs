#include <stdio.h> // include C standard library commands
#include <math.h> // include mathematics related functions and commands

int main(void)
{
	double input1, input2, input3; // declaring variables for the three user inputs
    printf("Enter three input numbers: ");
    scanf("%lf %lf %lf", &input1, &input2, &input3); // scanning user inputs into the aforementioned variables
    double mean, variance, stdDev; // declaring variables to store the final answers after the computations are complete
    mean = (input1 + input2 + input3)/3; // calculating the mean of the inputs based on the definition of the mean
    variance = (pow(input1 - mean, 2) + pow(input2 - mean, 2) + pow(input3 - mean, 2))/2; // calculating the variance of the inputs based on the definition of variance
    stdDev = sqrt(variance); // calculating standard deviation of the inputs based on the definition of standard deviation and the previously calculated variance
    printf("The mean is %.2lf and the standard deviation is %.2lf", mean, stdDev); // displaying the computed information to the user
	return 0;
}
