cmake_minimum_required(VERSION 3.21)
project(KDZ1)

set(CMAKE_CXX_STANDARD 17)

add_library(sorting-algorithms STATIC
        sorting-algorithms/bubbleSorts.cpp
        sorting-algorithms/selectionSort.cpp
        sorting-algorithms/insertionSort.cpp
        sorting-algorithms/countingSort.cpp
        sorting-algorithms/radixSort.cpp
        sorting-algorithms/mergeSort.cpp
        sorting-algorithms/quickSort.cpp
        sorting-algorithms/heapSort.cpp)

add_library(array-generating STATIC
        array-generating/arrayGeneration.cpp)

add_executable(KDZ1 main.cpp static/FileWriter.cpp static/enum.h)
#add_executable(bubbleSorts bubbleSorts/bubbleSorts.cpp array-generating/arrayGeneration.cpp array-generating/arrayGeneration.h bubbleSorts/bubbleSorts.h array-generating/arrayOutputing.cpp array-generating/arrayOutputing.h)

