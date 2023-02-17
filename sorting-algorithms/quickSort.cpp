#include <iostream>

/**
 * доп.функция, которая берет первый элемент опорным и ставит все что меньше слева и все что больше справа
 * @param arr массив
 * @param left левая граница
 * @param right правая граница
 * @return индекс опорного элемента после преобразований
 */
int partition(int *arr, int left, int right, int64_t &count) {
    count += 4; // 3 присваивания и +
    int pivot = arr[left];
    int i = left + 1, j = right;
    while (true) {
        while (i <= j && arr[i] <= pivot) {
            ++i;
            count += 3; // 2 сравнения и ++
        }
        while (i <= j && arr[j] >= pivot) {
            --j;
            count += 3; // 2 сравнения и --
        }
        ++count; // сравнение
        if (i <= j) {
            ++count; // swap
            std::swap(arr[i], arr[j]);
        } else {
            break;
        }
    }
    ++count; // swap
    std::swap(arr[left], arr[j]);
    return j;
}

/**
 * вспомогательная функция для классической быстрой сортировки
 * @param arr сортируемый массив
 * @param left левая граница
 * @param right правая граница
 */
void additionalQuickSort(int *arr, int left, int right, int64_t &count) {
    ++count; // сравнение
    if (left < right) {
        count += 3; // присваивание, - и + в параметрах функии
        int pivot_ind = partition(arr, left, right, count);
        additionalQuickSort(arr, left, pivot_ind - 1, count);
        additionalQuickSort(arr, pivot_ind + 1, right, count);
    }
}

/**
 * быстрая сортировка
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах и кол-во элементарных операций
 */
std::pair<int64_t, int64_t> quickSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    count += 3; // 2 присваивание и - ниже
    int left = 0, right = size - 1;
    additionalQuickSort(arr, left, right, count);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}