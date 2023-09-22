#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Define a structure to represent complex numbers with real and imaginary parts.
typedef struct {
    double real; // Real part of the complex number.
    double imag; // Imaginary part of the complex number.
} Complex;

// Function prototypes for complex number operations:

// Function to add two complex numbers.
Complex addComplex(Complex valueInput1, Complex valueInput2);

// Function to subtract one complex number from another.
Complex subtractComplex(Complex valueInput1, Complex valueInput2);

// Function to multiply two complex numbers.
Complex multiplyComplex(Complex valueInput1, Complex valueInput2);

// Function to divide one complex number by another.
Complex divideComplex(Complex valueInput1, Complex valueInput2);
