#include <iostream>

/**
 * сортировка Шелла (последовательность Шелла)
 * @param arr сортируемый массив
 * @param size размер массив
 * @return время сортировки в наносекундах
 */
std::pair<int64_t, int64_t> shellSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    count += 2; // присваивание и / в цикле ниже
    // расстояние изначально половина размера
    for (int gap = size / 2; gap > 0; gap /= 2) {
        count += 3; // сравнение, /= и присваивание в цикле ниже
         for (int i = gap; i < size; ++i) {
             count += 3; // сравнение, ++ и присваивание
            int temp = arr[i];
            int j;
            ++count; // присваивание
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                count += 6; // 2 сравнения, 2 -, -= и присваивания
            }
            ++count; // присваивание
            arr[j] = temp;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}