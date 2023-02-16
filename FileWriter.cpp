#include <iostream>
#include <fstream>

/**
 * статический класс для удобства вывода массива и вывода какого-то текста в нужный файл
 */
class FileWriter {
 public:
    static void writeToFile(const std::string& path, const std::string& message) {
        std::ofstream out(path, std::ios::app);
        out << message;
        out.close();
    }

    static void outputArray(const std::string& path, const std::string& message, int *arr, int size) {
        std::ofstream out(path, std::ios::app);
        out << message;
        for (int i = 0; i < size; ++i) {
            out << arr[i] << " ";
        }
        out << "\n";
        out.close();
    }
};
