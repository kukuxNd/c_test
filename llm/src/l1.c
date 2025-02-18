#include <stdio.h>
#include <string.h>
#include <math.h>

// Extremely simplified example (no actual neural network)
float cosine_similarity(float *vec1, float *vec2, int dim) {
    float dot_product = 0.0;
    float magnitude1 = 0.0;
    float magnitude2 = 0.0;
    for (int i = 0; i < dim; i++) {
        dot_product += vec1[i] * vec2[i];
        magnitude1 += vec1[i] * vec1[i];
        magnitude2 += vec2[i] * vec2[i];
    }
    magnitude1 = sqrt(magnitude1);
    magnitude2 = sqrt(magnitude2);
    return dot_product / (magnitude1 * magnitude2);
}

int main() {
    // Example question and answer embeddings (replace with actual embeddings)
    float question_embedding[2] = {0.8, 0.6};
    float answer1_embedding[2] = {0.7, 0.5};
    float answer2_embedding[2] = {0.2, 0.9};

    // Calculate cosine similarity
    float similarity1 = cosine_similarity(question_embedding, answer1_embedding, 2);
    float similarity2 = cosine_similarity(question_embedding, answer2_embedding, 2);

    printf("Similarity to answer 1: %f\n", similarity1);
    printf("Similarity to answer 2: %f\n", similarity2);

    if (similarity1 > similarity2) {
        printf("Answer 1 is more likely.\n");
    } else {
        printf("Answer 2 is more likely.\n");
    }

    return 0;
}