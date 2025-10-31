#include <stdio.h>

typedef struct {
    int pid;   
    int BT;    
    int AT;  
    int WT;    
    int TAT;  
    int CT;    
    char type; 
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void find_WT_TAT(Process p[], int n, int start_time) {
    int current_time = start_time;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].AT) {
            current_time = p[i].AT; 
        }
        p[i].WT = current_time - p[i].AT;
        p[i].CT = current_time + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        current_time = p[i].CT;
    }
}

int main() {
    int n;
    Process p[20], s[10], u[10];
    int sCount = 0, uCount = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter details for Process P%d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
        printf("Type (S = System / Higher, U = User / Lower): ");
        scanf(" %c", &p[i].type);

        if (p[i].type == 'S' || p[i].type == 's') {
            s[sCount++] = p[i];  
        } else {
            u[uCount++] = p[i];  
        }
    }

    
    sortByArrival(s, sCount);
    sortByArrival(u, uCount);

    
    find_WT_TAT(s, sCount, 0);

    
    int sys_end = (sCount > 0) ? s[sCount - 1].CT : 0;
    find_WT_TAT(u, uCount, sys_end);

  
    printf("\nPID\tAT\tBT\tType\tWT\tTAT\tCT\n");
    for (int i = 0; i < sCount; i++) {
        printf("P%d\t%d\t%d\tS(Higher)\t%d\t%d\t%d\n",
               s[i].pid, s[i].AT, s[i].BT, s[i].WT, s[i].TAT, s[i].CT);
    }
    for (int i = 0; i < uCount; i++) {
        printf("P%d\t%d\t%d\tU(Lower)\t%d\t%d\t%d\n",
               u[i].pid, u[i].AT, u[i].BT, u[i].WT, u[i].TAT, u[i].CT);
    }

    
    printf("\nExecution Order:\n");
    for (int i = 0; i < sCount; i++) {
        printf("P%d(Higher) -> ", s[i].pid);
    }
    for (int i = 0; i < uCount; i++) {
        printf("P%d(Lower) -> ", u[i].pid);
    }
    printf("End\n");

    return 0;
}