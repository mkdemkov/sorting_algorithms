#include <iostream>

/**
 * сортировка выбором
 * @param arr сортируемый массив
 * @param size размера массива
 * @return время сортировки в наносекундах
 */
int64_t selectionSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int index_of_min;
    for (int i = 0; i < size - 1; ++i) {
        index_of_min = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[index_of_min]) {
                index_of_min = j;
            }
        }
        if (index_of_min != i) {
            std::swap(arr[i], arr[index_of_min]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}