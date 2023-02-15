#include <iostream>
#include "array-generation-and-outputing/arrayGeneration.h"
#include "bubbleSorts/bubbleSorts.h"
#include "array-generation-and-outputing/arrayOutputing.h"

void copyArray(const int *original, int *copy, int size) {
    for (int i = 0; i < size; ++i) {
        copy[i] = original[i];
    }
}

int main() {
    int *unsorted_arr;
    std::ofstream out("../output.txt");
    std::ofstream table("../tables/time_of_size.csv"); // откроем таблицу
    table << "Вид массива;Метод сортировки;Размер массива;Время(нс)" << "\n";
    // цикл для создания массивов размерами от 50 до 300 с шагом 50 и значениями от 0 до 5
    for (int i = 50; i <= 300; i += 50) {
        unsorted_arr = generateArray(RANDOM_0_5, i);
        int *copy_to_sort = new int[i]; // этот массив - копию будем сортировать
        copyArray(unsorted_arr, copy_to_sort, i);
        out.open("../output.txt", std::ios::app);
        out << "Пузырьковая сортировка\n";
        out.close();
        printArray(copy_to_sort, i, false); // выведем неотсортированный массив
        int64_t total_time = 0, time; // суммарное время сортировки за 25 прогонов
        // цикл для прогона одного и того же массива
        for (int j = 0; j < 25; ++j) {
            time = bubbleSort(copy_to_sort, i);
            total_time += time;
            // тут аккуратный костыль, чтобы не вернуть сортируемый массив в исходное состояние
            if (j != 24)
                copyArray(unsorted_arr, copy_to_sort, i);
        }
        int64_t avg_time = total_time / 25;
        // int64_t time = bubbleSort(copy_to_sort, i);
        out.open("../output.txt", std::ios::app);
        printArray(copy_to_sort, i, true); // выведем массив после сортировки
        out << "Усредненное время сортировки: " << avg_time << "нс\n";
        out.close();
        // теперь добавим результаты измерения времени в csv таблицу
        table << "случайный 0-5;пузырьковая(обычн);" << i << ";" << avg_time << "\n";
    }
    table.close();
}