#include <iostream>

/**
 * сортировка простыми вставками
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t insertionSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int cur; // текущий элемент, который вставляем в отсортированную часть
    // идем с единицы, т.к массив из 1-го элемента отсортирован
    for (int i = 1; i < size; ++i) {
        cur = arr[i];
        int j = i - 1; // ставим указатель на конец отсортированной части
        while (j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j]; // таким образом сдвигаем вправо все элементы
            --j;
        }
        arr[j + 1] = cur;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

int binarySearch(const int *arr, int el, int left, int right) {
    // если левая граница совпадает с правой либо стала больше, то проверяем условия и возвращаем нужную позицию
    if (right <= left) {
        return el > arr[left] ? left + 1 : left;
    }
    int mid = (right + left) / 2;
    // если элемент совпадает с центральным, вставляем справа
    if (el == arr[mid]) {
        return mid + 1;
    }
    if (el > arr[mid]) {
        return binarySearch(arr, el, mid + 1, right); // базово сдвигаем границы
    }
    return binarySearch(arr, el, left, mid - 1);
}

/**
 * сортировка бинарными вставками
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t binaryInsertionSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int ind, cur; // ind - индекс элемента больше нашего, cur - текущий элемент
    for (int i = 1; i < size; ++i) {
        cur = arr[i];
        int j = i - 1; // ставим указатель на последний элемент отсортированой части массива
        ind = binarySearch(arr, cur, 0, j);
        // двигаем все элементы с места вставки до конца отсортированной части массива
        while (j >= ind) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = cur;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}