#include <iostream>

/**
 * сортировка выбором
 * @param arr сортируемый массив
 * @param size размера массива
 * @return время сортировки в наносекундах
 */
std::pair<int64_t, int64_t> selectionSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    int index_of_min;
    ++count; // присваивание в цикле
    for (int i = 0; i < size - 1; ++i) {
        count += 4; // сравнение, -, ++ и присваивание
        index_of_min = i;
        count += 2; // присваивание в цикле и +
        for (int j = i + 1; j < size; ++j) {
            count += 3; // сравнение, ++ и сравнение в условии ниже
            if (arr[j] < arr[index_of_min]) {
                index_of_min = j;
                ++count; // присваивание
            }
        }
        ++count; // сравнение
        if (index_of_min != i) {
            ++count; // swap
            std::swap(arr[i], arr[index_of_min]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}