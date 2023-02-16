//
// Created by Михаил Демков on 16.02.2023.
//

// #include "FileWriter.h"
#include <iostream>
#include <fstream>

class FileWriter {
 private:
    std::ofstream out_;
    std::string path_;
 public:

    FileWriter(const std::string &path) {
        this->path_ = path;
        out_.open(path, std::ios::app);
    }
    void writeToFile(const std::string& message) {
        out_ << message;
    }

    void outputArray(const std::string& message, int *arr, int size) {
        out_ << message;
        for (int i = 0; i < size; ++i) {
            out_ << arr[i] << " ";
        }
        out_ << "\n";
    }

    void close() {
        out_.close();
    }

    void open(const std::string &path) {
        out_.open(path);
    }

    void update(const std::string &path) {
        out_.close();
        this->path_ = path;
        out_.open(path);
    }

    ~FileWriter() {
        out_.close();
    }
};
