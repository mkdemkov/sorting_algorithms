//
// Created by Михаил Демков on 15.02.2023.
//

#include "arrayOutputing.h"

void printArray(int *arr, int size, bool status) {
    std::ofstream out("../output.txt", std::ios::app);
    if (!status) {
        out << "Массив до сортировки(размер " << size << "):\n";
    } else {
        out << "Массив после сортировки(размер " << size << "):\n";
    }
    for (int i = 0; i < size; ++i) {
        out << arr[i] << " ";
    }
    out << "\n";
    out.close();
}