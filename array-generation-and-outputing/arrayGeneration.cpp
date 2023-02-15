//
// Created by Михаил Демков on 15.02.2023.
//

#include "arrayGeneration.h"
#include <ctime>
#include <cstdlib>

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
            break;
        }
        case ALMOST_SORTED_DESCENDING: {
            break;
        }
    }
    return arr;
}

void printArray(std::ifstream fin, int *arr) {

}