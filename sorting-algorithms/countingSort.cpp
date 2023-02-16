#include <iostream>

/**
 * сортировка подсчетом
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t countingSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int *additional_arr = new int[4001]; // создадим доп. массив
    for (int i = 0; i < 4001; ++i) {
        additional_arr[i] = 0;
    }
    // заполним доп.массив
    for (int i = 0; i < size; ++i) {
        additional_arr[arr[i]]++;
    }
    int cur = 0; // текущий индекс, на который вставляем элемент
    for (int i = 0; i < 4001; ++i) {
        if (additional_arr[i] != 0) {
            while (additional_arr[i] != 0) {
                arr[cur++] = i;
                additional_arr[i]--;
            }
        }
    }
    delete[] additional_arr;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}