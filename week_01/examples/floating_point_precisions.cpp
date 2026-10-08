#include <iomanip>
#include <iostream>


void floating_point_precisions() {
    std::cout << __func__ << std::endl;
    auto f = 3.4028234e38f;    // float
    auto d = 3.4028234e38;     // double
    auto ld = 3.4028234e38l;   // long double

    std::cout << std::setprecision(8) << f << " = " << std::setprecision(39) << f << std::endl;
    std::cout << std::setprecision(8) << d << " = " << std::setprecision(39) << d << std::endl;
    std::cout << std::setprecision(8) << ld << " = " << std::setprecision(39) << ld << std::endl;

    auto fl = 3.4028234e6f;
    std::cout << "fl * fl * fl * fl" << " != " << "(fl * fl) * (fl * fl)" << std::endl;
    std::cout << std::setprecision(39) << fl * fl * fl * fl << " != " << (fl * fl) * (fl * fl) << std::endl;
    std::cout << std::endl;
}

int main() {
    floating_point_precisions();
    return 0;
}