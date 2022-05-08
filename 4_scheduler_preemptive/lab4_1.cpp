/* Моделирование работы планировщика потоков в однопроцессорной ОС
(вытесняющее планирование) */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


int main() {
    setlocale(LC_ALL, "Rus");
    int amount, sum = 0, index, t, t_index, quantum, ready = 0;

    int* process_time;
    int *process_time_copy;

    int *indexes;
    int *ready_processes;

    printf("Amount of processes: ");
    scanf_s("%d", &amount);

    printf("Quantum: ");
    scanf_s("%d", &quantum);

    process_time = (int*)malloc(amount * sizeof(int));
    process_time_copy = (int*)malloc(amount * sizeof(int));

    indexes = (int*)malloc(amount * sizeof(int));
    ready_processes = (int*)malloc(amount * sizeof(int));

    // Введение данных для процессов
    for (int i = 0; i < amount; i++) {
        printf("Time for %d process: \n", i + 1);
        scanf_s("%d", &process_time[i]);

        process_time_copy[i] = process_time[i];
        indexes[i] = i;

        ready += process_time[i] * (amount - i - 1);
    }
    printf("\n  ");

	// 1. Алгоритм FCFS

    // Печать времени для процессов
    for (int count_time = 1; count_time <= 20; count_time++)
        printf("%d ", count_time);

    printf("\n");

    // e (execution) - исполнение, w (waiting) - ожидание
    for (int i = 0; i < amount; i++) {
        printf("%d ", i + 1);
        while (process_time[i]) {
            ready = 0;
            for (int j = 0; j < i; j++) {
                if (process_time[j] >= quantum) {
                    ready += quantum;
                    process_time[j] -= quantum;
                }
                else if (process_time[j]) {
                    ready += process_time[j];
                    process_time[j] = 0;
                }
            }
            ready_processes[i] += ready;

            for (int j = 0; j < ready; j++)
                printf("w ");

            if (process_time[i] > quantum) {
                for (int j = 0; j < quantum ; j++)
                    printf("e ");
                process_time[i] -= quantum;
            }
            else {
                for (int j=0; j<process_time[i]; j++)
                    printf("e ");
                break;
            }
            ready = 0;
            for (int j = i + 1; j < amount; j++) {
                if (process_time[j]>=quantum) {
                    ready += quantum;
                    process_time[j] -= quantum;
                }
                else if (process_time[j]) {
                    ready += process_time[j];
                    process_time[j] = 0;
                }
            }
            for (int j = 0; j < ready; j++)
                printf("w ");
            ready_processes[i] += ready;
        }
        printf("\n");
        for(int j = 0; j < amount; j++)
            process_time[j] = process_time_copy[j];
    }
    printf("\n");
    printf("Number of process ");
    for(int i = 0; i < amount; i++) {
        printf("%d	", i + 1);
    }
    printf("\n");
    printf("Execution time    ");

    for (int i = 0; i < amount; i++) {
        printf("%d	", process_time_copy[i] + ready_processes[i]);
        sum += process_time_copy[i] + ready_processes[i];
    }
    printf("	%f", (float)(sum) / amount);
    sum = 0;
    printf("\n");
    printf("Waiting time      ");
    for (int i = 0; i < amount; i++) {
        printf("%d	", ready_processes[i]);
        sum += ready_processes[i];
    }
    printf("	%f", (float)sum / amount);

    printf("\n\n  ");

	// 2. Алгоритм SJF

    // Печать времени для процессов
    for (int count_time = 1; count_time <= 20; count_time++)
        printf("%d ", count_time);

    printf("\n");

    sum = 0;
    for (int j = 0; j < amount - 1; j++) {
        for (int i = 0; i < amount - 1 - j; i++) {
            if (process_time[i] > process_time[i+1]) {
                t = process_time[i];
                t_index = indexes[i];

                process_time[i] = process_time[i+1];
                indexes[i] = indexes[i+1];

                process_time[i+1] = t;
                indexes[i+1] = t_index;
            }
        }
    }
    for (int j = 0; j < amount; j++) {
        process_time_copy[j] = process_time[j];
        ready_processes[j] = 0;
    }
    for (int i = 0; i < amount; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < amount; j++) {
            if (indexes[j] == i) {
                index = j;
            }
        }
        while (process_time[index]) {
            ready = 0;
            for (int j=0; j < index; j++) {
                if (process_time[j] >= quantum) {
                    ready += quantum;
                    process_time[j] -= quantum;
                }
                else if (process_time[j]) {
                    ready += process_time[j];
                    process_time[j] = 0;
                }
            }
            ready_processes[index] += ready;
            for (int j = 0; j < ready; j++)
                printf("w ");
            if (process_time[index] > quantum) {
                for (int j = 0; j < quantum; j++)
                    printf("e ");
                process_time[index] -= quantum;
            }
            else {
                for (int j = 0; j < process_time[index]; j++)
                    printf("e ");
                break;
            }
            ready = 0;
            for (int j = index + 1; j < amount; j++) {
                if (process_time[j] >= quantum) {
                    ready += quantum;
                    process_time[j] -= quantum;
                }
                else if (process_time[j]) {
                    ready += process_time[j];
                    process_time[j] = 0;
                }
            }
            for (int j = 0; j < ready; j++)
                printf("w ");
            ready_processes[index] += ready;
        }
        printf("\n");
        for (int j = 0; j < amount; j++)
            process_time[j] = process_time_copy[j];
    }
    printf("\n");
    printf("Number of process ");
    for (int i = 0; i < amount; i++) {
        printf("%d	", i + 1);
    }
    printf("\n");
    printf("Execution time    ");
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount; j++)
            if (indexes[j] == i)
                index = j;
        printf("%d	", process_time_copy[index] + ready_processes[index]);
        sum += process_time_copy[i] + ready_processes[i];
    }
    printf("	%f", (float)sum / amount);
    sum=0;
    printf("\n");
    printf("Waiting time      ");
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount; j++)
            if (indexes[j] == i)
                index = j;
        printf("%d	", ready_processes[index]);
        sum += ready_processes[index];
    }
    printf("	%f", (float)sum / amount);

    return 0;
}
