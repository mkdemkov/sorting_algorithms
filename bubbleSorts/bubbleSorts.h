//
// Created by Михаил Демков on 15.02.2023.
//

#ifndef KDZ1_BUBBLESORTS_BUBBLESORTS_H_
#define KDZ1_BUBBLESORTS_BUBBLESORTS_H_

// #include "../array-generation-and-outputing/arrayGeneration.h"
#include "../array-generation-and-outputing/arrayOutputing.h"
#include <iostream>
#include <chrono>

enum typeOfArray {
    RANDOM_0_5,
    RANDOM_0_4000,
    ALMOST_SORTED,
    ALMOST_SORTED_DESCENDING
};

int64_t bubbleSort(int *arr, int size);


//void isSorted(const int *arr, int size);

#endif //KDZ1_BUBBLESORTS_BUBBLESORTS_H_
