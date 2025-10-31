#include <stdio.h>

#define N 5               
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
int mutex = 1;
int sem[N] = {0, 0, 0, 0, 0};  

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void test(int i) {
    
    if (state[i] == HUNGRY &&
        state[(i + 4) % N] != EATING &&
        state[(i + 1) % N] != EATING) {
        
        state[i] = EATING;
        sem[i] = 1;
        printf("Philosopher %d takes forks %d and %d\n", i + 1, (i + 4) % N + 1, i + 1);
        printf("Philosopher %d is Eating\n", i + 1);
    }
}

void take_fork(int i) {
    wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry\n", i + 1);
    test(i);
    signal(&mutex);

    if (state[i] != EATING)
        printf("Philosopher %d can't eat now (waiting)\n", i + 1);
}

void put_fork(int i) {
    wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", i + 1, (i + 4) % N + 1, i + 1);
    printf("Philosopher %d is Thinking\n", i + 1);
   
    test((i + 4) % N);
    test((i + 1) % N);
    signal(&mutex);
}

int main() {
    int choice, phil;

    while (1) {
        printf("\n1. Take Fork\n2. Put Fork\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Philosopher number (1-5): ");
                scanf("%d", &phil);
                if (phil >= 1 && phil <= 5)
                    take_fork(phil - 1);
                else
                    printf("Invalid philosopher number!\n");
                break;

            case 2:
                printf("Enter Philosopher number (1-5): ");
                scanf("%d", &phil);
                if (phil >= 1 && phil <= 5)
                    put_fork(phil - 1);
                else
                    printf("Invalid philosopher number!\n");
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}