#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NODES 4
#define FEATURES 3
#define HIDDEN_DIM 2

// 激活函数：sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 图卷积层
void gcn_layer(double input[NODES][FEATURES], double output[NODES][HIDDEN_DIM], double weights[FEATURES][HIDDEN_DIM], double adjacency[NODES][NODES]) {
    for (int i = 0; i < NODES; i++) {
        for (int j = 0; j < HIDDEN_DIM; j++) {
            output[i][j] = 0.0;
            for (int k = 0; k < NODES; k++) {
                if (adjacency[i][k] > 0) {
                    for (int l = 0; l < FEATURES; l++) {
                        output[i][j] += input[k][l] * weights[l][j];
                    }
                }
            }
            output[i][j] = sigmoid(output[i][j]);
        }
    }
}

int main() {
    double input[NODES][FEATURES] = {
        {1.0, 0.5, -1.0},
        {0.5, 1.0, 0.0},
        {0.0, 0.5, -0.5},
        {1.0, 0.0, 1.0}
    };

    double adjacency[NODES][NODES] = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}
    };

    double weights[FEATURES][HIDDEN_DIM] = {
        {0.1, 0.2},
        {-0.1, 0.3},
        {0.4, 0.1}
    };

    double output[NODES][HIDDEN_DIM];
    gcn_layer(input, output, weights, adjacency);

    printf("Output:\n");
    for (int i = 0; i < NODES; i++) {
        for (int j = 0; j < HIDDEN_DIM; j++) {
            printf("%f ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}