#include <iostream>

/**
 * сортировка подсчетом
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах и кол-во элементарных операций
 */
std::pair<int64_t, int64_t> countingSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    int *additional_arr = new int[4001]; // создадим доп. массив
    count += 2; // создание массива и присваивание - две эл. операции
    ++count; // присваивание в цикле i = 0
    for (int i = 0; i < 4001; ++i) {
        count += 3; // сравнение с 4001, инкремент и присваивание arr[i] = 0
        additional_arr[i] = 0;
    }
    ++count; // присваивание в цикле i = 0
    // заполним доп.массив
    for (int i = 0; i < size; ++i) {
        // сравнение с size, инкремент, присваивание и + (addit_arr[i] = addit_arr[i] + 1)
        count += 4;
        additional_arr[arr[i]]++;
    }
    ++count; // присваивание
    int cur = 0; // текущий индекс, на который вставляем элемент
    ++count; // присивание в цикле i = 0
    for (int i = 0; i < 4001; ++i) {
        count += 3; // сравнение с 4001, инкремент и !=
        if (additional_arr[i] != 0) {
            while (additional_arr[i] != 0) {
                count += 4; // !=, ++, = и --
                arr[cur++] = i;
                additional_arr[i]--;
            }
        }
    }
    ++count; // освобождегние памяти
    delete[] additional_arr;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}