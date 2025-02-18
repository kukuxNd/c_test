#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NOISE_DIM 3
#define DATA_DIM 2

// 激活函数：sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 生成器前向传播
void generator_forward(double noise[NOISE_DIM], double generated_data[DATA_DIM], double generator_weights[NOISE_DIM][DATA_DIM]) {
    for (int i = 0; i < DATA_DIM; i++) {
        generated_data[i] = 0.0;
        for (int j = 0; j < NOISE_DIM; j++) {
            generated_data[i] += noise[j] * generator_weights[j][i];
        }
        generated_data[i] = sigmoid(generated_data[i]);
    }
}

// 判别器前向传播
double discriminator_forward(double data[DATA_DIM], double discriminator_weights[DATA_DIM]) {
    double score = 0.0;
    for (int i = 0; i < DATA_DIM; i++) {
        score += data[i] * discriminator_weights[i];
    }
    return sigmoid(score);
}

int main() {
    double noise[NOISE_DIM] = {0.5, 0.2, 0.8};
    double generated_data[DATA_DIM];

    double generator_weights[NOISE_DIM][DATA_DIM] = {
        {0.1, 0.2},
        {-0.1, 0.3},
        {0.4, 0.1}
    };

    double discriminator_weights[DATA_DIM] = {0.3, -0.1};

    // 生成器生成数据
    generator_forward(noise, generated_data, generator_weights);

    // 判别器评分
    double score = discriminator_forward(generated_data, discriminator_weights);

    printf("Generated Data:\n");
    for (int i = 0; i < DATA_DIM; i++) {
        printf("%f\n", generated_data[i]);
    }

    printf("Discriminator Score: %f\n", score);

    return 0;
}