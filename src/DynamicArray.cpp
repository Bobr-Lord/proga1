#include "DynamicArray.h"
#include <iostream>
#include <algorithm>
#include <new>
#include <stdexcept>
#include <string>

int* DynamicArray::newArray(size_t size) {
    int* ptr = new (std::nothrow) int[size]();
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

DynamicArray::DynamicArray(size_t size) {
    this->size_ = size;
    this->data_ = newArray(size);
}
DynamicArray::~DynamicArray() {
    delete[] data_;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    this->size_ = other.size_;
    this->data_ = newArray(other.size_);
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

void DynamicArray::set(size_t index, int value) {
    if (index >= size_) {
        throw std::out_of_range("индекс " + std::to_string(index) + " вне границ массива");
    }
    if (!isValueValid(value)) {
        throw std::invalid_argument("значение " + std::to_string(value) + " вне диапазона [-100; 100]");
    }
    data_[index] = value;
}

int DynamicArray::get(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("индекс " + std::to_string(index) + " вне границ массива");
    }
    return data_[index];
}

void DynamicArray::push_back(int value) {
    if (!isValueValid(value)) {
        throw std::invalid_argument("значение " + std::to_string(value) + " вне диапазона [-100; 100]");
    }
    int* new_data = newArray(this->size_+1);
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