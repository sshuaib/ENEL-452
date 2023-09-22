/*
Name: Salman Shuaib
SID: 200374212
Date: Sept 21, 2023
Assignment 1
Karim Naqvi
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> 
#include "calculator.h"

/*
Function Header 1: Complex addComplex

Adds two complex numbers. Adding the real values and imaginary values separate.
*/

Complex addComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = valueInput1.real + valueInput2.real;
    result.imag = valueInput1.imag + valueInput2.imag;
    return result;
}

/*
Function Header 2: Complex subtractComplex

Subtracts two complex numbers. Subtracting the real values and imaginary values separate.
*/

// Function to subtract two complex numbers
Complex subtractComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = valueInput1.real - valueInput2.real;
    result.imag = valueInput1.imag - valueInput2.imag;
    return result;
}

/*
Function Header 3: Complex multiplyComplex

This function takes two Complex structures (valueInput1 and valueInput2) as input arguments and returns a Complex structure as the result.
*/

// Function to multiply two complex numbers
Complex multiplyComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = (valueInput1.real * valueInput2.real) - 
    (valueInput1.imag * valueInput2.imag);
    result.imag = (valueInput1.real * valueInput2.imag) +
    (valueInput1.imag * valueInput2.real);
    return result;
}

/*
Function Header 4: Complex divideComplex

This function takes two Complex structures (valueInput1 and valueInput2) as input arguments and returns a Complex structure as the result.
*/

// Function to divide two complex numbers
Complex divideComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = ((valueInput1.real * valueInput2.real) +
     (valueInput1.imag * valueInput2.imag)) 
    / ((valueInput2.real * valueInput2.real) +
     (valueInput2.imag * valueInput2.imag));

    result.imag = ((valueInput1.imag * valueInput2.real) -
     (valueInput1.real * valueInput2.imag)) 
    / ((valueInput2.real * valueInput2.real) +
     (valueInput2.imag * valueInput2.imag));
    return result;
}
