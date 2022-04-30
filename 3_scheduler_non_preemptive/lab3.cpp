/* Моделирование работы планировщика потоков заданий в однопроцессорной ОС
(режим - не вытесняющее планирование) FCFS, SJF*/

#include <stdio.h>
#include <stdlib.h>
using namespace std;


void print_result(int algorithm, int all_time, float work_time, float wait_time) {
    printf("Время обработки всех процессов: %d\n", all_time);
    printf("Среднее время выполнения: %0.1f\n", work_time);
    printf("Среднее время ожидания: %0.1f\n\n", wait_time);
}


int main() {
    int amount_of_process;

    printf("Введите количество процессов: ");
    scanf("%d", &amount_of_process);

    // Считывание процессов
    int* mas = (int*)malloc(amount_of_process * sizeof(int));
    for (int i=0; i < amount_of_process; i++) {
        printf("Введите время процесса %d: ", i + 1);
        scanf("%d", &mas[i]);
    }

    // 1. Алгоритм FCFS
    printf("\n1. Алгоритм FCFS\n");

    int all_time_FCFS = 0;
    int time = 0;
    int wait_time_FCFS = 0;

    for (int i=0; i < amount_of_process; i++) {
        all_time_FCFS += mas[i];
    }
    printf("   ");

    for (int i=0; i < all_time_FCFS; i++) {
        printf("%02d ", i+1);
    }
    printf("\n");

    for (int i=0; i < amount_of_process; i++) {
        printf("%02d ", i + 1);

        for (int j=0; j < time; j++) {
            printf("г  ");
            wait_time_FCFS++;
        }

        for (int j=0; j < mas[i]; j++) {
            printf("и  ");
            time++;
        }
        printf("\n");
    }

    int work_time_FCFS = 0;
    for (int i=0; i < amount_of_process; i++) work_time_FCFS += mas[i] * (amount_of_process - i);

    print_result(1, all_time_FCFS, ((float)work_time_FCFS) / amount_of_process, ((float)wait_time_FCFS) / amount_of_process);

    // 2. Алгоритм SJF
    printf("\n2. Алгоритм SJF\n");

    int all_time_SJF = 0;
    for (int i=0; i < amount_of_process; i++) all_time_SJF += mas[i];

    printf("   ");
    for (int i=0; i < all_time_SJF; i++) printf("%02d ", i + 1);
    printf("\n");

    int* order = (int*)malloc(amount_of_process * sizeof(int));

    for (int i=0; i < amount_of_process; i++) {
        order[i] = i;
    }

    for (int i=0; i < amount_of_process; i++) {
        for (int j=0; j< amount_of_process; j++) {
            if (mas[i] < mas[j]) {
                int t = mas[i];
                mas[i] = mas[j];
                mas[j] = t;

                t = order[i];
                order[i] = order[j];
                order[j] = t;
            }
        }
    }

    int wait_time_SGF;
    int work_time_SGF;

    for (int i=0; i < amount_of_process; i++) {
        int j=0;
        
        printf("%02d ", i + 1);
        while (order[j] != i) {
            for (int k=0; k < mas[j]; k++) printf("г  ");
            work_time_SGF += mas[j];
            wait_time_SGF += mas[j];
            j++;
        }
        for (int k=0; k < mas[j]; k++) printf("и  ");
        work_time_SGF += mas[j];
        printf("\n");
    }

    print_result(2, all_time_SJF, ((float)work_time_SGF) / amount_of_process, ((float)wait_time_SGF) / amount_of_process);
}
