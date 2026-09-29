#include "DynamicArray.h"
#include <iostream>
#include <algorithm>

DynamicArray::DynamicArray(size_t size) {
    this->size_ = size;
    this->data_ = new int[size]();
}
DynamicArray::~DynamicArray() {
    delete[] data_;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    this->size_ = other.size_;
    this->data_ = new int[other.size_];
    for (size_t index = 0; index < other.size_; index++) {
        this->data_[index] = other.data_[index];
    }
}

bool DynamicArray::isValueValid(int value) const {
    return value >= -100 && value <= 100;
}

size_t DynamicArray::size() const{
    return size_;
}


void DynamicArray::print() const {
    std::cout << "[";
    for (size_t index = 0; index < this->size(); index++) {
        if (index > 0) std::cout << ", ";
        std::cout << data_[index];
    }
    std::cout << "]" << std::endl;
}

bool DynamicArray::set(size_t index, int value) {
    if (index >= size_) {
        std::cout << "Ошибка: индекс " << index << " вне границ массива\n";
        return false;
    }
    if (!isValueValid(value)) {
        std::cout << "Ошибка: значение " << value << " вне диапазона [-100; 100]\n";
        return false;
    }
    data_[index] = value;
    return true;
}

int DynamicArray::get(size_t index) const {
    if (index >= size_) {
        std::cout << "Ошибка: индекс " << index << " вне границ массива\n";
        return 0;
    }
    return data_[index];
}

void DynamicArray::push_back(int value) {
    if (!isValueValid(value)) {
        std::cout << "Ошибка: значение " << value << " вне диапазона [-100; 100]\n";
        return;
    }
    int* new_data = new int[size_+1];
    for (size_t index = 0; index < size_; index++) {
        new_data[index] = this->data_[index];
    }
    new_data[size_] = value;
    delete[] data_;
    data_ = new_data;
    size_++;
}

void DynamicArray::add(const DynamicArray& other) {
    size_t minSize = std::min(other.size_, this->size_);

    for (size_t index = 0; index < minSize; index++) {
        this->data_[index] += other.data_[index];
    }
}

void DynamicArray::sub(const DynamicArray& other) {
    size_t minSize = std::min(other.size_, this->size_);

    for (size_t index = 0; index < minSize; index++) {
        this->data_[index] -= other.data_[index];
    }
}