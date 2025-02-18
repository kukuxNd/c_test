#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEQ_LENGTH 4
#define EMBEDDING_DIM 3
#define NUM_HEADS 2
#define HEAD_DIM (EMBEDDING_DIM / NUM_HEADS)

double dot_product(double *a, double *b, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

void self_attention(double input[SEQ_LENGTH][EMBEDDING_DIM], double output[SEQ_LENGTH][EMBEDDING_DIM],
                    double weights_q[EMBEDDING_DIM][EMBEDDING_DIM], double weights_k[EMBEDDING_DIM][EMBEDDING_DIM],
                    double weights_v[EMBEDDING_DIM][EMBEDDING_DIM]) {
    double queries[SEQ_LENGTH][EMBEDDING_DIM];
    double keys[SEQ_LENGTH][EMBEDDING_DIM];
    double values[SEQ_LENGTH][EMBEDDING_DIM];
    double scores[SEQ_LENGTH][SEQ_LENGTH];

    for (int i = 0; i < SEQ_LENGTH; i++) {
        for (int j = 0; j < EMBEDDING_DIM; j++) {
            queries[i][j] = dot_product(input[i], weights_q[j], EMBEDDING_DIM);
            keys[i][j] = dot_product(input[i], weights_k[j], EMBEDDING_DIM);
            values[i][j] = dot_product(input[i], weights_v[j], EMBEDDING_DIM);
        }
    }

    for (int i = 0; i < SEQ_LENGTH; i++) {
        for (int j = 0; j < SEQ_LENGTH; j++) {
            scores[i][j] = dot_product(queries[i], keys[j], EMBEDDING_DIM) / sqrt(EMBEDDING_DIM);
        }
    }

    for (int i = 0; i < SEQ_LENGTH; i++) {
        for (int j = 0; j < SEQ_LENGTH; j++) {
            double sum = 0.0;
            for (int k = 0; k < SEQ_LENGTH; k++) {
                sum += exp(scores[i][k]);
            }
            scores[i][j] = exp(scores[i][j]) / sum;
        }
    }

    for (int i = 0; i < SEQ_LENGTH; i++) {
        for (int j = 0; j < EMBEDDING_DIM; j++) {
            output[i][j] = 0.0;
            for (int k = 0; k < SEQ_LENGTH; k++) {
                output[i][j] += scores[i][k] * values[k][j];
            }
        }
    }
}

int main() {
    double input[SEQ_LENGTH][EMBEDDING_DIM] = {
        {1.0, 0.5, -1.0},
        {0.5, 1.0, 0.0},
        {0.0, 0.5, -0.5},
        {1.0, 0.0, 1.0}
    };

    double weights_q[EMBEDDING_DIM][EMBEDDING_DIM] = {
        {0.1, 0.2, 0.3},
        {0.4, 0.5, 0.6},
        {0.7, 0.8, 0.9}
    };

    double weights_k[EMBEDDING_DIM][EMBEDDING_DIM] = {
        {0.2, 0.3, 0.4},
        {0.5, 0.6, 0.7},
        {0.8, 0.9, 1.0}
    };

    double weights_v[EMBEDDING_DIM][EMBEDDING_DIM] = {
        {0.3, 0.4, 0.5},
        {0.6, 0.7, 0.8},
        {0.9, 1.0, 1.1}
    };

    double output[SEQ_LENGTH][EMBEDDING_DIM];
    self_attention(input, output, weights_q, weights_k, weights_v);

    printf("Output:\n");
    for (int i = 0; i < SEQ_LENGTH; i++) {
        for (int j = 0; j < EMBEDDING_DIM; j++) {
            printf("%f ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}