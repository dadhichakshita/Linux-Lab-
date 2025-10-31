#include <stdio.h>
#define MAX 10
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n], i, j;
    for (i = 0; i < n; i++)
        allocation[i] = -1;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for (i = 0; i < n; i++)
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1,
                   allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
}
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n], i, j, bestIdx;
    for (i = 0; i < n; i++)
        allocation[i] = -1;
    for (i = 0; i < n; i++)
    {
        bestIdx = -1;
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] <
                                         blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    for (i = 0; i < n; i++)
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1,
                   allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
}
void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n], i, j, worstIdx;
    for (i = 0; i < n; i++)
        allocation[i] = -1;
    for (i = 0; i < n; i++)
    {
        worstIdx = -1;
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] >
                                          blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for (i = 0; i < n; i++)
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1,
                   allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
}
int main()
{
    int m, n, i, blockSize[MAX], processSize[MAX];
    printf("Enter number of blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &processSize[i]);
    int b1[MAX], b2[MAX], b3[MAX];
    for (i = 0; i < m; i++)
    {
        b1[i] = b2[i] = b3[i] = blockSize[i];
    }
    firstFit(b1, m, processSize, n);
    bestFit(b2, m, processSize, n);
    worstFit(b3, m, processSize, n);
    return 0;
}