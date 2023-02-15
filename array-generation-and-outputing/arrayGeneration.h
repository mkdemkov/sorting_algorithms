//
// Created by Михаил Демков on 15.02.2023.
//

#ifndef KDZ1_ARRAY_GENERATION_ARRAYGENERATION_H_
#define KDZ1_ARRAY_GENERATION_ARRAYGENERATION_H_

#include "../bubbleSorts/bubbleSorts.h"
#include <fstream>

int *generateArray(typeOfArray type, int size);

void printArray(std::ifstream fin, int *arr);

#endif //KDZ1_ARRAY_GENERATION_ARRAYGENERATION_H_
