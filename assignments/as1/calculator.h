#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    double real;
    double imag;
} Complex;

// Function prototypes for complex number operations
Complex addComplex(Complex valueInput1, Complex valueInput2);
Complex subtractComplex(Complex valueInput1, Complex valueInput2);
Complex multiplyComplex(Complex valueInput1, Complex valueInput2);
Complex divideComplex(Complex valueInput1, Complex valueInput2);
