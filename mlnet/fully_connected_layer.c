#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 3
#define HIDDEN_NODES 4
#define OUTPUT_NODES 2

// 激活函数：ReLU
double relu(double x) {
    return fmax(0, x);
}

// 前向传播
void fully_connected_layer(double input[INPUT_NODES], double output[HIDDEN_NODES], double weights[INPUT_NODES][HIDDEN_NODES], double biases[HIDDEN_NODES]) {
    for (int i = 0; i < HIDDEN_NODES; i++) {
        output[i] = biases[i];
        for (int j = 0; j < INPUT_NODES; j++) {
            output[i] += input[j] * weights[j][i];
        }
        output[i] = relu(output[i]);
    }
}

int main() {
    double input[INPUT_NODES] = {1.0, 0.5, -1.0};
    double output[HIDDEN_NODES];

    double weights[INPUT_NODES][HIDDEN_NODES] = {
        {0.1, 0.2, -0.1, 0.4},
        {-0.1, 0.1, 0.9, -0.3},
        {0.1, 0.4, 0.1, 0.2}
    };

    double biases[HIDDEN_NODES] = {0.1, 0.2, 0.3, 0.4};

    fully_connected_layer(input, output, weights, biases);

    printf("Output:\n");
    for (int i = 0; i < HIDDEN_NODES; i++) {
        printf("%f\n", output[i]);
    }

    return 0;
}