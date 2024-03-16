    #ifndef OOP2B_SIGNAL_H
    #define OOP2B_SIGNAL_H
    #include <iostream>
    #include <string>
    #include <vector>
    #include "singler.h"
    #include <stdexcept>

    namespace Prog3 {
        template<typename T>
        class MyVector {
            private:
                int capacity; // вместительность
                int sized;     // размер массива
                T* array;     // указатель на массив

        public:
            explicit MyVector(int capacity = 32) : capacity(capacity), sized(0) {
                array = new T[capacity];
            }
            ~MyVector() {
                delete[] array;
            }
            void push_back(const T element) {
                if (sized == capacity) {
                    // Увеличить вместительность в два раза
                    int newCapacity = capacity * 2;
                    T* newArray = new T[newCapacity];

                    // Копирование элементов в новый массив
                    for (int i = 0; i < sized; i++) {
                        newArray[i] = array[i];
                    }

                    // Удаление старого массива
                    delete[] array;

                    // Изменение вместительности и массива
                    capacity = newCapacity;
                    array = newArray;
                }

                // Добавление нового элемента
                array[sized] = element;
                sized++;
            }

            void clear() {
                sized = 0;
            }

            T& operator[](int index) {
                if (index < 0 || index >= sized) {
                    throw std::out_of_range("Index out of range");
                }
                return array[index];
            }
             [[nodiscard]] int size() const { //компилятор выдавал предупреждение, когда возвращаемое значение функции отбрасывается
                return sized;
            }

            [[nodiscard]] T* begin() const {
                return array; // Возвращает указатель на первый элемент массива
            }

            void erase(T* position) {//удаление
                if (position >= array && position < array + sized) {
                    // Смещение элементов после позиции на одну позицию влево
                    for (T* p = position; p < array + sized - 1; ++p) {
                        *p = *(p + 1);
                    }
                    // Уменьшение размера массива
                    --sized;
                }
            }
            void insert(T* position, const T& element) {
                if (position >= array && position <= array + sized) {
                    // Если массив заполнен, увеличить его вместительность
                    if (sized == capacity) {
                        int newCapacity = capacity * 2;
                        T* newArray = new T[newCapacity];
                        // Копирование элементов перед позицией в новый массив
                        for (T* p = array; p < position; ++p) {
                            *newArray++ = *p;
                        }
                        // Вставка нового элемента
                        *newArray++ = element;
                        // Копирование элементов после позиции в новый массив
                        for (T* p = position; p < array + sized; ++p) {
                            *newArray++ = *p;
                        }
                        // Удаление старого массива
                        delete[] array;
                        // Изменение вместительности, размера и массива
                        capacity = newCapacity;
                        sized++;
                        array = newArray - sized;
                    } else {
                        // Смещение элементов после позиции на одну позицию вправо
                        for (T* p = array + sized; p > position; --p) {
                            *p = *(p - 1);
                        }
                        // Вставка нового элемента
                        *position = element;
                        // Увеличение размера массива
                        sized++;
                    }
                }
            }
        };

        class Signal {
        private:
            MyVector<Prog2::Signaler>signalArray; // Статический массив для хранения

        public:
            Signal();
            Signal(bool level, int duration);
            Signal(const std::string &signalString);
            ~Signal(); // Деструктор для освобождения памяти
            void printSignal();
            void invertSignal();
            void operator+=( Signal &otherSignal);
            void insertSignal(Signal &otherSignal, int position);
            void operator*=(int times);
            Signal& operator=(const Signal& other);
            void deleteSignal(int start, int duration);
            std::string operator[](int i);
            std::string formatSignal();
            void setSignal(const std::string &signalString);
            int getLength() const;
            friend std::ostream& operator<<(std::ostream& os,  Signal& signal);
            friend std::istream& operator>>(std::istream& is, Signal& signal);
        };


    } // namespace Prog3

    #endif // OOP2B_SIGNAL_H
