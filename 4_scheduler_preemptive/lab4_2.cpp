#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


int main() {
    setlocale(LC_ALL, "Rus");
    
    int amount, sum=0, min_time, ready=0, min=INT_MAX, max_time=0, index;
    int* process_time;
    int *process_time_copy;
    
    int *time;
    int *time_copy;
    int *ready_processes;

    printf("Amount of processes: ");
    scanf_s("%d", &amount);

    process_time = (int*)malloc(amount * sizeof(int));
    process_time_copy = (int*)malloc(amount * sizeof(int));
    time = (int*)malloc(amount * sizeof(int));
    time_copy = (int*)malloc(amount * sizeof(int));
    ready_processes = (int*)malloc(amount * sizeof(int));
    
    for (int i = 0; i < amount; i++) {
        printf("%d process: ", i + 1);
        scanf_s("%d", &process_time[i]);
        printf("\n");

        printf("Time of %d receipt: ", i + 1);
        scanf_s("%d", &time[i]);
        printf("\n");

        if (time[i] > max_time)
            max_time = time[i];
        
        time_copy[i] = time[i];
        process_time_copy[i] = process_time[i];
        sum += process_time[i];
    }
    printf("\n  ");

    // 3. Алгоритм SJF (учёт времени поступления)

    // Печать времени для процессов
    for (int count_time = 1; count_time <= 20; count_time++)
        printf("%d ", count_time);

    printf("\n");

    for (int ii = 0; ii < amount; ii++) {
        printf("%d ", ii + 1);
        for (int jj = 0; jj < sum + max_time; jj++) {
            min = INT_MAX;
            min_time = INT_MAX;
            index = -1;
            
            if (process_time[ii] == 0)
                break;

            for (int j = 0; j < amount; j++) {
                if ((time[j] <= 0 && process_time[j] < min && process_time[j]) || (time[j]<=0 && process_time[j]<=min && time[j]<=min_time && process_time[j])) {
                    min = process_time[j];
                    index = j;
                    min_time=time[j];
                }
            }

            if (time[ii] > 0) {
                printf("  ");
                if (index>=0)
                    process_time[index]--;
            }
            else {
                if (ii == index) {
                    printf("e ");
                    process_time[ii]--;
                }
                else {
                    printf("w ");
                    process_time[index]--;
                    ready_processes[ii]++;
                }
            }
            for (int j = 0; j < amount; j++) {
                time[j]--;
            }
        }
        ready += ready_processes[ii];
        printf("\n");
        
        for (int j = 0; j < amount; j++) {
            process_time[j] = process_time_copy[j];
            time[j] = time_copy[j];
        }
    }
    printf("\n");
    printf("Number of process ");
    for (int i = 0; i < amount; i++)
        printf("%3d  ", i + 1);
    printf("\n");
    
    printf("Execution time    ");
    for (int i = 0; i < amount; i++)
        printf("%3d  ", process_time[i] + ready_processes[i]);
    printf("        %f  \n", (float)(sum + ready) / amount);
    
    printf("Waiting time      ");
    for (int i = 0; i<amount; i++)
        printf("%3d  ", ready_processes[i]);
    printf("        %f", (float)ready / amount);
    
    return 0;
}
