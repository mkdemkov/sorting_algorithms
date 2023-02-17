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
 * @return усредненное время работы алгоритма
 */
int64_t sort(int *unsorted_arr,
             int size,
             const std::function<int64_t(int *, int)> &sortingAlgorithm) {
    int *copy_to_sort = new int[size]; // этот массив - копию будем сортировать
    copyArray(unsorted_arr, copy_to_sort, size);
    int64_t total_time = 0, time; // суммарное время сортировки за 25 прогонов
    // цикл для прогона одного и того же массива
    for (int j = 0; j < 25; ++j) {
        time = sortingAlgorithm(copy_to_sort, size);
        total_time += time;
        // тут аккуратный костыль, чтобы не вернуть сортируемый массив в исходное состояние
        copyArray(unsorted_arr, copy_to_sort, size);
    }
    // костыль чтобы отсортить массив в последний раз (26)
    time = sortingAlgorithm(unsorted_arr, size);
    total_time -= time; // и вычтем время потраченное на последнюю сортировку
    int64_t avg_time = total_time / 25;
    return avg_time;
}

/**
 * основная функция, прогоняющая созданный массив по всем алгоритмам
 * @param type тип массива
 * @param arr прогоняемый массив
 * @param i размер массива
 * @param copy копия, которую будем прогонять
 */
void process(typeOfArray type_of_array, int *arr, int i, int *copy) {
    std::ofstream table("../tables/time_of_size.csv", std::ios::app); // откроем таблицу
    // создаем массив со значениями типа type и прогоняем его по всем алгоритмам
    arr = generateArray(type_of_array, i); // генерирум массив, его будем гонять по сортировкам
    copy = new int[i];
    std::string path = "../text-files-output/bubbleSort.txt";
    std::string type = enumToString(type_of_array); // тип массива как строка
    // начало блока пузырьковых сортировок
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (обычный пузырек):\n", copy, i);
    int64_t time = sort(copy, i, bubbleSort); // отсортируем копию
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "пузырек(обычный);" << i << ";" << time
          << "\n"; // записали в таблицу инфу

    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (Айверсон-1):\n", copy, i);
    time = sort(copy, i, bubbleSortOptimized1); // отсортируем копию
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "пузырек(айверсон-1);" << i << ";" << time
          << "\n"; // занесем данные

    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (Айверсон-2):\n", copy, i);
    time = sort(copy, i, bubbleSortOptimized2);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "пузырек(айверсон-2);" << i << ";" << time
          << "\n"; // занесем данные

    // здесь начинается блок сортировки выбором
    path = "../text-files-output/selectionSort.txt"; // обновим путь для вывода
    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка подсчетом):\n",
                            copy,
                            i);
    time = sort(copy, i, selectionSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "сортировка выбором;" << i << ";" << time
          << "\n"; // занесем данные

    // блок сортировки вставками
    path = "../text-files-output/insertionSort.txt"; // обновим путь для вывода
    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка простыми вставками):\n",
                            copy,
                            i);
    time = sort(copy, i, insertionSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "сортировка простыми вставками;" << i << ";" << time
          << "\n"; // занесем данные

    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка бинарными вставками):\n",
                            copy,
                            i);
    time = sort(copy, i, binaryInsertionSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "сортировка бинарными вставками;" << i << ";" << time
          << "\n"; // занесем данные

    // блок сортировки подсчетом
    path = "../text-files-output/countingSort.txt"; // обновим путь
    copyArray(arr, copy, i);
    FileWriter::outputArray(path,
                            "Массив до сортировки (сортировка подсчетом):\n",
                            copy,
                            i);
    time = sort(copy, i, countingSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "сортировка подсчетом;" << i << ";" << time
          << "\n"; // занесем данные

    // блок цифровой сортировки (сделал по основанию 256) - сам алгоритм подсмотрен в интернете
    path = "../text-files-output/radixSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (цифровая сортировка):\n",
                            copy,
                            i);
    time = sort(copy, i, radixSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "цифровая сортировка;" << i << ";" << time
          << "\n"; // занесем данные

    // блок сортировки слиянием
    path = "../text-files-output/mergeSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (сортировка слиянием):\n",
                            copy,
                            i);
    time = sort(copy, i, mergeSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "сортировка слиянием;" << i << ";" << time
          << "\n"; // занесем данные

    // блок быстрой сортировки
    path = "../text-files-output/quickSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (быстрая сортировка):\n",
                            copy,
                            i);
    time = sort(copy, i, quickSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "быстрая сортировка;" << i << ";" << time
          << "\n"; // занесем данные

    // блок пирамидальной сортировки
    path = "../text-files-output/heapSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (пирамидальная сортировка):\n",
                            copy,
                            i);
    time = sort(copy, i, heapSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "пирамидальная сортировка;" << i << ";" << time
          << "\n"; // занесем данные

    // блок сортировки Шелла (последовательность Шелла)
    path = "../text-files-output/shellSort.txt";
    copyArray(arr, copy, i);
    FileWriter::outputArray(path, "Массив до сортировки (сортировка Шелла(посл.Шелла)):\n",
                            copy,
                            i);
    time = sort(copy, i, shellSort);
    FileWriter::outputArray(path, "Массив после сортировки:\n", copy, i);
    table << type << ";" << "сортировка Шелла(посл.Шелла);" << i << ";" << time
          << "\n"; // занесем данные

    table.close();
}

int main() {
    FileWriter::clearAllFiles();
    int *arr = nullptr, *copy = nullptr;
    std::ofstream table("../tables/time_of_size.csv"); // откроем таблицу
    table << "Вид массива;Метод сортировки;Размер массива;Время(нс)" << "\n";
    table.close();
    auto *types = new typeOfArray[4]{RANDOM_0_5, RANDOM_0_4000, ALMOST_SORTED, SORTED_DESCENDING};
    // цикл который пройдется по всем типам массива
    for (int t = 0; t < 4; ++t) {
        // цикл, который отвечает за размеры массива от 50 до 300
        for (int i = 50; i <= 300; i += 50) {
            process(types[t], arr, i, copy);
        }
        // цикл для массивов размером от 100 до 4100
        for (int i = 100; i < 4100; i += 100) {
            process(types[t], arr, i, copy);
        }
    }
}