#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "calculator.h"  // Includes a user-defined header file for complex number operations.

int main() {
    Complex valueInput1, valueInput2, result; // Declare variables to store complex numbers.
    char input[100]; // Initialize a character array to store user input.
    char choice; // Initialize a character to store the user's choice.
    bool error = false; // Initialize a boolean variable to track errors.

    // Prompt the user for input in a loop until they choose to quit ('q' or 'Q').
    while (1) {
        fprintf(stderr, "Enter exp: "); // Prompt the user for input.
        fgets(input, sizeof(input), stdin); // Read input from the user.
        sscanf(input, " %c ", &choice); // Extract the first character as the user's choice.

        if (choice == 'q' || choice == 'Q') {
            break; // If the user chooses to quit, exit the loop.
        }

        // Check if the input contains fewer than 4 floating-point numbers (real and imaginary parts).
        if (sscanf(input, " %*c %lf %lf %lf %lf", &valueInput1.real, &valueInput1.imag, &valueInput2.real, &valueInput2.imag) < 4) {
            fprintf(stdout, "error code: 2: missing arguments\n");
            error = true; // Set the error flag and continue to the next iteration.
            continue;
        } else if (sscanf(input, " %*c %lf %lf %lf %lf %100s", &valueInput1.real, &valueInput1.imag, &valueInput2.real, &valueInput2.imag, input) > 4) {
            fprintf(stdout, "error code: 3: extra arguments\n");
            error = true; // Set the error flag and continue to the next iteration.
            continue;
        } else if (sscanf(input, " %*c %lf %lf %lf %lf", &valueInput1.real, &valueInput1.imag, &valueInput2.real, &valueInput2.imag) == 4) {
            // If the input is valid and contains four floating-point numbers, perform complex number operations.
            switch (choice) {
                case 'a':
                case 'A':
                    result = addComplex(valueInput1, valueInput2); // Call a function to add two complex numbers.
                    fprintf(stdout, "%lf + j %lf\n", result.real, result.imag); // Print the result.
                    continue; // Continue to the next iteration of the loop.

                case 's':
                case 'S':
                    result = subtractComplex(valueInput1, valueInput2); // Call a function to subtract two complex numbers.
                    fprintf(stdout, "%lf + j %lf\n", result.real, result.imag); // Print the result.
                    continue; // Continue to the next iteration of the loop.

                case 'm':
                case 'M':
                    result = multiplyComplex(valueInput1, valueInput2); // Call a function to multiply two complex numbers.
                    fprintf(stdout,  "%lf + j %lf\n", result.real, result.imag); // Print the result.
                    continue; // Continue to the next iteration of the loop.

                case 'd':
                case 'D':
                    if (valueInput2.real == 0 && valueInput2.imag == 0) {
                        fprintf(stdout, "error code: 4: divide by zero\n" );
                        error = true; // Set the error flag and continue to the next iteration.
                        continue;
                    }

                    result = divideComplex(valueInput1, valueInput2); // Call a function to divide two complex numbers.
                    fprintf(stdout, "%lf + j %lf\n", result.real, result.imag); // Print the result.
                    continue; // Continue to the next iteration of the loop.

                default:
                    error = true;
                    fprintf(stdout, "error code: 1: illegal command\n"); // Handle an invalid command.
                    continue; // Continue to the next iteration of the loop.
            }
        }
        error = false; // Reset the error flag.
    }

    return 0; // Exit the program.
}
