#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定义一个简单的结构体，保存问答对和一个简单的嵌入向量（这里使用3维向量示例）
typedef struct {
    char question[256];
    char answer[256];
    float embedding[3]; // 这里我们用3维向量作为示例
} QA;

// 计算两个向量之间的余弦相似度
float cosine_similarity(float *v1, float *v2, int dim) {
    float dot = 0.0, mag1 = 0.0, mag2 = 0.0;
    for (int i = 0; i < dim; i++) {
        dot += v1[i] * v2[i];
        mag1 += v1[i] * v1[i];
        mag2 += v2[i] * v2[i];
    }
    if (mag1 == 0 || mag2 == 0) return 0.0;
    return dot / (sqrt(mag1) * sqrt(mag2));
}

// 一个极其简化的函数，用于根据文本生成一个“嵌入向量”，仅作示例
void get_embedding(const char* text, float *embedding, int dim) {
    // 使用文本长度和简单的取模操作，生成一个固定维度的向量
    int len = strlen(text);
    for (int i = 0; i < dim; i++) {
        embedding[i] = (float)((len + i) % (dim + 3)); // 仅作为示例，与真实的词嵌入无关
    }
}

int main() {
    // 定义一个简单的问答数据集（示例数据）
    QA dataset[3] = {
        {"你好", "你好，有什么我可以帮您的吗？", {0.0, 0.0, 0.0}},
        {"天气", "今天的天气晴朗，适合外出活动。", {0.0, 0.0, 0.0}},
        {"再见", "再见，祝您生活愉快！", {0.0, 0.0, 0.0}}
    };

    int dim = 3; // 向量维数
    
    // 为数据集中的每一个问题生成一个“嵌入向量”
    for (int i = 0; i < 3; i++) {
        get_embedding(dataset[i].question, dataset[i].embedding, dim);
    }

    // 获取用户输入的问题
    char input[256];
    printf("请输入问题：");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "读取输入失败！\n");
        return 1;
    }
    // 去除换行符
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }

    // 为用户输入生成“嵌入向量”
    float input_embedding[3];
    get_embedding(input, input_embedding, dim);

    // 计算用户输入和数据集中每个问题之间的相似度
    float best_similarity = -1.0;
    int best_index = -1;
    for (int i = 0; i < 3; i++) {
        float similarity = cosine_similarity(input_embedding, dataset[i].embedding, dim);
        printf("与 \"%s\" 的相似度：%f\n", dataset[i].question, similarity);
        if (similarity > best_similarity) {
            best_similarity = similarity;
            best_index = i;
        }
    }

    // 输出最佳匹配的问题及对应的回答
    if (best_index >= 0) {
        printf("\n最佳匹配问题：%s\n", dataset[best_index].question);
        printf("回答：%s\n", dataset[best_index].answer);
    } else {
        printf("未匹配到合适的回答。\n");
    }

    return 0;
}