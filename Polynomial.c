#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to convert a number from a given base to decimal
int base_to_decimal(const char* value, int base) {
    int result = 0;
    int length = strlen(value);
    
    for (int i = 0; i < length; i++) {
        result *= base;
        if (value[i] >= '0' && value[i] <= '9') {
            result += value[i] - '0';
        } else if (value[i] >= 'A' && value[i] <= 'F') {
            result += value[i] - 'A' + 10;
        }
    }
    return result;
}

// Function to find the constant term using Lagrange Interpolation
int lagrange_interpolation(int n, int x[], int y[]) {
    int result = 0;
    
    for (int i = 0; i < n; i++) {
        int term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - x[j]); // We use x = 0 because we want to find f(0)
                term /= (x[i] - x[j]);
            }
        }
        result += term;
    }

    return result;
}

int main() {
    // Sample input (as JSON parsed manually)
    int n = 4; // Number of roots
    int x[] = {1, 2, 3, 6}; // x values (keys)
    char* values[] = {"4", "111", "12", "213"}; // y values in base format
    int y[4]; // Array to store decoded y values
    
    // Decode the y values from the given bases
    for (int i = 0; i < n; i++) {
        int base;
        if (i == 0) base = 10;
        else if (i == 1) base = 2;
        else if (i == 2) base = 10;
        else base = 4;

        y[i] = base_to_decimal(values[i], base);
    }

    // Calculate the constant term 'c' using Lagrange Interpolation
    int c = lagrange_interpolation(n, x, y);

    // Output the result
    printf("The constant term (c) of the polynomial is: %d\n", c);
    
    return 0;
}
