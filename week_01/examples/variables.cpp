#include <iostream>


void variable_definition() {
    std::cout << __func__ << ':' << std::endl;
    char c = '1';
    char ce = '\\';
    bool b = true;
    int i = 42;
    unsigned ui = 42; // unsigned int
    short int si = 17;
    long li = 12321321312;
    long long lli = 12321321312;
    float f = 2.71828;
    double d = 3.141592;
    long double ld = 1e15;

    std::cout << "c = " << c << std::endl;
    std::cout << "ce = " << ce << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "ui = " << ui << std::endl;
    std::cout << "si = " << si << std::endl;
    std::cout << "li = " << li << std::endl;
    std::cout << "lli = " << lli << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "ld = " << ld << std::endl;
    std::cout << std::endl;
}

int main() {
    variable_definition();
    return 0;
}