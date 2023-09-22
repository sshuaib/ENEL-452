#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> 
#include "calculator.h"

Complex addComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = valueInput1.real + valueInput2.real;
    result.imag = valueInput1.imag + valueInput2.imag;
    return result;
}

// Function to subtract two complex numbers
Complex subtractComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = valueInput1.real - valueInput2.real;
    result.imag = valueInput1.imag - valueInput2.imag;
    return result;
}

// Function to multiply two complex numbers
Complex multiplyComplex(Complex valueInput1, Complex valueInput2) {
    Complex result;
    result.real = (valueInput1.real * valueInput2.real) - 
    (valueInput1.imag * valueInput2.imag);
    result.imag = (valueInput1.real * valueInput2.imag) +
    (valueInput1.imag * valueInput2.real);
    return result;
}

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
