//
// Created by Михаил Демков on 15.02.2023.
//

#include "arrayGeneration.h"

int *generateArray(typeOfArray type, int size) {
    int *arr = new int[size];
    std::srand(std::time(nullptr));
    switch (type) {
        case RANDOM_0_5: {
            for (int i = 0; i < size; ++i) {
                arr[i] = std::rand() % 6; // генерация рандомного числа от 0 до 5
            }
            break;
        }
        case RANDOM_0_4000: {
            for (int i = 0; i < size; ++i) {
                arr[i] = std::rand() % 4001; // генерация рандомного числа от 0 до 4000
            }
            break;
        }
        case ALMOST_SORTED: {
            int half = size / 2;
            int *sorted_half = new int[half];
            for (int i = 0; i < size; ++i) {
                arr[i] = std::rand() % 4001;
            }
            // тут мы копируем часть массива, чтобы отсортировать его
            for (int i = 0; i < half; ++i) {
                sorted_half[i] = arr[i];
            }
            bubbleSort(sorted_half, half); // отсортируем часть массива
            // обновим исходный массив
            for (int i = 0; i < half; ++i) {
                arr[i] = sorted_half[i];
            }
            delete[] sorted_half;
            break;
        }
        case SORTED_DESCENDING: {
            break;
        }
    }
    return arr;
}