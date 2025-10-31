 
#include <stdio.h> 
 
typedef struct { 
    int pid, at, bt, remaining_time; 
    int ct, tat, wt; 
    int completed; 
} Process; 
 
int main() { 
    int n; 
    Process p[20]; 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
 
    for (int i = 0; i < n; i++) { 
        p[i].pid = i + 1; 
        printf("Enter arrival time and burst time for P%d: ", p[i].pid); 
        scanf("%d %d", &p[i].at, &p[i].bt); 
        p[i].remaining_time = p[i].bt; 
        p[i].completed = 0; 
    } 
 
    int time = 0, completed = 0, min_remain, idx; 
    while (completed < n) { 
        idx = -1; 
        min_remain = 9999; 
 
        for (int i = 0; i < n; i++) { 
            if (p[i].at <= time && p[i].completed == 0 && 
p[i].remaining_time < min_remain) { 
                min_remain = p[i].remaining_time; 
                idx = i; 
            } 
        } 
 
        if (idx != -1) { 
            p[idx].remaining_time--; 
            if (p[idx].remaining_time == 0) { 
                p[idx].ct = time + 1; 
                p[idx].tat = p[idx].ct - p[idx].at; 
                p[idx].wt = p[idx].tat - p[idx].bt; 
                p[idx].completed = 1; 
                completed++; 
            } 
        } 
        time++; 
    } 
 
    float total_wt = 0, total_tat = 0; 
    printf("\nPID\tAT\tBT\tWT\tTAT\n"); 
    for (int i = 0; i < n; i++) { 
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, 
p[i].at, p[i].bt, p[i].wt, p[i].tat); 
        total_wt += p[i].wt; 
        total_tat += p[i].tat;
          } 
 
    printf("\nAverage Waiting Time: %.2f", total_wt / 
n); 
    printf("\nAverage Turnaround Time: %.2f\n", 
total_tat / n); 
 
    return 0; 
} 
