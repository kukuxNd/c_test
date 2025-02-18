#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATES 5
#define ACTIONS 2
#define EPISODES 1000
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.1

int get_action(double q_table[STATES][ACTIONS], int state) {
    if ((double) rand() / RAND_MAX < EPSILON) {
        return rand() % ACTIONS;
    } else {
        return q_table[state][0] > q_table[state][1] ? 0 : 1;
    }
}

int main() {
    double q_table[STATES][ACTIONS] = {0};
    int rewards[STATES][ACTIONS] = {
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {0, 0}
    };

    srand(time(NULL));

    for (int episode = 0; episode < EPISODES; episode++) {
        int state = rand() % STATES;
        while (state != STATES - 1) {
            int action = get_action(q_table, state);
            int next_state = state + (action == 0 ? -1 : 1);
            if (next_state < 0) next_state = 0;
            if (next_state >= STATES) next_state = STATES - 1;

            double reward = rewards[state][action];
            double max_next_q = q_table[next_state][0] > q_table[next_state][1] ? q_table[next_state][0] : q_table[next_state][1];
            q_table[state][action] += ALPHA * (reward + GAMMA * max_next_q - q_table[state][action]);

            state = next_state;
        }
    }

    printf("Q-table:\n");
    for (int i = 0; i < STATES; i++) {
        for (int j = 0; j < ACTIONS; j++) {
            printf("%f ", q_table[i][j]);
        }
        printf("\n");
    }

    return 0;
}