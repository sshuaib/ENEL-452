#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "calculator.h"

int main() {
    Complex valueInput1, valueInput2, result;
    char input[100];
    char x[200];
    char choice;
    bool error = false;

    //fprintf("Enter exp (a + bi): ");
    //scanf("%lf %lf", &valueInput2.real, &valueInput2.imag);

    while (1) {
        fprintf(stderr, "Enter exp: ");
        fgets (input, sizeof(input), stdin);
        sscanf(input, " %c ", &choice);

        if(choice == 'q' || choice == 'Q' )
        {
            break;
        }

        if (sscanf(input, " %*c %lf %lf %lf %lf", &valueInput1.real, &valueInput1.imag, &valueInput2.real, &valueInput2.imag) < 4) 
        { 
            fprintf(stdout, "error code: 2: missing arguments\n");
            error = true;
            continue;
        }

        else if (sscanf(input, " %*c %lf %lf %lf %lf %100s", &valueInput1.real, &valueInput1.imag, &valueInput2.real, &valueInput2.imag, input) > 4)
        {
            fprintf(stdout, "error code: 3: extra arguments\n");
            error = true;
            continue;
        }

        else if (sscanf(input, " %*c %lf %lf %lf %lf", &valueInput1.real, &valueInput1.imag, &valueInput2.real, &valueInput2.imag) == 4)
        {
            switch (choice) {
            case 'a':
            case 'A':
                result = addComplex(valueInput1, valueInput2);
                fprintf(stdout, "%lf + j %lf\n", result.real, result.imag);
                continue;

            case 's':
            case 'S':
                result = subtractComplex(valueInput1, valueInput2);
                fprintf(stdout, "%lf + j %lf\n", result.real, result.imag);
                continue;

            case 'm':
            case 'M':
                result = multiplyComplex(valueInput1, valueInput2);
                fprintf(stdout,  "%lf + j %lf\n", result.real, result.imag);
                continue;

            case 'd':
            case 'D':
                    if(valueInput2.real == 0 & valueInput2.imag == 0)
                    {
                        fprintf(stdout, "error code: 4: divide by zero\n" );
                        error = true;
                        continue;
                    }

                result = divideComplex(valueInput1, valueInput2);
                fprintf(stdout, "%lf + j %lf\n", result.real, result.imag);
                continue;

            default:
                error = true;
                fprintf(stdout, "error code: 1: illegal command\n");
                continue;
        }
        /*if(!error) 
        {
            if (result.imag >= 0)
            {
                fprintf(stdout,"%.6lf + j %.6lf\n", result.real, result.imag);
            }
             else
            {
                fprintf(stdout,"%.6lf - j %.6lf\n", result.real, -result.imag);
            }   
        }*/
        error = false;
        
    }

    return 0;
}
}
