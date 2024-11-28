#ifndef TOY_INFO_H
#define TOY_INFO_H

#include <string>

// Структура для хранения информации об игрушке
struct ToyInfo {
    char name[100];  // Название игрушки
    int price;       // Стоимость игрушки в рублях
    int min_age;     // Минимальный возраст
    int max_age;     // Максимальный возраст
};

#endif
