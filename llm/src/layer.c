#include <stdlib.h>
#include "layer.h"
#include "tensor.h"

Layer *create_dense_layer(int input_dim, int output_dim) {
    Layer *layer = (Layer*) malloc(sizeof(Layer));
    layer->type = DENSE;
    // 初始化权重和偏置张量（这里仅作为示例，实际应随机初始化）
    layer->weights = create_tensor(input_dim, output_dim);
    layer->bias = create_tensor(1, output_dim);
    return layer;
}

void forward_layer(Layer *layer, Tensor *input, Tensor *output) {
    // 实现全连接层的前向传播：output = input * weights + bias
    // 这里仅作为占位，实际需要实现矩阵乘法和加法。
}

void free_layer(Layer *layer) {
    free_tensor(layer->weights);
    free_tensor(layer->bias);
    free(layer);
}