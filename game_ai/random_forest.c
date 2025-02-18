#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TREES 10
#define MAX_DEPTH 3
#define NUM_FEATURES 2
#define NUM_SAMPLES 10

typedef struct TreeNode {
    int feature;
    double threshold;
    int left_label;
    int right_label;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *trees[NUM_TREES];
} RandomForest;

double data[NUM_SAMPLES][NUM_FEATURES] = {
    {2.0, 3.0}, {1.0, 1.0}, {4.0, 5.0}, {6.0, 7.0}, {8.0, 9.0},
    {3.0, 3.5}, {1.5, 1.5}, {5.0, 5.5}, {7.0, 7.5}, {9.0, 6.0}
};

int labels[NUM_SAMPLES] = {0, 0, 0, 1, 1, 0, 0, 1, 1, 1};

TreeNode* create_node() {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* build_tree(int depth) {
    if (depth == MAX_DEPTH) {
        TreeNode *leaf = create_node();
        leaf->left_label = rand() % 2;
        leaf->right_label = rand() % 2;
        return leaf;
    }

    TreeNode *node = create_node();
    node->feature = rand() % NUM_FEATURES;
    node->threshold = ((double)rand() / RAND_MAX) * 10.0;
    node->left = build_tree(depth + 1);
    node->right = build_tree(depth + 1);

    return node;
}

RandomForest* create_forest() {
    RandomForest *forest = (RandomForest *)malloc(sizeof(RandomForest));
    for (int i = 0; i < NUM_TREES; i++) {
        forest->trees[i] = build_tree(0);
    }
    return forest;
}

int predict_tree(TreeNode *tree, double *sample) {
    if (!tree->left && !tree->right) {
        return tree->left_label;
    }

    if (sample[tree->feature] < tree->threshold) {
        return predict_tree(tree->left, sample);
    } else {
        return predict_tree(tree->right, sample);
    }
}

int predict_forest(RandomForest *forest, double *sample) {
    int votes[2] = {0};
    for (int i = 0; i < NUM_TREES; i++) {
        int prediction = predict_tree(forest->trees[i], sample);
        votes[prediction]++;
    }
    return votes[0] > votes[1] ? 0 : 1;
}

int main() {
    srand(time(NULL));

    RandomForest *forest = create_forest();

    double test_sample[NUM_FEATURES] = {5.0, 5.0};
    int prediction = predict_forest(forest, test_sample);
    printf("Prediction: %d\n", prediction);

    // Free memory
    for (int i = 0; i < NUM_TREES; i++) {
        free(forest->trees[i]);
    }
    free(forest);

    return 0;
}