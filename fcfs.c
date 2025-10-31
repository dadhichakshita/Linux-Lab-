#include <stdio.h>
typedef struct {
 int pid; // Process ID
 int BT; // CPU Burst Time
 int AT; // Arrival Time
 int WT;
 int TAT;
 int CT;
} Process;
void Find_WT_TAT(Process p[], int n) {
 int current_time = 0;
 for (int i = 0; i < n; i++) {
 // If CPU is idle
 if (current_time < p[i].AT) {
 current_time = p[i].AT;
 }
 p[i].WT = current_time - p[i].AT;
 p[i].CT = current_time + p[i].BT;
 p[i].TAT = p[i].CT - p[i].AT;
 current_time = p[i].CT;
 }
}
void Show_ProcessTable(Process p[], int n) {
 float total_waiting = 0, total_turnaround = 0;
printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
 for (int i = 0; i < n; i++) {
 printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n",
 p[i].pid,
 p[i].AT,
 p[i].BT,
 p[i].WT,
 p[i].TAT,
 p[i].CT);
 total_waiting += p[i].WT;
 total_turnaround += p[i].TAT;
 }
 printf("\nAverage Waiting Time: %.2f", total_waiting / n);
 printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
}
int main() {
 int n;
 Process p[20];
 printf("Enter number of processes: ");
 scanf("%d", &n);
 printf("Enter Arrival Time and Burst Time for each process:\n");
 for (int i = 0; i < n; i++) {
 p[i].pid = i + 1;
 printf("P%d Arrival Time: ", p[i].pid);
 scanf("%d", &p[i].AT);
 printf("P%d Burst Time: ", p[i].pid);
 scanf("%d", &p[i].BT);
 }
 // Sort processes by arrival time
 for (int i = 0; i < n - 1; i++) {
 for (int j = 0; j < n - i - 1; j++) {
 if (p[j].AT > p[j + 1].AT) {
 Process temp = p[j];
 p[j] = p[j + 1];
 p[j + 1] = temp;
 }
 }
 }
 Find_WT_TAT(p, n);
 Show_ProcessTable (p, n);
 return 0;
}