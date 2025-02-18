#ifndef MODEL_H
#define MODEL_H

#include "layer.h"

typedef struct {
    int num_layers;      // 模型中包含的层数
    Layer **layers;      // 层数组
} Model;

// 创建一个简单模型（可以手动添加多个层）
Model* create_model();

// 模型训练（这里只是骨架，实际训练需要实现前向传播、反向传播和优化）
void train_model(Model *model);

// 释放模型占用的内存
void free_model(Model *model);

#endif