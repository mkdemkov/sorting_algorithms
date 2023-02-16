//
// Created by Михаил Демков on 16.02.2023.
//

#include "FileWriter.h"

FileWriter::FileWriter(const std::string &path) {
    this->path_ = path;
    out_.open(path, std::ios::app);
}
void FileWriter::writeToFile(const std::string& message) {
    out_ << message;
}

void FileWriter::outputArray(const std::string& message, int *arr, int size) {
    out_ << message;
    for (int i = 0; i < size; ++i) {
        out_ << arr[i] << " ";
    }
    out_ << "\n";
}

void FileWriter::close() {
    out_.close();
}

void FileWriter::open(const std::string &path) {
    out_.open(path);
}

void FileWriter::update(const std::string &path) {
    out_.close();
    this->path_ = path;
    out_.open(path);
}

FileWriter::~FileWriter() {
    out_.close();
}
