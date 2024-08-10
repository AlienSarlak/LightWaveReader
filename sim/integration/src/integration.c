#include "include/integration.h"
#include <stdio.h>

// Function to implement Trapezoidal Rule
float trapezoidal(float arr[], int n, float a, float b) {
    float h = (b - a) / n;
    float sum = arr[0] + arr[n];

    for (int i = 1; i < n; i++) {
        sum += 2 * arr[i];
    }

    return (h / 2) * sum;
}

// Function to implement Midpoint Rule
float midpoint(float arr[], int n, float a, float b) {
    float h = (b - a) / n;
    float sum = 0.0;

    for (int i = 0; i < n; i++) {
        float mid_point = (arr[i] + arr[i+1]) / 2.0;
        sum += mid_point;
    }

    return h * sum;
}

// Function to implement Simpson's Rule
float simpsons(float arr[], int n, float a, float b) {
    if (n % 2 != 0) {
        printf("n must be even for Simpson's rule\n");
        return -1;
    }

    float h = (b - a) / n;
    float sum = arr[0] + arr[n];

    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            sum += 2 * arr[i];
        } else {
            sum += 4 * arr[i];
        }
    }

    return (h / 3) * sum;
}
