#ifndef OPP1_PROG1_H
#define OPP1_PROG1_H

#include<iostream>
#include<string>
#include<limits>
#include<cstring>
#include<vector>
#include<list>
#include<functional>

namespace Prog1 {
    // структура для задания строки матрицы
    struct Point  {
        int i; // индекс
        int a; //элемент
        Point(int index, int value) : i(index), a(value) {} // конструктор
    };
       // структура для задания строки матрицы
    struct  Row { // массив точек(индекс столб и знач)
        int n; //чтобы выводить матрицу(нужное число нулей потом вывести)
        std::vector<Point> lines; // вектор  столбцов
    };
    struct Matrix {
        int m = 0; // количество строк
        std::vector<Row> rows; // массив столбцов
    };

    // шаблонная функция ввода одного числа
    template <class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if (std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            else if (std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if (a >= min && a <= max) // если число входит в заданный диапазон
                return a;
        }
    }

    // прототипы функций
    Matrix input(); // ввод матрицы
    void output( const Matrix& matrix); // вывод матрицы
    void erase(Matrix& matrix); // освобождение занятой памяти
    std::vector<int> formVector (const Matrix& matrix, std::function<bool(int)> callback); // вычисление главного результат
};

#endif //OPP1_PROG1_H