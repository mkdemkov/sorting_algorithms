/**
 * АиСД-2, 2023, задание 5. Демков Михаил Кириллович БПИ212. Среда разработки - CLion
*/
#include <iostream>
#include "../static/enum.h"

// вспомогат функция для генерации частично отсорт. и обратно отсорт. массивов
int64_t sortArray(int *arr, int size) {
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
 * функиция генерации массива заданного типа и размера
 * @param type тип массива
 * @param size размер массива
 * @return указатель на созданный массив
 */
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
            sortArray(sorted_half, half); // отсортируем часть массива
            // обновим исходный массив
            for (int i = 0; i < half; ++i) {
                arr[i] = sorted_half[i];
            }
            delete[] sorted_half;
            break;
        }
        case SORTED_DESCENDING: {
            // заполним массив значениями от 0 до 4000
            for (int i = 0; i < size; ++i) {
                arr[i] = std::rand() % 4001;
            }
            sortArray(arr, size); // отсортируем как обычно
            int *copy = new int[size]; // создадим доп. массив, который отсортируем по убыванию
            // заполним доп. массив
            int j = 0;
            for (int i = size - 1; i >= 0; --i) {
                copy[j++] = arr[i];
            }
            // заполним основной массив
            for (int i = 0; i < size; ++i) {
                arr[i] = copy[i];
            }
//            for (int i = 0; i < size; ++i) {
//                std::cout << copy[i] << " ";
//            }
//            std::cout << "\n";
            delete[] copy;
        }
    }
    return arr;
}