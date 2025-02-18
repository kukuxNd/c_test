#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "tensor.h"

// ReLU 激活函数，对张量中的每个元素进行操作
void relu(Tensor *tensor);

// Softmax 激活函数，通常用于输出层归一化
void softmax(Tensor *tensor);

#endif