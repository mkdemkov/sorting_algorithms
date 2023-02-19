/**
 * АиСД-2, 2023, задание 5. Демков Михаил Кириллович БПИ212. Среда разработки - CLion
*/
#include <iostream>

/**
 * пузырьковая сортировка (самая примитивная)
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах и кол-во элементарных операций
 */
std::pair<int64_t, int64_t> bubbleSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    count += 2; // эта эл. операция во внешнем цикле i = 0 и внутреннем j = 0 (присвоение);
    for (int i = 0; i < size; ++i) {
        count += 2; // сравнение с size и инкремент
        // в самой примитивной реализации на каждой итерации наибольший элемент в неотсортированной части массива всплывает в конец
        for (int j = 0; j < size - 1; ++j) {
            count += 2; // сравнение и инкремент
            count += 2; // сравнение и +
            if (arr[j] > arr[j + 1]) {
                ++count; // свап
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}

/**
 * пузырьковая сортировка с уловием Айверсона 1
 * @param arr сортируемы массив
 * @param size размер массива
 * @return время сортировки в наносекундах и кол-во элементарных операций
 */
std::pair<int64_t, int64_t> bubbleSortOptimized1(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    count += 2; // присваивания i = 0 и j = 0 в циклах
    for (int i = 0; i < size; ++i) {
        count += 3; // сравнение с size, ++ и присваивание has_swaps = false;
        bool has_swaps; // флаг, показываюший были ли обмены
        for (int j = 0; j < size - 1; ++j) {
            count += 4; // сравнение с size - 1, ++, + и сравнение > ниже
            if (arr[j] > arr[j + 1]) {
                count += 3; // присваивание, + и swap
                has_swaps = true;
                std::swap(arr[j], arr[j + 1]);
            }
        }
        ++count; // сравнение !=
        // если обменов не произошло, значит массив отсортирован
        if (!has_swaps) {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}

/**
 * пузырьковая сортировка с условием айверсона-2
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах и кол-во элементарных операций
 */
std::pair<int64_t, int64_t> bubbleSortOptimized2(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    ++count; // присваивание last_swap = size - 1
    int last_swap = size - 1, help;
    count += 2; // присваивания i = 0 и j = 0 в циклах
    for (int i = 0; i < size; ++i) {
        count += 4; // сравнение с size, ++ и 2 присваивания ниже
        help = last_swap; // вспомогательная перемнная, чтобы не потерять позицию последнего свапа
        last_swap = 0;
        // в цикле идем до позиции последнего обмена
        for (int j = 0; j < help; ++j) {
            count += 4; // сравнение с help, ++, + и сравнение > ниже
            if (arr[j] > arr[j + 1]) {
                last_swap = j; // обновляем позицию ласт обмена
                std::swap(arr[j], arr[j + 1]);
                count += 3; // присваивание, + и swap
            }
        }
        ++count; // сравнение == ниже
        // если позиция осталась 0, то обменов не было
        if (last_swap == 0) {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}
