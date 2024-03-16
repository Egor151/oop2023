#pragma once
#include <algorithm>
#include <iostream>
#include <initializer_list>

template <class T>
class Vector {
public:
    Vector() : size_(0), capacity_(0), arr_(nullptr) {}

    explicit Vector(size_t size) : Vector() {
        Resize(size);
    }

    Vector(std::initializer_list<T> list) : Vector() {
        Resize(list.size());
        std::copy(list.begin(), list.end(), arr_);
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), arr_(new T[capacity_]) {
        std::copy(other.arr_, other.arr_ + size_, arr_);
    }

    Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.arr_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            arr_ = new T[capacity_];
            std::copy(other.arr_, other.arr_ + size_, arr_);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            Swap(other);
        }
        return *this;
    }

    ~Vector() {
        delete[] arr_;
    }

    void Swap(Vector& other) noexcept {
        std::swap(arr_, other.arr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    T& operator[](size_t idx) {
        return arr_[idx];
    }

    const T& operator[](size_t idx) const {
        return arr_[idx];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_arr = new T[new_capacity];
            std::copy(arr_, arr_ + size_, new_arr);
            delete[] arr_;
            arr_ = new_arr;
            capacity_ = new_capacity;
        }
    }

    void Resize(size_t new_size) {
        Reserve(new_size);
        size_ = new_size;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void PushBack(const T& el) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        arr_[size_] = el;
        ++size_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    bool Contains(const T& value) const {
        return std::find(arr_, arr_ + size_, value) != arr_ + size_;
    }

    bool Find(const T& value) const {
        return std::find(arr_, arr_ + size_, value) != arr_ + size_;
    }

    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(pointer ptr = nullptr) : ptr_(ptr) {}

        reference operator*() const {
            return *ptr_;
        }

        pointer operator->() const {
            return ptr_;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr_;
            return tmp;
        }

        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --ptr_;
            return tmp;
        }

        Iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }

        friend Iterator operator+(Iterator it, difference_type n) {
            it += n;
            return it;
        }

        friend Iterator operator-(Iterator it, difference_type n) {
            it -= n;
            return it;
        }

        friend difference_type operator-(const Iterator& a, const Iterator& b) {
            return a.ptr_ - b.ptr_;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.ptr_ == b.ptr_;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.ptr_ != b.ptr_;
        }

    private:
        pointer ptr_;
    };

    Iterator Begin() const {
        return Iterator(arr_);
    }

    Iterator End() const {
        return Iterator(arr_ + size_);
    }

private:
    T* arr_;
    size_t size_;
    size_t capacity_;
};
