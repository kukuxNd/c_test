#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

// Function to print a matrix
void print_matrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to add two matrices
void add_matrices(int matrix1[ROWS][COLS], int matrix2[ROWS][COLS], int result[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Function to multiply two matrices
void multiply_matrices(int matrix1[ROWS][COLS], int matrix2[ROWS][COLS], int result[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COLS; k++) {
                result[i][j] += matrix1[i][k] * matrix2[i][j];
            }
        }
    }
}

// Function to transpose a matrix
void transpose_matrix(int matrix[ROWS][COLS], int result[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

int main() {
    int matrix1[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int matrix2[ROWS][COLS] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int result[ROWS][COLS];

    printf("Matrix 1:\n");
    print_matrix(matrix1);
    printf("\n");

    printf("Matrix 2:\n");
    print_matrix(matrix2);
    printf("\n");

    // Add matrices
    add_matrices(matrix1, matrix2, result);
    printf("Sum of matrices:\n");
    print_matrix(result);
    printf("\n");

    // Multiply matrices
    multiply_matrices(matrix1, matrix2, result);
    printf("Product of matrices:\n");
    print_matrix(result);
    printf("\n");

    // Transpose matrix1
    transpose_matrix(matrix1, result);
    printf("Transpose of Matrix 1:\n");
    print_matrix(result);
    printf("\n");

    return 0;
}