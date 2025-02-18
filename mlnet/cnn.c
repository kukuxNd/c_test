#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 5
#define FILTER_SIZE 3
#define OUTPUT_SIZE (INPUT_SIZE - FILTER_SIZE + 1)

// 卷积操作
void convolution(double input[INPUT_SIZE][INPUT_SIZE], double filter[FILTER_SIZE][FILTER_SIZE], double output[OUTPUT_SIZE][OUTPUT_SIZE]) {
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            output[i][j] = 0.0;
            for (int m = 0; m < FILTER_SIZE; m++) {
                for (int n = 0; n < FILTER_SIZE; n++) {
                    output[i][j] += input[i + m][j + n] * filter[m][n];
                }
            }
        }
    }
}

int main() {
    double input[INPUT_SIZE][INPUT_SIZE] = {
        {1, 1, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0}
    };

    double filter[FILTER_SIZE][FILTER_SIZE] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };

    double output[OUTPUT_SIZE][OUTPUT_SIZE];
    convolution(input, filter, output);

    printf("Output:\n");
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            printf("%f ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}