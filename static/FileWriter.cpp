#include <iostream>
#include <fstream>

/**
 * статический класс для удобства вывода массива и вывода какого-то текста в нужный файл
 */
class FileWriter {
 public:
    /**
     * функция для записи сообщения в файл
     * @param path путь до файла
     * @param message сообщение для записи
     */
    static void writeToFile(const std::string& path, const std::string& message) {
        std::ofstream out(path, std::ios::app);
        out << message;
        out.close();
    }

    /**
     * функция для вывода массива в указанный файл
     * @param path путь до файла
     * @param message некоторое доп.сообщение для вывода
     * @param arr сам массив для вывода
     * @param size размер массива
     */
    static void outputArray(const std::string& path, const std::string& message, int *arr, int size) {
        std::ofstream out(path, std::ios::app);
        out << message;
        for (int i = 0; i < size; ++i) {
            out << arr[i] << " ";
        }
        out << "\n";
        out.close();
    }

    /**
     * костыльная функция чтобы очистить файлы при каждом запуске программы
     */
    static void clearAllFiles() {
        std::ofstream out("../text-files-output/bubbleSort.txt");
        out.close();
        out.open("../text-files-output/selectionSort.txt");
        out.close();
        out.open("../text-files-output/countingSort.txt");
        out.close();
        out.open("../text-files-output/heapSort.txt");
        out.close();
        out.open("../text-files-output/insertionSort.txt");
        out.close();
        out.open("../text-files-output/mergeSort.txt");
        out.close();
        out.open("../text-files-output/quickSort.txt");
        out.close();
        out.open("../text-files-output/radixSort.txt");
        out.close();
        out.open("../text-files-output/shellSort.txt");
        out.close();
        out.open("../tables/time_of_size.csv");
        out.close();
        out.open("../tables/time_of_operations.csv");
        out.close();
    }
};
