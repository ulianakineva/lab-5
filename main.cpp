#include <iostream>
#include "RabdomFile.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    // Создание объектов классов
    RabdomFile rabdomFile;

    // Файлы для работы
    string numbersFile = "numbers.dat";
    string multiplesFile = "multiples.dat";
    string toysFile = "toys.dat";
    string randomFile = "random.dat";
    string filteredFile = "filtered.dat";
    string indexfile = "numbers.txt";
    string divfile = "prod.txt";
    string randomIntsFile = "data.dat  ";
    string matrixFile = "matrix.dat";
    string inputFile = "text.txt";
    string outputFile = "output.txt";

    // Задача 1: Заполнение файла случайными числами
    cout << "Задание 1" << endl;
    rabdomFile.fillFileWithRandomNumbers(numbersFile, 10, 1, 100);

    int k = rabdomFile.inputK();
    rabdomFile.filterMultiplesOfK(numbersFile, multiplesFile, k);

    // Задача 2
    cout << "Задание 2" << endl;
    // Генерация случайных данных и запись в бинарный файл

    // Ввод размерности матрицы с клавиатуры
    int n = rabdomFile.inputMatrixSize();

    // Копирование данных в матрицу и запись в текстовый файл
    rabdomFile.copyDataToMatrix(numbersFile, matrixFile, n);


    // Задача 3: Заполнение файла с данными об игрушках
    cout << "Задание 3" << endl;
    rabdomFile.ToyData(toysFile);

    // Поиск самого дорогого конструктора
    rabdomFile.findMostExpensiveConstructor(toysFile);

    // Задание 4
    cout << "Задание 4" << endl;

    size_t size = 20; // Количество элементов
    int minValue = 0; // Минимальное значение
    int maxValue = 20; // Максимальное значение

    

    // Генерация файла
    rabdomFile.generateFile(indexfile, size, minValue, maxValue);

    // Чтение и обработка файла
    rabdomFile.readFile(indexfile);

    // Задание 5
    cout << "Задание 5" << endl;

    // Генерация файла
    rabdomFile.generateRows(divfile, 3, 7, 5, 1, 100);
    int kk = rabdomFile.inputK();
    // Чтение и обработка бинарного файла: произведение элементов, кратных k
    rabdomFile.cal(divfile, kk);

    // Задание 6
    cout << "Задание 6" << endl;

    rabdomFile.processFileWithoutRussianLetters(inputFile, outputFile);
   

    return 0;
}
