#include <iostream>

/**
 * алгоритм подсмотрен на хабре с лекции по сортировкам кучей, реализован самостоятельно
 * @param arr сортируемый массив
 * @param size размер массива
 * @param i индекс текущего максимума
 */
void heapify(int *arr, int size, int i) {
    int biggest_ind = i;          // фактически текущий родители
    int left_child = 2 * i + 1;   // левый потомок
    int right_child = 2 * i + 2;  // правый потомок
    // если левый потомок больше родителя (нарушение критерия кучи)
    if (left_child < size && arr[left_child] > arr[biggest_ind]) {
        biggest_ind = left_child;
    }
    // по аналогии если правый потомок больше родителя
    if (right_child < size && arr[right_child] > arr[biggest_ind]) {
        biggest_ind = right_child;
    }
    // если текущий ролитель (корень) изменился
    if (biggest_ind != i) {
        std::swap(arr[biggest_ind], arr[i]);
        heapify(arr, size, biggest_ind);
    }
}

/**
 * пирамидальная сортировка
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t heapSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }
    for (int i = size - 1; i >= 0; --i) {
        // меняем текущий корень с концом массива
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);  // хипуем оставшуюся кучу
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}