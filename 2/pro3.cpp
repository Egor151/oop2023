#include "dynamic/signal.h"
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

using namespace Prog3;

int main() {
    int choice;
    Signal sig;
    int i, a;
    int lev, dur;
    std::string input, input2;

    do {
        std::cout << "\n1. Input signal\n";
        std::cout << "2. Format signal\n";
        std::cout << "3. Duplicate signal\n";
        std::cout << "4. Delete signal\n";
        std::cout << "5. Append signal\n";
        std::cout << "6. Invert signal\n";
        std::cout << "7. Insert signal in time\n";
        std::cout << "8. Receiving signal in time\n";
        std::cout << "9. Print\n";
        std::cout << "0. Exit program" << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) { // проверка на неверный ввод
            if (std::cin.eof()) {
                std::cin.clear(); // очищаем флаг ошибки
                std::cin.ignore(
                        1 << (sizeof(int) * 8 - 2),
                        '\n'); // проигнорируем оставшиеся символы во входном потоке
                std::cout << "Invalid choice. Please try again." << std::endl;
                continue;
            }
        }

        try {
            switch (choice) {
                case 1:
                    std::cout << "\n1. Input only string\n";
                    std::cout << "2. Input level and duration\n";
                    std::cout << "0. Back" << std::endl;
                    while (true) {
                        std::string str;
                        std::cin >> str;
                        if (str.length() == 1 && (str[0] == '0' || str[0] == '1' || str[0] == '2')) {
                            a = str[0] - '0';
                            break;
                        }
                        std::cout << "Invalid number. Please, come again\n";
                    }
                    switch (a) {
                        case 1:
                            std::cin >> sig;
                            break;
                        case 2:
                            std:: cout << "Enter level: ";
                            if(!(std::cin >> lev)) {
                                std:: cout << "invalid duration" << std::endl;
                                continue;
                            }
                            std:: cout << "Enter duration: ";
                            if(!(std::cin >> dur)) {
                                std:: cout << "invalid duration" << std::endl;
                                continue;
                            }
                            sig = Signal(lev, dur);
                            break;
                    }
                    break;
                case 2:
                    std::cout << sig;

                    break;
                case 3:
                    std::cout << "How many times to increase: ";
                    if (!(std::cin >> i) || i < 0) {
                        std::cin.clear();
                        std::cin.ignore(1 << (sizeof(int) * 8 - 2), '\n');
                        throw std::invalid_argument("Invalid input!");
                    }
                    sig *= i;
                    break;
                case 4:
                    int start, duration;
                    std::cout << "Input start position: ";
                    if (!(std::cin >> start) || start < 0 || start >= sig.getLength()) {
                        std::cin.clear();
                        std::cin.ignore(1 << (sizeof(int) * 8 - 2), '\n');
                        throw std::invalid_argument("Invalid start position!");
                    }
                    std::cout << "Input duration: ";
                    if (!(std::cin >> duration) || duration <= 0 ||
                        duration > sig.getLength() - start) {
                        std::cin.clear();
                        std::cin.ignore(1 << (sizeof(int) * 8 - 2), '\n');
                        throw std::invalid_argument("Invalid duration!");
                    }
                    sig.deleteSignal(start, duration);
                    break;
                case 5:
                    std::cout << "Input signal to append: ";
                    if (!(std::cin >> input)) {
                        std::cout << "invalid string" << std::endl;
                        continue;
                    }
                    try {
                        Signal otherSignal(input);
                        sig += otherSignal;
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case 6:
                    sig.invertSignal();
                    break;
                case 7:
                    std::cout << "Enter the signal to insert: ";
                    if (!(std::cin >> input)) {
                        std::cout << "invalid string" << std::endl;
                        continue;
                    }
                    std::cout << "Enter the position to insert: ";
                    std::cin >> i;
                    try {
                        Signal otherSignal(input);
                        sig.insertSignal(otherSignal, i);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case 8:
                    std::cout << "Enter the time to get signal level: ";
                    std::cin >> i;
                    try {
                        std::string level = sig[i];
                        std::cout << "Signal level at time " << i << " is " << level
                                  << std::endl;
                    } catch (const std::exception &e) {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                case 9:
                    std::cout << "Signal: ";
                    sig.printSignal();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Invalid number choice. Please try again." << std::endl;
                    break;
            }
        } catch (const std::exception &e) { // в случае прочих исключений
            std::cerr << e.what() << std::endl;
        }
    } while (choice != 0);

    return 0;
}
