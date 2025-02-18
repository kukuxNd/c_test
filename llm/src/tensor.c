#include <stdio.h>
#include <stdlib.h>
#include "tensor.h"

Tensor *create_tensor(int rows, int cols) {
    Tensor *tensor = (Tensor*) malloc(sizeof(Tensor));
    tensor->rows = rows;
    tensor->cols = cols;
    tensor->data = (float*) calloc(rows * cols, sizeof(float));
    return tensor;
}

void free_tensor(Tensor *tensor) {
    if (tensor) {
        free(tensor->data);
        free(tensor);
    }
}

void print_tensor(const Tensor *tensor) {
    for (int i = 0; i < tensor->rows; i++) {
        for (int j = 0; j < tensor->cols; j++) {
            printf("%f ", tensor->data[i * tensor->cols + j]);
        }
        printf("\n");
    }
}