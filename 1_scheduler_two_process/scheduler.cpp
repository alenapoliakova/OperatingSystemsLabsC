#include <iostream>
using namespace std;

int main(){
    // system("chcp 65001");  -  для отображения русского языка
    int amount;
    cout << "Write amount of processes: ";
    cin >> amount;

    int arr[amount];
    for (int i=0; i<=(amount-1); i++){
        cout << "Write time for " << i+1 << " process: ";
        int time_for_process;
        cin >> time_for_process;
        arr[i] = time_for_process;
    }

    // Сортировка массива пузырьком (по убыванию)
    for (int i=1; i<amount; ++i){
        for (int r=0; r<amount-i; r++){
            if (arr[r] < arr[r+1]){
                int temp = arr[r];
                arr[r] = arr[r+1];
                arr[r+1] = temp;
            }
        }
    }

    /* Выведем отсортированный массив */
    cout << "Sorted processes: ";
    for (int i=0; i<amount; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    int processor_1[amount];
    int processor_2[amount];

    int position_1=0;
    int sum_1=0;

    int position_2=0;
    int sum_2=0;

    for (int i=0; i<amount; i++){
        if (sum_1 + arr[i] <= sum_2 + arr[i]){
            processor_1[position_1] = arr[i];
            position_1++;
            sum_1 += arr[i];
        }
        else {
            processor_2[position_2] = arr[i];
            position_2++;
            sum_2 += arr[i];
        }
    }

    cout << "Processor 1: ";
    for (int i=0; i<position_1; i++){
        cout << processor_1[i] << " ";
    }
    cout << endl;

    cout << "Processor 2: ";
    for (int i=0; i<position_2; i++){
        cout << processor_2[i] << " ";
    }
    cout << endl;


    return 0;
};
