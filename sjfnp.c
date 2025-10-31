#include <stdio.h>
typedef struct {
 int pid;
 int at;
 int bt;
 int wt;
 int tat;
 int completed;
} Process;
void sortByArrival(Process p[], int n) {
 for (int i = 0; i < n - 1; i++)
 for (int j = 0; j < n - i - 1; j++)
 if (p[j].at > p[j + 1].at) {
 Process temp = p[j];
 p[j] = p[j + 1];
 p[j + 1] = temp;
 }
}
int main() {
 int n;
 Process p[20];
 printf("Enter number of processes: ");
 scanf("%d", &n);
 for (int i = 0; i < n; i++) {
 p[i].pid = i + 1;
 printf("Enter arrival time and burst time for P%d:", p[i].pid);
 scanf("%d %d", &p[i].at, &p[i].bt);
 p[i].completed = 0;
 }
 sortByArrival(p, n);
 int completed = 0, current_time = 0;
 while (completed < n) {
 int idx = -1, min_bt = 9999;
 for (int i = 0; i < n; i++) {
 if (p[i].at <= current_time && p[i].completed
== 0) {
 if (p[i].bt < min_bt) {
 min_bt = p[i].bt;
 idx = i;
 }
 }
 }
 if (idx != -1) {
 p[idx].wt = current_time - p[idx].at;
 current_time += p[idx].bt;
 p[idx].tat = current_time - p[idx].at;
 p[idx].completed = 1;
 completed++;
} else {
 current_time++;
 }
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