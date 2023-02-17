#include <iostream>

/**
 * функция поиска максимума в массиве
 * @param arr массив
 * @param size размер массива
 * @return наибольший элемент
 */
int findMax(const int *arr, int size, int64_t &count) {
    int max = arr[0];
    count += 2; // 2 присваивания
    for (int i = 1; i < size; i++) {
        count += 3; // 2 сравнения и ++
        if (arr[i] > max) {
            max = arr[i];
            ++count; // присваивание
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
void countingSort256(int *arr, int size, int exp, int64_t &counter) {
    auto *output = new int[size];
    int i, count[256] = {0};
    counter += 3; // 2 присваивания и выделение памяти

    ++counter; // присваивание в цикле
    for (i = 0; i < size; i++) {
        count[(arr[i] / exp) % 256]++;
        counter += 5; // сравнение, 2 ++, / и %
    }
    ++counter; // присваивание в цикле
    for (i = 1; i < 256; i++) {
        count[i] += count[i - 1];
        counter += 5; // сравнение, ++, +, присваивание и -
    }
    counter += 2; // присваивание и -
    for (i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 256] - 1] = arr[i];
        count[(arr[i] / exp) % 256]--;
        counter += 9; // сравнение, 2 --, 2 /, 2 %, - и присваивание
    }
    ++counter; // присваивание в цикле
    for (i = 0; i < size; i++) {
        arr[i] = output[i];
        counter += 3; // сравнение, ++ и присваивание
    }
    ++counter; // освобождение памяти
    delete[] output;
}

/**
 * цифровая сортировка по основанию 256
 * @param arr сортируемый массив
 * @param size размер массива
 */
std::pair<int64_t, int64_t> radixSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    ++count; // присваивание
    int m = findMax(arr, size, count);

    ++count; // присваивание в цикле
    for (int exp = 1; m / exp > 0; exp *= 256) {
        count += 4; // сравнение, /, * и присваивание
        countingSort256(arr, size, exp, count);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}
