#include <iostream>
#include <vector>

/**
 * функция слияния двух отсортированных подмассивов
 * @param arr массив который надо "слить"
 * @param left левая граница
 * @param mid середина
 * @param right правая граница
 */
void merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *l = new int[n1];
    int *r = new int[n2];
    for (int i = 0; i < n1; ++i) {
        l[i] = 0;
    }
    for (int i = 0; i < n2; ++i) {
        r[i] = 0;
    }
//    std::vector<int> l(n1);
//    std::vector<int> r(n2);
    for (int i = 0; i < n1; i++) {
        l[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        r[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            arr[k] = l[i];
            i++;
        } else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = l[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = r[j];
        j++;
        k++;
    }
    delete[] l;
    delete[] r;
}

/**
 * вспомогательная функция сортировки
 * @param arr сортируемый массив
 * @param left левая граница
 * @param right правая граница
 */
void additionalMergeSort(int *arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    additionalMergeSort(arr, left, mid);
    additionalMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

/**
 * сортировка слиянием
 * @param arr сортируемый массив
 * @param size размер массива
 * @return время сортировки в наносекундах
 */
int64_t mergeSort(int *arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    int left = 0, right = size - 1;
    additionalMergeSort(arr, left, right);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

