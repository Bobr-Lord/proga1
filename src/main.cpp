#include "DynamicArray.h"
#include <iostream>

int main() {
    std::cout << "Задание 1" << std::endl;
    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    a.print();
    std::cout << "a.get(1) = " << a.get(1) << std::endl;
    a.set(5, 1);
    a.set(0, 150);
    a.get(5);

    std::cout << "\nЗадание 2" << std::endl;
    DynamicArray copy(a);
    copy.set(0, 99);
    a.print();
    copy.print();

    std::cout << "\nЗадание 3" << std::endl;
    a.push_back(40);
    a.push_back(500);
    a.print();

    std::cout << "\n=== Задание 4 ===" << std::endl;
    DynamicArray b(2);
    b.set(0, 1);
    b.set(1, 2);
    a.add(b);
    a.print();
    a.sub(b);
    a.print();

    return 0;
}
