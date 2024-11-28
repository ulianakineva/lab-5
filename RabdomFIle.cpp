#include "RabdomFile.h"
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

// Задание 1
void RabdomFile::fillFileWithRandomNumbers(const std::string& filename, size_t count, int min, int max) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        return;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    
    for (size_t i = 0; i < count; ++i) {
        int num = dis(gen);
        outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
    }
    cout << endl;
    outFile.close();
    cout << "Файл " << filename << " успешно записан." << endl;
}

int RabdomFile::inputK() {
    int k;
    while (true) {
        cout << "Введите число k (целое число): ";
        cin >> k;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите целое число." << endl;
        }
        else {
            break;
        }
    }
    return k;
}

void RabdomFile::filterMultiplesOfK(const string& inputFile, const string& outputFile, int k) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия входного файла: " << inputFile << endl;
        return;
    }

    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия выходного файла: " << outputFile << endl;
        return;
    }

    int num;
    bool found = false;
    cout << "Чтение из файла сгенерированных значений: ";
    while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        cout << " " << num;
        if (num % k == 0) {
            outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
            found = true;
        }
    }
    cout << endl; 
    if (found) {
        cout << "Записываю в файл " << outputFile << " следующие числа, кратные " << k << ": ";
        inFile.clear();  // Нужно очистить флаг ошибки после чтения
        inFile.seekg(0); // Перемещаем указатель в начало файла
        while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            if (num % k == 0) {
                cout << num << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Нет чисел, кратных " << k << ", в исходном файле." << endl;
    }

    inFile.close();
    outFile.close();
    cout << "Файл " << outputFile << " успешно записан." << endl;
}

// Задание 2

// Статический метод для ввода размерности матрицы
int RabdomFile::inputMatrixSize() {
    int n;
    while (true) {
        std::cout << "Введите размерность матрицы n (положительное целое число): ";
        std::cin >> n;

        // Проверка, что введено корректное число
        if (std::cin.fail() || n <= 0) {
            std::cin.clear(); // Очистка флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка оставшегося ввода
            std::cout << "Ошибка ввода! Пожалуйста, введите положительное целое число." << std::endl;
        }
        else {
            break;
        }
    }
    return n;
}

// Статический метод для копирования данных в матрицу
void RabdomFile::copyDataToMatrix(const std::string& inputFile, const std::string& outputFile, int n) {
    
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile) {
            std::cerr << "Ошибка открытия входного файла для чтения." << std::endl;
            return;
        }

        // Создаем квадратную матрицу n x n
        int** matrix = new int* [n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new int[n]();
        }

        // Читаем данные из файла и заполняем матрицу
        int num;
        int index = 0;
        while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num)) && index < n * n) {
            matrix[index / n][index % n] = num;
            ++index;
        }

        // Закрываем файл после чтения
        inFile.close();

        // Найти столбец с минимальной суммой элементов
        int minColumnIndex = 0;
        int minSum = INT_MAX;

        for (int col = 0; col < n; ++col) {
            int columnSum = 0;
            for (int row = 0; row < n; ++row) {
                columnSum += matrix[row][col];
            }
            if (columnSum < minSum) {
                minSum = columnSum;
                minColumnIndex = col;
            }
        }

        // Заменяем все столбцы на столбец с минимальной суммой
        for (int col = 0; col < n; ++col) {
            for (int row = 0; row < n; ++row) {
                matrix[row][col] = matrix[row][minColumnIndex];
            }
        }

        // Выводим итоговую матрицу
        cout << "Матрица после замены всех столбцов на столбец с минимальной суммой:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        // Записываем модифицированную матрицу в бинарный файл
        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile) {
            std::cerr << "Ошибка открытия выходного файла для записи." << std::endl;

            // Освобождаем память перед завершением
            for (int i = 0; i < n; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;

            return;
        }

        for (int i = 0; i < n; ++i) {
            outFile.write(reinterpret_cast<char*>(matrix[i]), n * sizeof(int));
        }

        outFile.close();

        // Освобождаем память
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;

        std::cout << "Матрица записана в файл: " << outputFile << std::endl;
    }


// Задание 3
void RabdomFile::ToyData(const std::string& filename) {
    ToyInfo toys[] = {
        {"Конструктор LEGO", rand() % 900000 + 100000, 5, 10},
        {"Конструктор из дерева", rand() % 900000 + 100000, 3, 6},
        {"Игрушка для младенцев",rand() % 900000 + 100000, 0, 2},
        {"Конструктор машинки", rand() % 900000 + 100000, 4, 8},
        {"Конструктор для девочек", rand() % 900000 + 100000, 6, 12},
    };

    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    cout << "Записываю в файл " << filename << " данные об игрушках:" << endl;
    for (const ToyInfo& toy : toys) {
        // Выводим информацию перед записью в файл
        cout << "Название: " << toy.name << ", Цена: " << toy.price << ", Возраст: " << toy.min_age << "-" << toy.max_age << endl;
        outFile.write(reinterpret_cast<const char*>(&toy), sizeof(toy));
    }

    outFile.close();
    cout << "Данные о конструкторах успешно записаны в файл." << endl;
}


void RabdomFile::findMostExpensiveConstructor(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения: " << filename << endl;
        return;
    }

    ToyInfo toy, mostExpensiveToy;
    mostExpensiveToy.price = 0;

    cout << "Чтение файла: " << filename << "..." << endl;

    while (inFile.read(reinterpret_cast<char*>(&toy), sizeof(toy))) {
        // Преобразуем название игрушки в строку
        string toyName(toy.name);

        // Приводим строку к нижнему регистру, чтобы искать независимо от регистра
        transform(toyName.begin(), toyName.end(), toyName.begin(), ::tolower);

        cout << "Читаем игрушку: " << toyName << ", Цена: " << toy.price << endl;  // Выводим прочитанные данные

        // Проверяем, содержится ли "конструктор" в названии и если да, то обновляем самый дорогой
        if (toyName.find("конструктор") != string::npos && toy.price > mostExpensiveToy.price) {
            mostExpensiveToy = toy;
        }
    }

    if (mostExpensiveToy.price > 0) {
        cout << "Самый дорогой конструктор: " << mostExpensiveToy.name << ", Цена: " << mostExpensiveToy.price << endl;
    }
    else {
        cout << "Конструктор не найден в файле." << endl;
    }

    inFile.close();
}

// Задание 4

void RabdomFile::generateFile(const string& filename, size_t size, int minValue, int maxValue) {
    ofstream outFile(filename); // Текстовый режим по умолчанию
    if (!outFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел

    for (size_t i = 0; i < size; ++i) {
        int value = minValue + rand() % (maxValue - minValue + 1);
        outFile << value << '\n'; // Записываем число в текстовом формате, добавляя символ новой строки
    }

    outFile.close();
    cout << "Файл " << filename << " заполнен " << size << " случайными числами.\n";
}

    



void RabdomFile::readFile(const string& filename) {
    ifstream inFile(filename); // Текстовый режим по умолчанию
    if (!inFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        return;
    }

    vector<int> values;
    int value;
    size_t index = 0;
    int sum = 0;

    while (inFile >> value) { // Чтение числа из текстового файла
        values.push_back(value);
        if (static_cast<int>(index) == value) {
            sum += value;
        }
        ++index;
    }

    inFile.close();

    // Вывод данных для проверки
    cout << "Чтение из файла:" << endl;
    for (size_t i = 0; i < values.size(); ++i) {
        cout << "Индекс " << i << ": " << values[i] << endl;
    }

    cout << "Сумма элементов, равных их индексам: " << sum << endl;
}
// Задание 5
void RabdomFile::generateRows(const string& filename, size_t minCols, size_t maxCols, size_t rows, int minValue, int maxValue) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел

    for (size_t i = 0; i < rows; ++i) {
        size_t cols = minCols + rand() % (maxCols - minCols + 1); // Случайное количество чисел в строке
        for (size_t j = 0; j < cols; ++j) {
            int value = minValue + rand() % (maxValue - minValue + 1); // Случайное число
            outFile << value;
            if (j < cols - 1) {
                outFile << " "; // Разделитель между числами
            }
        }
        outFile << endl; // Переход на новую строку
    }

    outFile.close();
    cout << "Файл " << filename << " успешно заполнен случайными числами с переменным количеством столбцов.\n";
}

void RabdomFile::cal(const string& filename, int k) {

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    long long product = 1; // Начальное значение для произведения
    bool hasMultiples = false; // Флаг наличия элементов, кратных k

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line); // Для обработки строки
        int value;
        while (ss >> value) {
            if (value % k == 0) {
                product *= value;
                hasMultiples = true;
            }
        }
    }

    inFile.close();

    if (hasMultiples) {
        cout << "Произведение элементов, кратных " << k << ": " << product << endl;
    }
    else {
        cout << "Нет элементов, кратных " << k << " в файле." << endl;
    }
}
// Задание 6
// Функция для проверки наличия русских букв
bool RabdomFile::containsRussianLetters(const string& str) {
    for (char ch : str) {
        // Проверяем, является ли символ русской буквой
        if ((ch >= 'а' && ch <= 'я') || (ch >= 'А' && ch <= 'Я')) {
            return true;  // Если хотя бы одна русская буква
        }
    }
    return false;  // Если нет русских букв
}

// Функция для обработки файла
void RabdomFile::processFileWithoutRussianLetters(const string& inputFilename, const string& outputFilename) {
    // Открываем исходный файл
    ifstream inFile(inputFilename);
    if (!inFile) {
        cerr << "Ошибка: невозможно открыть файл " << inputFilename << endl;
        return;
    }

    // Открываем выходной файл для записи
    ofstream outFile(outputFilename);
    if (!outFile) {
        cerr << "Ошибка: невозможно открыть файл " << outputFilename << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        // Если строка не содержит русских букв, записываем её в новый файл
        if (!containsRussianLetters(line)) {
            outFile << line << endl;  // Записываем строку в новый файл
        }
    }

    inFile.close();  // Закрываем входной файл
    outFile.close();  // Закрываем выходной файл
    cout << "Строки без русских букв переписаны в файл " << outputFilename << endl;
}

