#include "DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>

int main() {
    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    a.push_back(40);
    a.print();

    std::cout << "\nstd::out_of_range" << std::endl;
    try {
        a.set(10, 1);
    } catch (const std::out_of_range& e) {
        std::cout << "set: " << e.what() << std::endl;
    }
    try {
        a.get(10);
    } catch (const std::out_of_range& e) {
        std::cout << "get: " << e.what() << std::endl;
    }

    std::cout << "\nstd::invalid_argument" << std::endl;
    try {
        a.set(0, 150);
    } catch (const std::invalid_argument& e) {
        std::cout << "set: " << e.what() << std::endl;
    }
    try {
        a.push_back(-500);
    } catch (const std::invalid_argument& e) {
        std::cout << "push_back: " << e.what() << std::endl;
    }
    a.print();

    std::cout << "\nstd::bad_alloc" << std::endl;
    try {
        DynamicArray huge(1000000000000ULL);
    } catch (const std::bad_alloc& e) {
        std::cout << "конструктор: " << e.what() << std::endl;
    }

    return 0;
}