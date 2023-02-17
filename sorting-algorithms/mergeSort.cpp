#include <iostream>
#include <vector>

/**
 * функция слияния двух отсортированных подмассивов
 * @param arr массив который надо "слить"
 * @param left левая граница
 * @param mid середина
 * @param right правая граница
 */
void merge(int *arr, int left, int mid, int right, int64_t &count) {
    count += 9; // 4 присваивания, 2 выделения памяти, 2 - и +
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *l = new int[n1];
    int *r = new int[n2];
    ++count; // присваивание в цикле
    for (int i = 0; i < n1; ++i) {
        count += 3; // сравнение, ++ и присваивание
        l[i] = 0;
    }
    ++count; // присваивание в цикле
    for (int i = 0; i < n2; ++i) {
        count += 3; // сравнение, ++ и присваивание
        r[i] = 0;
    }
    ++count; // присваивание в цикле
    for (int i = 0; i < n1; i++) {
        count += 4; // сравнение, ++, + и присваивание
        l[i] = arr[left + i];
    }
    ++count; // присваивание в цикле
    for (int j = 0; j < n2; j++) {
        count += 5; // сравнение, ++, 2 + и присваивание
        r[j] = arr[mid + 1 + j];
    }
    count += 3; // 3 присваивания
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        count += 2; // 2 сравнения в условии
        if (l[i] <= r[j]) {
            arr[k] = l[i];
            i++;
            count += 3; // сравнение, присваивание и ++
        } else {
            arr[k] = r[j];
            j++;
            count += 2; // присваивание и ++
        }
        ++count; // ++
        k++;
    }

    while (i < n1) {
        arr[k] = l[i];
        i++;
        k++;
        count += 4; // сравнение, присваивание и 2 ++
    }

    while (j < n2) {
        arr[k] = r[j];
        j++;
        k++;
        count += 4; // сравнение, присваивание и 2 ++
    }
    count += 2; // 2 раза высвобождение памяти
    delete[] l;
    delete[] r;
}

/**
 * вспомогательная функция сортировки
 * @param arr сортируемый массив
 * @param left левая граница
 * @param right правая граница
 */
void additionalMergeSort(int *arr, int left, int right, int64_t &count) {
    ++count; // сравнение в условии
    if (left >= right) {
        return;
    }
    count += 5; // присваивание, +, -, / и + в параметрах функции
    int mid = left + (right - left) / 2;
    additionalMergeSort(arr, left, mid, count);
    additionalMergeSort(arr, mid + 1, right, count);
    merge(arr, left, mid, right, count);
}

/**
 * сортировка слиянием
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах и кол-во элементарных операций
 */
std::pair<int64_t, int64_t> mergeSort(int *arr, int size) {
    int64_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    count += 3; // 2 присваивания и -
    int left = 0, right = size - 1;
    additionalMergeSort(arr, left, right, count);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return std::make_pair(duration.count(), count);
}

