#ifndef BINARY_FILE_HANDLER_H
#define BINARY_FILE_HANDLER_H

#include <string>

class BinaryFileHandler {
public:
    // ����������� ����� ��� ������������� ���������, ������� k, � ������ ����
    static void copyMultiplesOfK(const std::string& inputFile, const std::string& outputFile, int k);
};

#endif
#pragma once
