#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POP_SIZE 10
#define GENE_LENGTH 5
#define MAX_GENERATIONS 100
#define MUTATION_RATE 0.1

typedef struct {
    int genes[GENE_LENGTH];
    int fitness;
} Individual;

Individual population[POP_SIZE];

int evaluate_fitness(Individual *ind) {
    int sum = 0;
    for (int i = 0; i < GENE_LENGTH; i++) {
        sum += ind->genes[i];
    }
    return sum;
}

void initialize_population() {
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 0; j < GENE_LENGTH; j++) {
            population[i].genes[j] = rand() % 2;
        }
        population[i].fitness = evaluate_fitness(&population[i]);
    }
}

Individual crossover(Individual parent1, Individual parent2) {
    Individual child;
    int crossover_point = rand() % GENE_LENGTH;
    for (int i = 0; i < GENE_LENGTH; i++) {
        if (i < crossover_point) {
            child.genes[i] = parent1.genes[i];
        } else {
            child.genes[i] = parent2.genes[i];
        }
    }
    child.fitness = evaluate_fitness(&child);
    return child;
}

void mutate(Individual *ind) {
    for (int i = 0; i < GENE_LENGTH; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            ind->genes[i] = !ind->genes[i];
        }
    }
    ind->fitness = evaluate_fitness(ind);
}

Individual select_parent() {
    return population[rand() % POP_SIZE];
}

void evolve() {
    Individual new_population[POP_SIZE];

    for (int i = 0; i < POP_SIZE; i++) {
        Individual parent1 = select_parent();
        Individual parent2 = select_parent();
        new_population[i] = crossover(parent1, parent2);
        mutate(&new_population[i]);
    }

    for (int i = 0; i < POP_SIZE; i++) {
        population[i] = new_population[i];
    }
}

int main() {
    srand(time(NULL));

    initialize_population();

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        evolve();
    }

    for (int i = 0; i < POP_SIZE; i++) {
        printf("Individual %d: fitness = %d\n", i, population[i].fitness);
    }

    return 0;
}