#include <stdio.h>
struct Process {
 int id, at, bt, rt, ct, tat, wt;
};
int main() {
 int n, time = 0, tq;
 printf("Enter number of processes: ");
 scanf("%d", &n);
 struct Process p[n];
 for (int i = 0; i < n; i++) {
 p[i].id = i + 1;
 printf("Enter AT and BT of P%d: ", p[i].id);
 scanf("%d %d", &p[i].at, &p[i].bt);
 p[i].rt = p[i].bt;
 }
 printf("Enter Time Quantum: ");
 scanf("%d", &tq);
 int completed = 0;
 while (completed < n) {
 int done = 1;
 for (int i = 0; i < n; i++) {
 if (p[i].rt > 0 && p[i].at <= time) {
 done = 0;
 if (p[i].rt > tq) {
 time += tq;
 p[i].rt -= tq;
 } else {
 time += p[i].rt;
 p[i].ct = time;
 p[i].rt = 0;
 completed++;
 }
 }
 }
 if (done) time++; // idle time handling
 }
 float totalTAT = 0, totalWT = 0;
 printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
 for (int i = 0; i < n; i++) {
 p[i].tat = p[i].ct - p[i].at;
 p[i].wt = p[i].tat - p[i].bt;
 totalTAT += p[i].tat;
 totalWT += p[i].wt;
 printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id,
p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
 }
 printf("\nAvg TAT = %.2f, Avg WT = %.2f\n",
totalTAT / n, totalWT / n);
 return 0;
}