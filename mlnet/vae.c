#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 3
#define HIDDEN_NODES 2
#define LATENT_DIM 2

// 激活函数：sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 编码器前向传播
void encoder_forward(double input[INPUT_NODES], double mean[LATENT_DIM], double log_var[LATENT_DIM],
                     double input_hidden_weights[INPUT_NODES][HIDDEN_NODES], double hidden_mean_weights[HIDDEN_NODES][LATENT_DIM],
                     double hidden_log_var_weights[HIDDEN_NODES][LATENT_DIM]) {
    double hidden[HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden[i] = 0.0;
        for (int j = 0; j < INPUT_NODES; j++) {
            hidden[i] += input[j] * input_hidden_weights[j][i];
        }
        hidden[i] = sigmoid(hidden[i]);
    }

    for (int i = 0; i < LATENT_DIM; i++) {
        mean[i] = 0.0;
        log_var[i] = 0.0;
        for (int j = 0; j < HIDDEN_NODES; j++) {
            mean[i] += hidden[j] * hidden_mean_weights[j][i];
            log_var[i] += hidden[j] * hidden_log_var_weights[j][i];
        }
    }
}

// 解码器前向传播
void decoder_forward(double z[LATENT_DIM], double output[INPUT_NODES], double latent_hidden_weights[LATENT_DIM][HIDDEN_NODES],
                     double hidden_output_weights[HIDDEN_NODES][INPUT_NODES]) {
    double hidden[HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden[i] = 0.0;
        for (int j = 0; j < LATENT_DIM; j++) {
            hidden[i] += z[j] * latent_hidden_weights[j][i];
        }
        hidden[i] = sigmoid(hidden[i]);
    }

    for (int i = 0; i < INPUT_NODES; i++) {
        output[i] = 0.0;
        for (int j = 0; j < HIDDEN_NODES; j++) {
            output[i] += hidden[j] * hidden_output_weights[j][i];
        }
        output[i] = sigmoid(output[i]);
    }
}

int main() {
    double input[INPUT_NODES] = {1.0, 0.5, -1.0};
    double mean[LATENT_DIM];
    double log_var[LATENT_DIM];

    double input_hidden_weights[INPUT_NODES][HIDDEN_NODES] = {
        {0.1, 0.2},
        {-0.1, 0.3},
        {0.4, 0.1}
    };

    double hidden_mean_weights[HIDDEN_NODES][LATENT_DIM] = {
        {0.3, -0.1},
        {0.1, 0.4}
    };

    double hidden_log_var_weights[HIDDEN_NODES][LATENT_DIM] = {
        {0.2, 0.1},
        {-0.3, 0.2}
    };

    encoder_forward(input, mean, log_var, input_hidden_weights, hidden_mean_weights, hidden_log_var_weights);

    double z[LATENT_DIM];
    for (int i = 0; i < LATENT_DIM; i++) {
        double std = exp(0.5 * log_var[i]);
        z[i] = mean[i] + std * ((double) rand() / RAND_MAX);
    }

    double output[INPUT_NODES];

    double latent_hidden_weights[LATENT_DIM][HIDDEN_NODES] = {
        {0.1, 0.3},
        {0.2, -0.1}
    };

    double hidden_output_weights[HIDDEN_NODES][INPUT_NODES] = {
        {0.3, -0.1, 0.2},
        {0.1, 0.4, 0.1}
    };

    decoder_forward(z, output, latent_hidden_weights, hidden_output_weights);

    printf("Output:\n");
    for (int i = 0; i < INPUT_NODES; i++) {
        printf("%f\n", output[i]);
    }

    return 0;
}