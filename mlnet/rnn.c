#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 3
#define HIDDEN_NODES 3
#define OUTPUT_NODES 1
#define TIME_STEPS 5

// 激活函数：sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 前向传播
void rnn_forward(double input[TIME_STEPS][INPUT_NODES], double hidden[HIDDEN_NODES],
                 double output[TIME_STEPS][OUTPUT_NODES], double input_hidden_weights[INPUT_NODES][HIDDEN_NODES],
                 double hidden_hidden_weights[HIDDEN_NODES][HIDDEN_NODES], double hidden_output_weights[HIDDEN_NODES][OUTPUT_NODES]) {
    for (int t = 0; t < TIME_STEPS; t++) {
        double new_hidden[HIDDEN_NODES] = {0};

        for (int i = 0; i < HIDDEN_NODES; i++) {
            new_hidden[i] = 0.0;
            for (int j = 0; j < INPUT_NODES; j++) {
                new_hidden[i] += input[t][j] * input_hidden_weights[j][i];
            }
            for (int j = 0; j < HIDDEN_NODES; j++) {
                new_hidden[i] += hidden[j] * hidden_hidden_weights[j][i];
            }
            new_hidden[i] = sigmoid(new_hidden[i]);
        }

        for (int i = 0; i < HIDDEN_NODES; i++) {
            hidden[i] = new_hidden[i];
        }

        for (int i = 0; i < OUTPUT_NODES; i++) {
            output[t][i] = 0.0;
            for (int j = 0; j < HIDDEN_NODES; j++) {
                output[t][i] += hidden[j] * hidden_output_weights[j][i];
            }
            output[t][i] = sigmoid(output[t][i]);
        }
    }
}

int main() {
    double input[TIME_STEPS][INPUT_NODES] = {
        {1.0, 0.5, -1.0},
        {0.5, 1.0, -0.5},
        {0.0, 0.5, -0.5},
        {0.5, 1.0, 0.0},
        {1.0, 0.5, 0.5}
    };

    double hidden[HIDDEN_NODES] = {0};
    double output[TIME_STEPS][OUTPUT_NODES];

    double input_hidden_weights[INPUT_NODES][HIDDEN_NODES] = {
        {0.1, 0.2, -0.1},
        {-0.1, 0.1, 0.9},
        {0.1, 0.4, 0.1}
    };

    double hidden_hidden_weights[HIDDEN_NODES][HIDDEN_NODES] = {
        {0.3, 0.1, -0.2},
        {0.2, -0.3, 0.1},
        {0.1, 0.2, 0.3}
    };

    double hidden_output_weights[HIDDEN_NODES][OUTPUT_NODES] = {
        {0.3},
        {0.1},
        {-0.2}
    };

    rnn_forward(input, hidden, output, input_hidden_weights, hidden_hidden_weights, hidden_output_weights);

    printf("Output:\n");
    for (int t = 0; t < TIME_STEPS; t++) {
        printf("%f\n", output[t][0]);
    }

    return 0;
}