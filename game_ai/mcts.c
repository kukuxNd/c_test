#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITERATIONS 1000
#define EXPLORATION_CONSTANT 1.414

typedef struct TreeNode {
    int visits;
    double value;
    struct TreeNode *parent;
    struct TreeNode *children[2];
} TreeNode;

TreeNode* create_node(TreeNode *parent) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->visits = 0;
    node->value = 0.0;
    node->parent = parent;
    node->children[0] = NULL;
    node->children[1] = NULL;
    return node;
}

double simulate() {
    return ((double)rand() / RAND_MAX) > 0.5 ? 1.0 : 0.0;
}

TreeNode* select_best_child(TreeNode *node) {
    TreeNode *best_child = NULL;
    double best_value = -INFINITY;
    for (int i = 0; i < 2; i++) {
        if (node->children[i] != NULL) {
            double uct_value = node->children[i]->value / node->children[i]->visits +
                               EXPLORATION_CONSTANT * sqrt(log(node->visits) / node->children[i]->visits);
            if (uct_value > best_value) {
                best_value = uct_value;
                best_child = node->children[i];
            }
        }
    }
    return best_child;
}

void backpropagate(TreeNode *node, double result) {
    while (node != NULL) {
        node->visits++;
        node->value += result;
        node = node->parent;
    }
}

void expand(TreeNode *node) {
    for (int i = 0; i < 2; i++) {
        if (node->children[i] == NULL) {
            node->children[i] = create_node(node);
        }
    }
}

void mcts(TreeNode *root) {
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        TreeNode *node = root;
        while (node->children[0] != NULL && node->children[1] != NULL) {
            node = select_best_child(node);
        }
        expand(node);
        double result = simulate();
        backpropagate(node, result);
    }
}

int main() {
    printf("MCTS Simulation\n");
    srand(time(NULL));

    TreeNode *root = create_node(NULL);
    mcts(root);

    printf("Root visits: %d\n", root->visits);
    printf("Root value: %f\n", root->value);

    // Free memory
    for (int i = 0; i < 2; i++) {
        free(root->children[i]);
    }
    free(root);

    return 0;
}