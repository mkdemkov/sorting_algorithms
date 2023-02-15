//
// Created by Михаил Демков on 14.02.2023.
//
#include "bubbleSorts.h"
#include "../array-generation-and-outputing/arrayGeneration.h"

/**
 * пузырьковая сортировка (самая примитивная)
 * @param arr - сортируемый массив
 * @param size - размер массива
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
