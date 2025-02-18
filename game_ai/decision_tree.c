#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FEATURES 2
#define NUM_SAMPLES 10
#define MAX_DEPTH 3

typedef struct TreeNode {
    int feature;
    double threshold;
    int label;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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
        leaf->label = rand() % 2;
        return leaf;
    }

    TreeNode *node = create_node();
    node->feature = rand() % NUM_FEATURES;
    node->threshold = ((double)rand() / RAND_MAX) * 10.0;
    node->left = build_tree(depth + 1);
    node->right = build_tree(depth + 1);

    return node;
}

int predict_tree(TreeNode *tree, double *sample) {
    if (!tree->left && !tree->right) {
        return tree->label;
    }

    if (sample[tree->feature] < tree->threshold) {
        return predict_tree(tree->left, sample);
    } else {
        return predict_tree(tree->right, sample);
    }
}

int main() {
    srand(time(NULL));

    TreeNode *root = build_tree(0);

    double test_sample[NUM_FEATURES] = {5.0, 5.0};
    int prediction = predict_tree(root, test_sample);
    printf("Prediction: %d\n", prediction);

    // Free memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}