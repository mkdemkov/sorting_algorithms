#include <iostream>

/**
 * функция поиска максимума в массиве
 * @param arr массив
 * @param size размер массива
 * @return наибольший элемент
 */
int findMax(const int *arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/**
 * вспомогательная сортировка подсчетом для сортировки разрядов в СС о основанием 256
 * @param arr сортирукмый массив
 * @param size размер массива
 * @param exp текущий разряд
 */
void countingSort256(int *arr, int size, int exp) {
    auto *output = new int[size];
    int i, count[256] = {0};

    for (i = 0; i < size; i++) {
        count[(arr[i] / exp) % 256]++;
    }

    for (i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    for (i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 256] - 1] = arr[i];
        count[(arr[i] / exp) % 256]--;
    }

    for (i = 0; i < size; i++) {
        arr[i] = output[i];
    }
    delete[] output;
}

/**
 * цифровая сортировка по основанию 256
 * @param arr сортируемый массив
 * @param size размер массива
 */
int64_t radixSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int m = findMax(arr, size);

    for (int exp = 1; m / exp > 0; exp *= 256) {
        countingSort256(arr, size, exp);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}
