//
// Created by Михаил Демков on 14.02.2023.
//
#include "bubbleSorts.h"
#include "../array-generation-and-outputing/arrayGeneration.h"

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

//void isSorted(const int *arr, int size) {
//    for (int i = 0; i < size; ++i) {
//        bool flag = true; // массив отсортирован
//        for (int j = i + 1; j < size; ++j) {
//            if (arr[i] > arr[j]) {
//                flag = false;
//            }
//        }
//        if (!flag) {
//            std::cout << "Массив не отсортирован!\n";
//            return;
//        }
//    }
//    std::cout << "Массив отсортирован!\n";
//}

void bubbleMain() {
//    int *arr;
//    bool flag; // флаг, чтобы надпись "пузырьковая сортировка" вывести один раз
//    // этот цикл для массивов размерами от 50 до 300 с шагом 50 со значениями от 0 до 5
//    for (int i = 50; i <= 300; i += 50) {
//        arr = generateArray(RANDOM_0_5, i);
//        // костыль, но хотелось чтобы весь вывод в рамках одной функции был
//        if (!flag) {
//            printArray(arr,
//                       i,
//                       false,
//                       "Пузырьковая сортировка\n"); // выведем в файл output.txt массив до сортировки
//        } else {
//            printArray(arr, i, false, ""); // выведем в файл output.txt массив до сортировки
//        }
//        auto time = bubbleSort(arr, i); // сортируем
//        printArray(arr, i, true, ""); // выведем после сортировки
//        delete[] arr;
//    }
}
