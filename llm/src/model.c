#include <stdlib.h>
#include <stdio.h>
#include "model.h"
#include "layer.h"

Model* create_model() {
    Model *model = (Model*) malloc(sizeof(Model));
    // 示例中，我们先创建一个单层模型
    model->num_layers = 1;
    model->layers = (Layer**) malloc(sizeof(Layer*) * model->num_layers);
    // 可以在这里根据需要选择不同类型的层，例如全连接层
    model->layers[0] = create_dense_layer(784, 128);  // 示例：输入维度784，输出维度128
    return model;
}

void train_model(Model *model) {
    // 这里实现训练逻辑：前向传播、计算损失、反向传播、参数更新等
    // 此处只打印一条消息，作为占位符。
    printf("训练中...（此处应实现训练循环和参数更新）\n");
}

void free_model(Model *model) {
    // 释放每一层内存
    for (int i = 0; i < model->num_layers; i++) {
        free_layer(model->layers[i]);
    }
    free(model->layers);
    free(model);
}