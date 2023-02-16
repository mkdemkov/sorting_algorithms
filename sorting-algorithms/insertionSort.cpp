#include <iostream>

/**
 * сортировка простыми вставками
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t insertionSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int cur; // текущий элемент, который вставляем в отсортированную часть
    // идем с единицы, т.к массив из 1-го элемента отсортирован
    for (int i = 1; i < size; ++i) {
        cur = arr[i];
        int j = i - 1; // ставим указатель на конец отсортированной части
        while (j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j]; // таким образом сдвигаем вправо все элементы
            --j;
        }
        arr[j + 1] = cur;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}