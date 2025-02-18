#include <math.h>
#include "activation.h"

void relu(Tensor *tensor) {
    int size = tensor->rows * tensor->cols;
    for (int i = 0; i < size; i++) {
        if (tensor->data[i] < 0)
            tensor->data[i] = 0;
    }
}

void softmax(Tensor *tensor) {
    // 此处演示简单的 softmax 算法，通常在实际应用中需要考虑数值稳定性
    int size = tensor->rows * tensor->cols;
    for (int i = 0; i < tensor->rows; i++) {
        // 找每行最大值（防止溢出）
        float max_val = tensor->data[i * tensor->cols];
        for (int j = 1; j < tensor->cols; j++) {
            float val = tensor->data[i * tensor->cols + j];
            if (val > max_val) max_val = val;
        }
        float sum = 0.0;
        for (int j = 0; j < tensor->cols; j++) {
            int index = i * tensor->cols + j;
            tensor->data[index] = expf(tensor->data[index] - max_val);
            sum += tensor->data[index];
        }
        for (int j = 0; j < tensor->cols; j++) {
            tensor->data[i * tensor->cols + j] /= sum;
        }
    }
}