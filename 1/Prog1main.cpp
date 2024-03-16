#include <iostream>
#include<functional>
#include<string>
#include "Prog1.h"


using namespace Prog1;

int main() {
    Matrix matrix; // исходная матрица
    std::vector<int> res; // полученный результат
    int choice;

    do {
        std::cout << "\n1. Input matrix\n";
        std::cout << "2. Output matrix\n";
        std::cout << "3. Free memory\n";
        std::cout << "4. Selection criteria\n";
        std::cout << "0. Exit program" << std::endl;
        std::cout << "Enter your choice: ";
        //std::cin >> choice;

        if (!(std::cin >> choice)) { // проверка на неверный ввод
            if (std::cin.eof()) {
                std::cin.clear(); // очищаем флаг ошибки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n'); // проигнорируем оставшиеся символы во входном потоке
                std::cout << "Invalid choice. Please try again." << std::endl;
                choice = 1;//чтобы выводить ошибку при вводе букв
                continue; // переходим к следующей итерации цикла
            }
        }

        try {
            switch (choice) {
                case 1:
                    matrix = input(); // ввод матрицы
                    break;
                case 2:
                    std::cout << "Sourced matrix" << std::endl;
                    output(matrix); // вывод матрицы
                    break;
                case 3:
                    erase(matrix); // освобождение памяти
                    break;
                case 4:
                    res = formVector(matrix, [](int elem) {
                        return elem > 2;  // Example callback: sum only elements greater than 2 // любая логика
                    });

                    for (int ress: res) {
                        std::cout << ress << " ";
                    }
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Invalid number  choice. Please try again." << std::endl;
                    break;
            }
        }
        catch (const std::bad_alloc &ba) { // в случае ошибок выделения памяти
            std::cerr << "Not enough memory" << std::endl;
            erase(matrix);
        }
        catch (const std::exception &e) { // в случае прочих исключений
            std::cerr << e.what() << std::endl;
            erase(matrix);
        }
    } while(choice != 0);

    erase(matrix); // освобождение памяти перед завершением программы

    return 0;
}