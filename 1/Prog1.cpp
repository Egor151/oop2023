#include<iostream>
#include<vector>
#include <functional>
#include "Prog1.h"


namespace Prog1 {
    // функция ввода
    Matrix input() {
        // выделение памяти для матрицы
        Matrix matrix;
        try {
            // вводим количество строк
            std::cout << "Enter number of lines: --> " << std::endl;
            matrix.m = getNum<int>(0);
            // выделяем память под массив структур - строк матрицы
            matrix.rows.resize(matrix.m);
            // для каждой строки матрицы вводим количество столбцов
            std::cout << "Enter number of columns  in line " << " --> " << std::endl;
            int n = getNum<int>(0);

            for (int i = 0; i < matrix.m; i++) {
                // запоминаем ссылку на обрабатываемую строку
                Row& row = matrix.rows[i];
                row.n = n;
                for (int j = 0; j < n; j++) {
                    // вводим элемент
                    std::cout << "Enter item #" << (j + 1) << ": " << std::endl;
                    int elements  = getNum<int>();
                    if( elements != 0){
                        row.lines.push_back(Point(j, elements));
                    }
                }
            }
        }
        catch (...) { // в случае любого исключения
            erase(matrix); // очищаем уже выделенную память
            throw; // перекидываем исключение дальше
        }
        return matrix;
    }

    // функция вывода
    void output(const Matrix& matrix) {
        std::cout << "\n";
        for (const Row& row : matrix.rows) {
            int colIndex = 0;
            for (const Point& point : row.lines) {
                while (colIndex < point.i) {
                    std::cout << "0\t";
                    colIndex++;
                }
                std::cout << point.a << "\t";
                colIndex++;
            }
            while (colIndex < row.n) {
                std::cout << "0\t";
                colIndex++;
            }
            std::cout << std::endl;
        }
    }

    // функция освобождения занятой памяти
    void erase(Matrix& matrix) {
        matrix.rows.clear();
        matrix.m = 0;
    }

    // функция формирования вектора
    std::vector<int> formVector (const Matrix& matrix, std::function<bool(int)> callback) {
        std::vector<int> sums;

        for (const Row& row : matrix.rows) {
            int currentSum = 0;
            for (const Point& point : row.lines) {
                if (callback(point.a)) {
                    currentSum += point.a;
                }
            }
            sums.push_back(currentSum);
        }

        return sums;
    }

}