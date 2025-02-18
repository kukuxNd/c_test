#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 3
#define HIDDEN_NODES 3
#define OUTPUT_NODES 1

// 激活函数：sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 前向传播
void feedforward(double input[INPUT_NODES], double hidden[HIDDEN_NODES], double output[OUTPUT_NODES],
                 double input_hidden_weights[INPUT_NODES][HIDDEN_NODES], double hidden_output_weights[HIDDEN_NODES][OUTPUT_NODES]) {
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden[i] = 0.0;
        for (int j = 0; j < INPUT_NODES; j++) {
            hidden[i] += input[j] * input_hidden_weights[j][i];
        }
        hidden[i] = sigmoid(hidden[i]);
    }

    for (int i = 0; i < OUTPUT_NODES; i++) {
        output[i] = 0.0;
        for (int j = 0; j < HIDDEN_NODES; j++) {
            output[i] += hidden[j] * hidden_output_weights[j][i];
        }
        output[i] = sigmoid(output[i]);
    }
}

int main() {
    double input[INPUT_NODES] = {1.0, 0.5, -1.0};
    double hidden[HIDDEN_NODES];
    double output[OUTPUT_NODES];

    double input_hidden_weights[INPUT_NODES][HIDDEN_NODES] = {
        {0.1, 0.2, -0.1},
        {-0.1, 0.1, 0.9},
        {0.1, 0.4, 0.1}
    };

    double hidden_output_weights[HIDDEN_NODES][OUTPUT_NODES] = {
        {0.3},
        {0.1},
        {-0.2}
    };

    feedforward(input, hidden, output, input_hidden_weights, hidden_output_weights);

    printf("Output: %f\n", output[0]);

    return 0;
}