#include <iostream>
#include "array-generation-and-outputing/arrayGeneration.cpp"
#include "bubbleSorts/bubbleSorts.cpp"
#include "FileWriter.cpp"
// #include "array-generation-and-outputing/arrayOutputing.h"
//#include "enum.cpp"

void copyArray(const int *original, int *copy, int size) {
    for (int i = 0; i < size; ++i) {
        copy[i] = original[i];
    }
}

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
    // std::ofstream out("../output.txt", std::ios::app);
    // std::ofstream table("../tables/time_of_size.csv", std::ios::app);

    //unsorted_arr = generateArray(type, i);
    int *copy_to_sort = new int[size]; // этот массив - копию будем сортировать
    copyArray(unsorted_arr, copy_to_sort, size);
    // out.open("../output.txt", std::ios::app);
    // out.close();
    // printArray(copy_to_sort, size, false); // выведем неотсортированный массив
    int64_t total_time = 0, time; // суммарное время сортировки за 25 прогонов
    // цикл для прогона одного и того же массива
    for (int j = 0; j < 25; ++j) {
        time = sortingAlgorithm(copy_to_sort, size);
        total_time += time;
        // тут аккуратный костыль, чтобы не вернуть сортируемый массив в исходное состояние
        if (j != 24)
            copyArray(unsorted_arr, copy_to_sort, size);
    }
    int64_t avg_time = total_time / 25;
    // out.open("../output.txt", std::ios::app);
    // printArray(copy_to_sort, size, true); // выведем массив после сортировки
    // out << "Усредненное время сортировки: " << avg_time << "нс\n\n";
    // out.close();
    // std::string type_string = enumToString(type); // тип массива как строка
    // теперь добавим результаты измерения времени в csv таблицу
    // table << type_string << ";пузырьковая(обычн);" << i << ";" << avg_time << "\n";
    return avg_time;
    // out.close();
    // table.close();
}

int main() {
    // int *unsorted_arr = nullptr;
    int *arr_0_5, *arr_0_4000, *arr_almost_sorted, *arr_sorted_descending, *copy;
    // std::ofstream out("../output.txt");
    std::ofstream table("../tables/time_of_size.csv"); // откроем таблицу
    table << "Вид массива;Метод сортировки;Размер массива;Время(нс)" << "\n";
    // создадим массив с типами
    // auto *types = new typeOfArray[4]{RANDOM_0_5, RANDOM_0_4000, ALMOST_SORTED, SORTED_DESCENDING};
    // table.close();
    // цикл, который отвечает за размеры массива
    for (int i = 50; i <= 300; i += 50) {
        // out << "Сейчас будут генерироваться и сортироваться массивы размера " << i << "\n";
        // создаем массив со значениями от 0 до 5 и прогоняем по всем алгоритмам
        arr_0_5 = generateArray(RANDOM_0_5, i); // генерирум массив, его будем гонять по сортировкам
        copy = new int[i];
        copyArray(arr_0_5, copy, i);
        FileWriter fw("../text-files-output/bubbleSort.txt");
        // out << "Массив со значениями от 0 до 5\n";
        // out.close(); // закрываем, т.к для удобства внутри сортировки выводим массив до / после сортировки
        fw.outputArray("Массив до сортировки (обычный пузырек):\n", copy, i);
        int64_t time = sort(copy, i, bubbleSort); // отсортируем копию
        for (int j = 0; j < i; ++j) {
            std::cout << copy[j] << " ";
        }
        std::cout << "\n";
        fw.outputArray("Массив после сортировки:\n", copy, i);
        // std::string message = &"Усредненное время сортировки: " [ time];
        // message += "нс";
        // fw.writeToFile(message);
        // out << "Усредненное время сортировки: " << time << "нс\n";
        table << "обычный 0-5;пузырек(обычный);" << i << ";" << time
              << "\n"; // записали в таблицу инфу

        copyArray(arr_0_5, copy, i);
        fw.outputArray("Массив до сортировки (Айверсон-1):\n", copy, i);
        time = sort(copy, i, bubbleSortOptimized1); // отсортируем копию
        for (int j = 0; j < i; ++j) {
            std::cout << copy[j] << " ";
        }
        std::cout << "\n";
        fw.outputArray("Массив после сортировки:\n", copy, i);
        table << "обычный 0-5;пузырек(айверсон-1);" << i << ";" << time << "\n"; // занесем данные

        copyArray(arr_0_5, copy, i);
        fw.outputArray("Массив до сортировки (Айверсон-2):\n", copy, i);
        time = sort(copy, i, bubbleSortOptimized2);
        for (int j = 0; j < i; ++j) {
            std::cout << copy[j] << " ";
        }
        std::cout << "\n";
        fw.outputArray("Массив после сортировки:\n", copy, i);
        table << "обычный 0-5;пузырек(айверсон-2);" << i << ";" << time << "\n";
    }

//    out << "Пузырьковая сортировка на массивах со значениями от 0 до 5\n";
//    out.close();
//    sort(unsorted_arr, RANDOM_0_5, 50, 300, 50, bubbleSort);
//    out.open("../output.txt", std::ios::app);
//    out << "Пузырьковая сортировка на массивах со значениями от 0 до 4000\n";
//    out.close();
//    sort(unsorted_arr, RANDOM_0_4000, 50, 300, 50, bubbleSort);
//    out.open("../output.txt", std::ios::app);
//    out << "Пузырьковая сортировка на почти отсортированных массивах со значениями от 0 до 4000\n";
//    out.close();
//    sort(unsorted_arr, ALMOST_SORTED, 500, 300, 50, bubbleSort);

    // цикл для создания массивов размерами от 50 до 300 с шагом 50 и значениями от 0 до 5
//    for (int i = 50; i <= 300; i += 50) {
//        unsorted_arr = generateArray(RANDOM_0_5, i);
//        int *copy_to_sort = new int[i]; // этот массив - копию будем сортировать
//        copyArray(unsorted_arr, copy_to_sort, i);
//        out.open("../output.txt", std::ios::app);
//        out << "Пузырьковая сортировка\n";
//        out.close();
//        printArray(copy_to_sort, i, false); // выведем неотсортированный массив
//        int64_t total_time = 0, time; // суммарное время сортировки за 25 прогонов
//        // цикл для прогона одного и того же массива
//        for (int j = 0; j < 25; ++j) {
//            time = bubbleSort(copy_to_sort, i);
//            total_time += time;
//            // тут аккуратный костыль, чтобы не вернуть сортируемый массив в исходное состояние
//            if (j != 24)
//                copyArray(unsorted_arr, copy_to_sort, i);
//        }
//        int64_t avg_time = total_time / 25;
//        // int64_t time = bubbleSort(copy_to_sort, i);
//        out.open("../output.txt", std::ios::app);
//        printArray(copy_to_sort, i, true); // выведем массив после сортировки
//        out << "Усредненное время сортировки: " << avg_time << "нс\n";
//        out.close();
//        // теперь добавим результаты измерения времени в csv таблицу
//        table << "случайный 0-5;пузырьковая(обычн);" << i << ";" << avg_time << "\n";
//    }
}