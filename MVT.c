#include <stdio.h> 
 
void MFT() { 
    int ms, bs, nob, ef, n, mp[10], i, j; 
    int b[10] = {0}, count = 0; 
    printf("Enter total memory size: "); 
    scanf("%d", &ms); 
    printf("Enter block size: "); 
    scanf("%d", &bs); 
    nob = ms / bs; 
    ef = ms - nob * bs; 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
    printf("Enter memory required for each process:\n"); 
    for (i = 0; i < n; i++) 
    scanf("%d", &mp[i]); 
 
    printf("\nMemory blocks allocation (MFT):\n"); 
    j = 0; 
    for (i = 0; i < n && j < nob; i++) { 
        if (mp[i] <= bs) { 
            printf("Process %d -> Block %d (%d KB used, %d KB wasted)\n", 
                   i + 1, j + 1, mp[i], bs - mp[i]); 
            count++; 
            j++; 
        } else 
            printf("Process %d -> Not allocated (size too big)\n", i + 1); 
    } 
    printf("Total processes allocated: %d\n", count); 
    printf("External Fragmentation = %d\n", ef); 
} 
 
void MVT() { 
    int ms, n, mp[10], i, sum = 0; 
    printf("Enter total memory size: "); 
    scanf("%d", &ms); 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
    printf("Enter memory required for each process:\n"); 
    for (i = 0; i < n; i++) scanf("%d", &mp[i]); 
 
    printf("\nMemory blocks allocation (MVT):\n"); 
    for (i = 0; i < n; i++) { 
        if (sum + mp[i] <= ms) { 
            printf("Process %d -> Allocated (%d KB)\n", i + 1, mp[i]); 
            sum += mp[i]; 
        } else 
            printf("Process %d -> Not allocated (insufficient memory)\n", i + 1); 
    } 
    printf("Total memory used: %d\n", sum); 
    printf("External Fragmentation = %d\n", ms - 
sum); 
} 
 
int main() { 
    int choice; 
    printf("1. MFT\n2. MVT\nEnter choice: "); 
    scanf("%d", &choice); 
    if (choice == 1) MFT(); 
    else MVT(); 
    return 0; 
} 
 
 