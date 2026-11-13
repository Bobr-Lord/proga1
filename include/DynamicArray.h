#pragma once
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <cmath>
#include  <typeinfo>
template <typename T>
class DynamicArray {
public:
    class Reference {
    public:
        Reference(DynamicArray& array, size_t index) : array_(array), index_(index) {}

        Reference& operator=(const T& value) {
            array_.set(index_, value);
            return *this;
        }

        Reference& operator=(const Reference& other) {
            return *this = static_cast<T&>(other);
        }

        operator T&() const {
            return array_.data_[index_];
        }

    private:
        DynamicArray& array_;
        size_t index_;
    };

    explicit DynamicArray(size_t size) {
        this->size_ = size;
        this->data_ = newArray(size);
    }

    ~DynamicArray() {
        delete[] data_;
    }

    DynamicArray(const DynamicArray& other) {
        this->size_ = other.size_;
        this->data_ = newArray(other.size_);
        for (size_t index = 0; index < other.size_; index++) {
            this->data_[index] = other.data_[index];
        }
    }

    size_t size() const{
        return size_;
    }
    void print() const {
        std::cout << "[";
        for (size_t index = 0; index < this->size(); index++) {
            if (index > 0) std::cout << ", ";
            std::cout << data_[index];
        }
        std::cout << "]" << std::endl;
    }

    void set(size_t index, const T& value) {
        if (index >= size_) {
            throw std::out_of_range("индекс " + std::to_string(index) + " вне границ массива");
        }
        checkValue(value);

        data_[index] = value;
    }
    T get(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("индекс " + std::to_string(index) + " вне границ массива");
        }
        return data_[index];
    }

    Reference operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("индекс " + std::to_string(index) + " вне границ массива");
        }
        return Reference(*this, index);
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("индекс " + std::to_string(index) + " вне границ массива");
        }
        return data_[index];
    }

    bool operator==(const DynamicArray& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t index = 0; index < size_; index++) {
            if (data_[index] != other.data_[index]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    DynamicArray& operator+=(const DynamicArray& other) {
        add(other);
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        sub(other);
        return *this;
    }

    DynamicArray& operator+=(const T& value) {
        for (size_t index = 0; index < size_; index++) {
            data_[index] += value;
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        for (size_t index = 0; index < size_; index++) {
            data_[index] -= value;
        }
        return *this;
    }

    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    const T* begin() const {
        return data_;
    }

    const T* end() const {
        return data_ + size_;
    }

    void push_back(const T& value) {
        checkValue(value);

        T* new_data = newArray(this->size_+1);
        for (size_t index = 0; index < size_; index++) {
            new_data[index] = this->data_[index];
        }
        new_data[size_] = value;
        delete[] data_;
        data_ = new_data;
        size_++;
    }

    void add(const DynamicArray& other) {
        size_t minSize = std::min(other.size_, this->size_);

        for (size_t index = 0; index < minSize; index++) {
            this->data_[index] += other.data_[index];
        }
    }
    void sub(const DynamicArray& other) {
        size_t minSize = std::min(other.size_, this->size_);

        for (size_t index = 0; index < minSize; index++) {
            this->data_[index] -= other.data_[index];
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "[";
        for (size_t index = 0; index < arr.size_; index++) {
            if (index > 0) os << ", ";
            os << arr.data_[index];
        }
        os << "]";
        return os;
    }

    double distance(const DynamicArray& other) const {
        if constexpr (std::is_arithmetic_v<T>) {
            if (other.size_ != size_) {
                throw std::invalid_argument("размеры массивов различаются");
            }
            double sum = 0;

            for (size_t index = 0; index < other.size_; index++) {
                double dif = other.data_[index] - data_[index];
                sum += dif * dif;
            }

            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }

private:
    T* data_;
    size_t size_;
    void checkValue(const T& value) const {
        if constexpr (std::is_integral_v<T>) {
            if (value < -100 || value > 100) {
                throw std::invalid_argument("значение " + std::to_string(value) + " вне диапазона [-100; 100]");
            }
        }
    }

    static T* newArray(size_t size) {
        T* ptr = new (std::nothrow) T[size]();
        if (!ptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }
};
