#include <stdio.h>
#include "model.h"

int main() {
    // 创建模型（这里可以根据需要添加多个层）
    Model *model = create_model();

    // 模型训练、推理的代码入口（这里只给出一个骨架）
    printf("开始训练模型...\n");
    train_model(model);
    printf("训练完成。\n");

    // 示例：推理，假设输入数据为固定张量（真实情况需要处理数据读取和预处理）
    // inference_model(model, ...);

    // 释放模型内存
    free_model(model);
    return 0;
}