#include <iostream>
#include <limits>
#include <iomanip> // for I/O manipulators std::boolalpha std::noboolalpha


void numeric_limits_integer() {
    std::cout << "numeric_limits_integer:" << std::endl;
    std::cout << "type\t\t│ min()\t\t\t│ max()" << '\n';
    std::cout << "bool\t\t│ "
              << std::numeric_limits<bool>::min() << "\t\t\t│ "
              << std::numeric_limits<bool>::max() << '\n';
    std::cout << "char\t\t│ "
              << +std::numeric_limits<char>::min() << "\t\t\t│ " // unary `+` to convert to int instead of char
              << +std::numeric_limits<char>::max() << '\n';
    std::cout << "uchar\t\t│ "
              << +std::numeric_limits<unsigned char>::min() << "\t\t\t│ "
              << +std::numeric_limits<unsigned char>::max() << '\n';
    std::cout << "short\t\t│ "
              << std::numeric_limits<short>::min() << "\t\t│ "
              << std::numeric_limits<short>::max() << '\n';
    std::cout << "int\t\t│ "
              << std::numeric_limits<int>::min() << "\t\t│ "
              << std::numeric_limits<int>::max() << '\n';
    std::cout << "unsigned int\t│ "
              << +std::numeric_limits<unsigned>::min() << "\t\t\t│ "
              << +std::numeric_limits<unsigned>::max() << '\n';
    std::cout << "long long\t│ "
              << std::numeric_limits<long long>::min() << "\t│ "
              << std::numeric_limits<long long>::max() << '\n';
    std::cout << "size_t\t\t│ "
              << std::numeric_limits<size_t>::min() << "\t\t\t│ "
              << std::numeric_limits<size_t>::max() << '\n';
    std::cout << std::endl;
}

void numeric_limits_floating_point() {
    std::cout << "numeric_limits_floating_point:" << std::endl;
    std::cout << "type\t\t│ lowest()\t│ min()\t\t│ max()" << '\n';
    std::cout << "float\t\t│ "
              << std::numeric_limits<float>::lowest() << "\t│ "
              << std::numeric_limits<float>::min() << "\t│ "
              << std::numeric_limits<float>::max() << '\n';
    std::cout << "double\t\t│ "
              << std::numeric_limits<double>::lowest() << "\t│ "
              << std::numeric_limits<double>::min() << "\t│ "
              << std::numeric_limits<double>::max() << '\n';
    std::cout << "long double\t│ "
              << std::numeric_limits<long double>::lowest() << "│ "
              << std::numeric_limits<long double>::min() << "\t│ "
              << std::numeric_limits<long double>::max() << '\n';
    std::cout << std::endl;
}

void test_char_is_signed() {
    std::cout << __func__ << ':' << std::endl;
    char a = static_cast<char>(0);
    std::cout << "char a = 0 has int value = " << static_cast<int>(a) << std::endl;
    std::cout << "--a has int value = " << static_cast<int>(--a) << std::endl;
    std::cout << std::endl;
}

void numeric_limits_is_signed() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << std::boolalpha;
    std::cout << "bool is signed = " << std::numeric_limits<bool>::is_signed << std::endl;
    std::cout << "char is signed = " << std::numeric_limits<char>::is_signed << std::endl;
    std::cout << "unsigned is signed = " << std::numeric_limits<unsigned>::is_signed << std::endl;
    std::cout << "int is signed = " << std::numeric_limits<int>::is_signed << std::endl;
    std::cout << "double is signed = " << std::numeric_limits<double>::is_signed << std::endl;
    std::cout << std::noboolalpha;
    std::cout << std::endl;
}

int main() {
    numeric_limits_integer();
    numeric_limits_floating_point();
    test_char_is_signed();
    numeric_limits_is_signed();
    return 0;
}