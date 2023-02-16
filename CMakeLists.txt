cmake_minimum_required(VERSION 3.21)
project(KDZ1)

set(CMAKE_CXX_STANDARD 17)

add_library(sorting-algorithms STATIC
        sorting-algorithms/bubbleSorts.cpp
        sorting-algorithms/selectionSort.cpp
        sorting-algorithms/insertionSort.cpp)

add_library(array-generation-and-outputing STATIC
        array-generation-and-outputing/arrayGeneration.cpp
        )

add_executable(KDZ1 main.cpp static/FileWriter.cpp static/enum.h)
#add_executable(bubbleSorts bubbleSorts/bubbleSorts.cpp array-generation-and-outputing/arrayGeneration.cpp array-generation-and-outputing/arrayGeneration.h bubbleSorts/bubbleSorts.h array-generation-and-outputing/arrayOutputing.cpp array-generation-and-outputing/arrayOutputing.h)

