#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <jansson.h>

// Function to convert a number from a given base to decimal
unsigned long base_to_decimal(const char* value, int base) {
    unsigned long result = 0;
    int length = strlen(value);
    
    for (int i = 0; i < length; i++) {
        result *= base;
        if (value[i] >= '0' && value[i] <= '9') {
            result += value[i] - '0';
        } else if (value[i] >= 'a' && value[i] <= 'f') {
            result += value[i] - 'a' + 10;
        }
    }
    return result;
}

// Function to find the constant term using Lagrange Interpolation
unsigned long lagrange_interpolation(int n, unsigned long x[], unsigned long y[]) {
    unsigned long result = 0;
    
    for (int i = 0; i < n; i++) {
        unsigned long term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - x[j]);  // We use x = 0 to get the constant term
                term /= (x[i] - x[j]);
            }
        }
        result += term;
    }

    return result;
}

int main() {
    // Test case 1
    json_t *root1;
    json_error_t error1;

    // Load the first test case JSON data
    root1 = json_load_file("testcase1.json", 0, &error1);
    if (!root1) {
        fprintf(stderr, "Error loading JSON file for testcase 1: %s\n", error1.text);
        return 1;
    }

    // Read the 'keys' values
    json_t *keys1 = json_object_get(root1, "keys");
    int n1 = json_integer_value(json_object_get(keys1, "n"));
    int k1 = json_integer_value(json_object_get(keys1, "k"));

    unsigned long x1[n1];
    unsigned long y1[n1];
    
    // Read the root data (from "1" to "n")
    for (int i = 1; i <= n1; i++) {
        char key[10];
        snprintf(key, sizeof(key), "%d", i);

        json_t *root_data = json_object_get(root1, key);
        if (root_data) {
            const char *base_str = json_string_value(json_object_get(root_data, "base"));
            const char *value_str = json_string_value(json_object_get(root_data, "value"));

            int base = atoi(base_str); // Convert base to integer
            unsigned long y_value = base_to_decimal(value_str, base);
            x1[i - 1] = i;  // x values are the keys (1 to n)
            y1[i - 1] = y_value;
        }
    }

    // Calculate the constant term 'c' using Lagrange Interpolation
    unsigned long c1 = lagrange_interpolation(n1, x1, y1);
    printf("Testcase 1: The constant term (c) of the polynomial is: %lu\n", c1);
    
    // Test case 2
    json_t *root2;
    json_error_t error2;

    // Load the second test case JSON data
    root2 = json_load_file("testcase2.json", 0, &error2);
    if (!root2) {
        fprintf(stderr, "Error loading JSON file for testcase 2: %s\n", error2.text);
        return 1;
    }

    // Read the 'keys' values
    json_t *keys2 = json_object_get(root2, "keys");
    int n2 = json_integer_value(json_object_get(keys2, "n"));
    int k2 = json_integer_value(json_object_get(keys2, "k"));

    unsigned long x2[n2];
    unsigned long y2[n2];
    
    // Read the root data (from "1" to "n")
    for (int i = 1; i <= n2; i++) {
        char key[10];
        snprintf(key, sizeof(key), "%d", i);

        json_t *root_data = json_object_get(root2, key);
        if (root_data) {
            const char *base_str = json_string_value(json_object_get(root_data, "base"));
            const char *value_str = json_string_value(json_object_get(root_data, "value"));

            int base = atoi(base_str); // Convert base to integer
            unsigned long y_value = base_to_decimal(value_str, base);
            x2[i - 1] = i;  // x values are the keys (1 to n)
            y2[i - 1] = y_value;
        }
    }

    // Calculate the constant term 'c' using Lagrange Interpolation
    unsigned long c2 = lagrange_interpolation(n2, x2, y2);
    printf("Testcase 2: The constant term (c) of the polynomial is: %lu\n", c2);
    
    // Free the JSON object
    json_decref(root1);
    json_decref(root2);
    
    return 0;
}
