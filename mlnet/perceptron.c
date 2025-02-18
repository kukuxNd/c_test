#include <stdio.h>
#include <stdlib.h>

#define INPUT_NODES 3
#define LEARNING_RATE 0.1
#define EPOCHS 1000

typedef struct {
    double weights[INPUT_NODES];
    double bias;
} Perceptron;

// 激活函数：阶跃函数
int step_function(double x) {
    return x >= 0 ? 1 : 0;
}

// 初始化感知机
void initialize_perceptron(Perceptron *p) {
    for (int i = 0; i < INPUT_NODES; i++) {
        p->weights[i] = ((double)rand() / RAND_MAX) * 2 - 1;  // 初始化为-1到1之间的随机值
    }
    p->bias = ((double)rand() / RAND_MAX) * 2 - 1;  // 初始化为-1到1之间的随机值
}

// 前向传播
int predict(Perceptron *p, double input[INPUT_NODES]) {
    double sum = p->bias;
    for (int i = 0; i < INPUT_NODES; i++) {
        sum += p->weights[i] * input[i];
    }
    return step_function(sum);
}

// 训练感知机
void train(Perceptron *p, double inputs[][INPUT_NODES], int labels[], int num_samples) {
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        for (int i = 0; i < num_samples; i++) {
            int prediction = predict(p, inputs[i]);
            int error = labels[i] - prediction;

            // 更新权重和偏置
            for (int j = 0; j < INPUT_NODES; j++) {
                p->weights[j] += LEARNING_RATE * error * inputs[i][j];
            }
            p->bias += LEARNING_RATE * error;
        }
    }
}

int main() {
    srand(time(NULL));

    // 输入数据和标签
    double inputs[4][INPUT_NODES] = {
        {0.0, 0.0, 1.0},
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0},
        {1.0, 1.0, 1.0}
    };
    int labels[4] = {0, 0, 0, 1};  // AND逻辑门

    Perceptron p;
    initialize_perceptron(&p);
    train(&p, inputs, labels, 4);

    printf("Trained weights: ");
    for (int i = 0; i < INPUT_NODES; i++) {
        printf("%f ", p.weights[i]);
    }
    printf("\nTrained bias: %f\n", p.bias);

    // 测试感知机
    double test_input[INPUT_NODES] = {1.0, 1.0, 1.0};
    int prediction = predict(&p, test_input);
    printf("Prediction for input {1.0, 1.0, 1.0}: %d\n", prediction);

    return 0;
}