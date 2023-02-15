//
// Created by Михаил Демков on 14.02.2023.
//
#include <iostream>
#include <fstream>
#include "../array-generation-and-outputing///arrayGeneration.h"
#include "bubbleSorts.h"

// пузырьковая сортировка (самая примитивная)
void bubbleSort(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        // в самой примитивной реализации на каждой итерации наибольший элемент в неотсортированной части массива всплывает в конец
        for (int j = 0; j < size - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void isSorted(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        bool flag = true; // массив отсортирован
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                flag = false;
            }
        }
        if (!flag) {
            std::cout << "Массив не отсортирован!\n";
            return;
        }
    }
    std::cout << "Массив отсортирован!\n";
}

// вспомогательная функция для вывода массива
void printArray(const int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ifstream fin("../input.txt");
    int n = 0;
    int *arr;
    // этот цикл для массивов размерами от 50 до 300 с шагом 50 со значениями от 0 до 5
    for (int i = 50; i <= 300; i += 50) {
        arr = generateArray(RANDOM_0_5, i);
        // printArray(arr, i);
        bubbleSort(arr, i);
        // printArray(arr, i);
        delete[] arr;
    }
    fin.close();

//    int *arr = new int[]{6, 5, 4, 3, 2, 1};
//    bubbleSort(arr, n);
//    printArray(arr, n);
//    delete[] arr;
}
