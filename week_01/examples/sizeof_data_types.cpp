#include <iostream>


int main() {
    std::cout << "sizeof_data_types:" << std::endl;
    std::cout << "char: " << sizeof(char) << "\n";                 //  1
    std::cout << "bool: " << sizeof(bool) << "\n";                 //  1
    std::cout << "short: " << sizeof(short) << "\n";               //  2 (isocpp >= 2)
    std::cout << "int: " << sizeof(int) << "\n";                   //  4 (isocpp >= 2)
    std::cout << "long: " << sizeof(long) << "\n";                 //  8 (isocpp >= 4)
    std::cout << "long long: " << sizeof(long long) << "\n";       //  8 (isocpp >= 8)

    std::cout << "float: " << sizeof(float) << "\n";               //  4
    std::cout << "double: " << sizeof(double) << "\n";             //  8
    std::cout << "long double: " << sizeof(long double) << "\n";   // 16

    // std::cout << "void: " << sizeof(void) << "\n";                 //  compile-error or 1
    std::cout << "std::nullptr_t: " << sizeof(nullptr) << "\n";    //  8
    std::cout << "size_t: " << sizeof(size_t) << "\n";             //  8
    std::cout << std::endl;
    return 0;
}