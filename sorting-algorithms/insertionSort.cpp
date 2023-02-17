#include <iostream>

/**
 * сортировка простыми вставками
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
std::pair<int64_t, int64_t> insertionSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    int cur; // текущий элемент, который вставляем в отсортированную часть
    // идем с единицы, т.к массив из 1-го элемента отсортирован
    ++count; // присваивание i = 1 в цикле
    for (int i = 1; i < size; ++i) {
        count += 5; // сравнение с size, ++, присваивание cur = arr[i], присваивание и - ниже
        cur = arr[i];
        int j = i - 1; // ставим указатель на конец отсортированной части
        while (j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j]; // таким образом сдвигаем вправо все элементы
            --j;
            count += 5; // 2 сравнения в условии, +, присваивание и --
        }
        count += 2; // присваивание и +
        arr[j + 1] = cur;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}

int binarySearch(const int *arr, int el, int left, int right, int64_t &count) {
    // если левая граница совпадает с правой либо стала больше, то проверяем условия и возвращаем нужную позицию
    ++count; // сравнение в условии
    if (right <= left) {
        if (el > arr[left]) {
            ++count; // по условию в return возможна операция +
        }
        return el > arr[left] ? left + 1 : left;
    }
    count += 4; // присваивание, +, сравнение в условии ниже и /
    int mid = (right + left) / 2;
    // если элемент совпадает с центральным, вставляем справа
    if (el == arr[mid]) {
        ++count; // +
        return mid + 1;
    }
    count += 2; // сравнение в условии и + в параметрах
    if (el > arr[mid]) {
        return binarySearch(arr, el, mid + 1, right, count); // базово сдвигаем границы
    }
    ++count; // - в параметрах функции
    return binarySearch(arr, el, left, mid - 1, count);
}

/**
 * сортировка бинарными вставками
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
std::pair<int64_t, int64_t> binaryInsertionSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    int ind, cur; // ind - индекс элемента больше нашего, cur - текущий элемент
    ++count; // присваивание в цикле
    for (int i = 1; i < size; ++i) {
        // сравнение с size, ++, присваивание arr[i] и j, - и присваивание результата бин.поиска
        count += 6;
        cur = arr[i];
        int j = i - 1; // ставим указатель на последний элемент отсортированой части массива
        ind = binarySearch(arr, cur, 0, j, count);
        // двигаем все элементы с места вставки до конца отсортированной части массива
        while (j >= ind) {
            arr[j + 1] = arr[j];
            --j;
            count += 4; // сравнение >=, +, присваивание и --
        }
        count += 2; // присваивание и +
        arr[j + 1] = cur;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}