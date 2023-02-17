#include <iostream>

/**
 * сортировка Шелла (последовательность Шелла)
 * @param arr сортируемый массив
 * @param size размер массив
 * @return время сортировки в наносекундах
 */
int64_t shellSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    // расстояние изначально половина размера
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}