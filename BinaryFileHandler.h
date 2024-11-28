#ifndef BINARY_FILE_HANDLER_H
#define BINARY_FILE_HANDLER_H

#include <string>

class BinaryFileHandler {
public:
    // Статический метод для переписывания элементов, кратных k, в другой файл
    static void copyMultiplesOfK(const std::string& inputFile, const std::string& outputFile, int k);
};

#endif
#pragma once
