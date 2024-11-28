#ifndef RABDOMFILE_H
#define RABDOMFILE_H
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <regex>
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

struct ToyInfo {
    char name[100];  // Название игрушки (массив символов)
    int price;      // Цена
    int min_age;    // Минимальный возраст
    int max_age;    // Максимальный возраст
};


class RabdomFile {
public:
    // Заполнение бинарного файла случайными числами
    static void fillFileWithRandomNumbers(const std::string& filename, size_t count, int min, int max);

    // Ввод числа k
    static int inputK();

    // Фильтрация чисел, кратных k
    static void filterMultiplesOfK(const std::string& inputFile, const std::string& outputFile, int k);

    static int inputMatrixSize();

    static void copyDataToMatrix(const string& inputFile, const string& outputFile, int n);

    // Заполнение файла данными о конструкторах
    static void ToyData(const string& filename);

    // Поиск самого дорогого конструктора
    static void findMostExpensiveConstructor(const std::string& filename);

    // Метод для генерации бинарного файла с случайными числами
    static void generateFile(const string& filename, size_t size, int minValue, int maxValue);

    // Метод для чтения бинарного файла и вычисления суммы элементов, равных своему индексу
    static void readFile(const string& filename);

    static void generateRows(const string& filename, size_t minCols, size_t maxCols, size_t rows, int minValue, int maxValue);

    // Метод для чтения бинарного файла и вычисления произведения элементов, кратных k
    static void cal(const string& filename, int k);

    static bool containsRussianLetters(const string& str);

    static void processFileWithoutRussianLetters(const string& inputFilename, const string& outputFilename);


};

#endif // RABDOMFILE_H
