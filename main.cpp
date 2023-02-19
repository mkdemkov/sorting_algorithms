/**
 * АиСД-2, 2023, задание 5. Демков Михаил Кириллович БПИ212. Среда разработки - CLion
*/
#include <iostream>
#include "array-generating/arrayGeneration.cpp"
#include "sorting-algorithms/bubbleSorts.cpp"
#include "sorting-algorithms/selectionSort.cpp"
#include "sorting-algorithms/insertionSort.cpp"
#include "sorting-algorithms/countingSort.cpp"
#include "sorting-algorithms/radixSort.cpp"
#include "sorting-algorithms/mergeSort.cpp"
#include "sorting-algorithms/quickSort.cpp"
#include "sorting-algorithms/heapSort.cpp"
#include "sorting-algorithms/shellSort.cpp"
#include "static/FileWriter.cpp"

/**
 * функция, копирующая массив
 * @param original откуда копировать
 * @param copy куда копировать
 * @param size размер массива
 */
void copyArray(const int *original, int *copy, int size) {
    for (int i = 0; i < size; ++i) {
        copy[i] = original[i];
    }
}

/**
 * перевод enum в строку
 * @param type тип массива
 * @return строка
 */
std::string enumToString(typeOfArray type) {
    switch (type) {
        case RANDOM_0_5: return "обычный 0-5";
        case RANDOM_0_4000: return "обычный 0-4000";
        case ALMOST_SORTED: return "почти отсорт. 0-4000";
        case SORTED_DESCENDING: return "обратно отсорт.";
    }
}

/**
 * функция для сортировки массива заданным методом, подсчет времени тоже здесь
 * @param unsorted_arr исхоный массив
 * @param type тип массива
 * @param left левая граница размера массива
 * @param right правая граница размера массива
 * @param step шаг для изменения размера массива
 * @param sortingAlgorithm алгоритм сортировки, которым сортируем
 * @return усредненное время работы алгоритма и усредненное число эл. операций
 */
std::pair<int64_t, int64_t> sort(int *unsorted_arr,
                                 int size,
                                 const std::function<std::pair<int64_t, int64_t>(int *,
                                                                                 int)> &sortingAlgorithm) {
    int *copy_to_sort = new int[size]; // этот массив - копию будем сортировать
    copyArray(unsorted_arr, copy_to_sort, size);
    int64_t total_time = 0, time, count,
        total_count = 0; // суммарное время сортировки за 25 прогонов
    // цикл для прогона одного и того же массива
    for (int j = 0; j < 25; ++j) {
        auto res = sortingAlgorithm(copy_to_sort, size);
        time = res.first;
        count = res.second;
        total_time += time;
        total_count += count;
        // тут аккуратный костыль, чтобы не вернуть сортируемый массив в исходное состояние
        copyArray(unsorted_arr, copy_to_sort, size);
    }
    // костыль чтобы отсортить массив в последний раз (26)
    auto res = sortingAlgorithm(unsorted_arr, size);
    time = res.first;
    count = res.second;
    total_time -= time; // и вычтем время потраченное на последнюю сортировку
    total_count -= count;
    int64_t avg_time = total_time / 25, avg_count = total_count / 25;
    return std::make_pair(avg_time, avg_count);
}

/**
 * основная функция, прогоняющая созданный массив по всем алгоритмам
 * @param type тип массива
 * @param arr прогоняемый массив
 * @param i размер массива
 * @param copy копия, которую будем прогонять
 */
void process(typeOfArray type_of_array, int *arr, int i, int *copy) {
    std::ofstream time_table("../tables/time_of_size.csv", std::ios::app); // откроем таблицы
    std::ofstream count_table("../tables/time_of_operations.csv", std::ios::app);
    // создаем массив со значениями типа type и прогоняем его по всем алгоритмам
    arr = generateArray(type_of_array, i); // генерирум массив, его будем гонять по сортировкам
    copy = new int[i];
    int64_t time, count; // время и число эл.операций
    std::string path = "../text-files-output/bubbleSort.txt";
    std::string type = enumToString(type_of_array); // тип массива как строка
    // начало блока пузырьковых сортировок
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (обычный пузырек):\n", copy, i);
    auto res = sort(copy, i, bubbleSort); // отсортируем копию
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "пузырек(обычный);" << i << ";" << time
               << "\n"; // записали в таблицы инфу
    count_table << type << ";" << "пузырек(обычный);" << i << ";" << count << "\n";

    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (Айверсон-1):\n", copy, i);
    res = sort(copy, i, bubbleSortOptimized1); // отсортируем копию
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "пузырек(айверсон-1);" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "пузырек(айверсон-1);" << i << ";" << count << "\n";

    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (Айверсон-2):\n", copy, i);
    res = sort(copy, i, bubbleSortOptimized2);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "пузырек(айверсон-2);" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "пузырек(айверсон-2);" << i << ";" << count << "\n";

    // здесь начинается блок сортировки выбором
    path = "../text-files-output/selectionSort.txt"; // обновим путь для вывода
    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка подсчетом):\n",
                            copy,
                            i);
    res = sort(copy, i, selectionSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "сортировка выбором;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "сортировка выбором;" << i << ";" << count << "\n";

    // блок сортировки вставками
    path = "../text-files-output/insertionSort.txt"; // обновим путь для вывода
    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка простыми вставками):\n",
                            copy,
                            i);
    res = sort(copy, i, insertionSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "сортировка простыми вставками;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "сортировка простыми вставками;" << i << ";" << count << "\n";

    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка бинарными вставками):\n",
                            copy,
                            i);
    res = sort(copy, i, binaryInsertionSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "сортировка бинарными вставками;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "сортировка бинарными вставками;" << i << ";" << count << "\n";

    // блок сортировки подсчетом
    path = "../text-files-output/countingSort.txt"; // обновим путь
    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка подсчетом):\n",
                            copy,
                            i);
    res = sort(copy, i, countingSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "сортировка подсчетом;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "сортировка подсчетом;" << i << ";" << count << "\n";

    // блок цифровой сортировки (сделал по основанию 256) - сам алгоритм подсмотрен в интернете
    path = "../text-files-output/radixSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (цифровая сортировка):\n",
                            copy,
                            i);
    res = sort(copy, i, radixSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "цифровая сортировка;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "цифровая сортировка;" << i << ";" << count << "\n";

    // блок сортировки слиянием
    path = "../text-files-output/mergeSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (сортировка слиянием):\n",
                            copy,
                            i);
    res = sort(copy, i, mergeSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "сортировка слиянием;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "сортировка слиянием;" << i << ";" << count << "\n";

    // блок быстрой сортировки
    path = "../text-files-output/quickSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (быстрая сортировка):\n",
                            copy,
                            i);
    res = sort(copy, i, quickSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "быстрая сортировка;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "быстрая сортировка;" << i << ";" << count << "\n";

    // блок пирамидальной сортировки
    path = "../text-files-output/heapSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (пирамидальная сортировка):\n",
                            copy,
                            i);
    res = sort(copy, i, heapSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "пирамидальная сортировка;" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "пирамидальная сортировка;" << i << ";" << count << "\n";

    // блок сортировки Шелла (последовательность Шелла)
    path = "../text-files-output/shellSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (сортировка Шелла(посл.Шелла)):\n",
                            copy,
                            i);
    res = sort(copy, i, shellSort);
    time = res.first;
    count = res.second;
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    time_table << type << ";" << "сортировка Шелла(посл.Шелла);" << i << ";" << time
               << "\n"; // занесем данные
    count_table << type << ";" << "сортировка Шелла(посл.Шелла);" << i << ";" << count << "\n";

    delete[] arr;
    delete[] copy;
    time_table.close();
    count_table.close();
}

int main() {
    FileWriter::clearAllFiles();
    int *arr = nullptr, *copy = nullptr;
    std::ofstream time_table("../tables/time_of_size.csv"); // откроем таблицы
    std::ofstream count_table("../tables/time_of_operations.csv");
    time_table << "Type of array;Sorting algorithm;Array size;Time(ns)" << "\n";
    count_table << "Type of array;Sorting algorithm;Array size;Elementary operations" << "\n";
    time_table.close();
    count_table.close();
    auto *types = new typeOfArray[4]{RANDOM_0_5, RANDOM_0_4000, ALMOST_SORTED, SORTED_DESCENDING};
    // цикл который пройдется по всем типам массива
    for (int t = 0; t < 4; ++t) {
        // цикл, который отвечает за размеры массива от 50 до 300
        for (int i = 50; i <= 300; i += 50) {
            process(types[t], arr, i, copy);
        }
        // цикл для массивов размером от 100 до 4100
        for (int i = 400; i <= 4100; i += 100) {
            process(types[t], arr, i, copy);
        }
    }
}