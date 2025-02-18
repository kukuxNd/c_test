#ifndef TENSOR_H
#define TENSOR_H

// 简单张量结构体，仅支持二维张量
typedef struct {
    int rows;
    int cols;
    float *data;
} Tensor;

// 创建一个张量并分配内存
Tensor *create_tensor(int rows, int cols);

// 释放张量内存
void free_tensor(Tensor *tensor);

// 打印张量内容（调试用）
void print_tensor(const Tensor *tensor);

#endif