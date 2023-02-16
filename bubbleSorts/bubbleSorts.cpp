#include <iostream>

/**
 * пузырьковая сортировка (самая примитивная)
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t bubbleSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        // в самой примитивной реализации на каждой итерации наибольший элемент в неотсортированной части массива всплывает в конец
        for (int j = 0; j < size - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

/**
 * пузырьковая сортировка с уловием Айверсона 1
 * @param arr сортируемы массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t bubbleSortOptimized1(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        bool has_swaps; // флаг, показываюший были ли обмены
        for (int j = 0; j < size - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                has_swaps = true;
                std::swap(arr[j], arr[j + 1]);
            }
        }
        // если обменов не произошло, значит массив отсортирован
        if (!has_swaps) {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

/**
 * пузырьковая сортировка с условием айверсона-2
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t bubbleSortOptimized2(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int last_swap = size - 1, help;
    for (int i = 0; i < size; ++i) {
        help = last_swap; // вспомогательная перемнная, чтобы не потерять позицию последнего свапа
        last_swap = 0;
        // в цикле идем до позиции последнего обмена
        for (int j = 0; j < help; ++j) {
            if (arr[j] > arr[j + 1]) {
                last_swap = j; // обновляем позицию ласт обмена
                std::swap(arr[j], arr[j + 1]);
            }
        }
        // если позиция осталась 0, то обменов не было
        if (last_swap == 0) {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}
