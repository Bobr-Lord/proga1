#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>

int main() {
    std::cout << "Задание 1" << std::endl;
    DynamicArray<int> a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    try {
        a.set(0, 500);
    } catch (const std::invalid_argument& e) {
        std::cout << "int: " << e.what() << std::endl;
    }

    DynamicArray<double> d(2);
    d.set(0, 500.5);
    d.set(1, -1000.25);

    DynamicArray<std::string> s(0);
    s.push_back("hello");
    s.push_back("world");

    std::cout << "\nЗадание 2" << std::endl;
    std::cout << "int:    " << a << std::endl;
    std::cout << "double: " << d << std::endl;
    std::cout << "string: " << s << std::endl;

    std::cout << "\nЗадание 3" << std::endl;
    DynamicArray<int> p(2);
    DynamicArray<int> q(2);
    q.set(0, 3);
    q.set(1, 4);
    std::cout << "distance(" << p << ", " << q << ") = " << p.distance(q) << std::endl;

    try {
        a.distance(p);
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }

    try {
        s.distance(s);
    } catch (const std::bad_typeid& e) {
        std::cout << "bad_typeid: " << e.what() << std::endl;
    }

    std::cout << "\nЧасть 4. Задание 1" << std::endl;
    DynamicArray<int> indexed(2);
    indexed[0] = 10;
    indexed[1] = 20;
    std::cout << "indexed[0] = " << indexed[0] << std::endl;
    try {
        indexed[0] = 500;
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }
    try {
        indexed[2] = 30;
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    std::cout << "\nЧасть 4. Задание 2" << std::endl;
    DynamicArray<int> same(2);
    same[0] = 10;
    same[1] = 20;
    DynamicArray<int> different(2);
    different[0] = 10;
    different[1] = 30;
    std::cout << std::boolalpha;
    std::cout << "indexed == same: " << (indexed == same) << std::endl;
    std::cout << "indexed != different: " << (indexed != different) << std::endl;

    std::cout << "\nЧасть 4. Задание 3" << std::endl;
    DynamicArray<int> arithmetic(3);
    arithmetic[0] = 1;
    arithmetic[1] = 2;
    arithmetic[2] = 3;
    arithmetic += indexed;
    std::cout << "arithmetic += indexed: " << arithmetic << std::endl;
    arithmetic -= indexed;
    std::cout << "arithmetic -= indexed: " << arithmetic << std::endl;
    arithmetic += 5;
    std::cout << "arithmetic += 5: " << arithmetic << std::endl;
    arithmetic -= 2;
    std::cout << "arithmetic -= 2: " << arithmetic << std::endl;

    std::cout << "\nЧасть 4. Задание 4" << std::endl;
    for (auto& x : arithmetic) {
        x += 1;
    }
    std::cout << "После for (auto& x : arr): " << arithmetic << std::endl;
    const DynamicArray<int>& constArithmetic = arithmetic;
    std::cout << "Константный обход: ";
    for (const auto& x : constArithmetic) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}