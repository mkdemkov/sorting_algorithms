#include <iostream>

/**
 * доп.функция, которая берет первый элемент опорным и ставит все что меньше слева и все что больше справа
 * @param arr массив
 * @param left левая граница
 * @param right правая граница
 * @return индекс опорного элемента после преобразований
 */
int partition(int *arr, int left, int right) {
    int pivot = arr[left];
    int i = left + 1, j = right;
    while (true) {
        while (i <= j && arr[i] <= pivot) {
            ++i;
        }
        while (i <= j && arr[j] >= pivot) {
            --j;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
        } else {
            break;
        }
    }
    std::swap(arr[left], arr[j]);
    return j;
}

/**
 * вспомогательная функция для классической быстрой сортировки
 * @param arr сортируемый массив
 * @param left левая граница
 * @param right правая граница
 */
void additionalQuickSort(int *arr, int left, int right) {
    if (left < right) {
        int pivot_ind = partition(arr, left, right);
        additionalQuickSort(arr, left, pivot_ind - 1);
        additionalQuickSort(arr, pivot_ind + 1, right);
    }
}

/**
 * быстрая сортировка
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t quickSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int left = 0, right = size - 1;
    additionalQuickSort(arr, left, right);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}