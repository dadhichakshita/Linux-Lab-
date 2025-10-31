#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10] = {0}, safeSeq[10], ind = 0;

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm
    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[ind++] = i;
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    // Check if safe
    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
    } else {
        printf("\nSystem is NOT in a safe state.");
    }

     return 0;
}