//
// Created by Михаил Демков on 16.02.2023.
//

#ifndef KDZ1__FILEWRITER_H_
#define KDZ1__FILEWRITER_H_

#include <iostream>
#include <fstream>

class FileWriter {
 private:
    std::string path_;
    std::ofstream out_;
 public:
    ~FileWriter();

    explicit FileWriter(const std::string &path);

    void writeToFile(const std::string& message);

    void outputArray(const std::string& message, int *arr, int size);

    void open(const std::string &path);

    void close();

    void update(const std::string &path);

};

#endif //KDZ1__FILEWRITER_H_
