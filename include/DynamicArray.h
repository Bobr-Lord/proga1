#pragma once
#include <cstddef>

class DynamicArray {
public:
    explicit DynamicArray(size_t size);
    ~DynamicArray();
    DynamicArray(const DynamicArray& other);

    size_t size() const;
    void print() const;

    bool set(size_t index, int value);
    int get(size_t index) const;

    void push_back(int value);
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
private:
    int* data_;
    size_t size_;
    bool isValueValid(int value) const;
};
