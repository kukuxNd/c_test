#ifndef LAYER_H
#define LAYER_H

#include "tensor.h"

// 层的类型，可以根据需要扩展
typedef enum {
    DENSE,
    // 可添加其他类型，例如 CONVOLUTIONAL 等
} LayerType;

typedef struct {
    LayerType type;
    Tensor *weights;
    Tensor *bias;
    // 其它层参数可在此处添加
} Layer;

// 创建一个全连接层（Dense Layer）的函数：输入维度和输出维度
Layer *create_dense_layer(int input_dim, int output_dim);

// 前向传播：输入张量，输出结果张量
void forward_layer(Layer *layer, Tensor *input, Tensor *output);

// 释放层相关内存
void free_layer(Layer *layer);

#endif