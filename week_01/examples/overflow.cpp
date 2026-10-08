#include <cmath>
#include <iostream>
#include <limits>
#include <iomanip>


void overflow_examples() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "Signed integral types overflowing is UB:" << std::endl;
    std::cout << "MAX_INT = " << std::numeric_limits<int>::max() << std::endl;
    // int overflow = max_int + 1;  // UNDEFINED BEHAVIOR
    std::cout << "MAX_INT + 1 = " << std::numeric_limits<int>::max() + 1 << " (overflow)" << std::endl;
    std::cout << std::endl;

    std::cout << "Unsigned integral types overflowing is defined behavior (modulo arithmetic):" << std::endl;
    unsigned int max_uint = std::numeric_limits<unsigned int>::max();
    unsigned int uint_overflow = max_uint + 1;
    std::cout << "MAX_UINT + 1 = " << uint_overflow << " (wrap-around)" << std::endl;
    std::cout << std::endl;


    std::cout << "floating-point types overflowing is defined behavior ";
    float max_float = std::numeric_limits<float>::max();
    float huge_float = max_float * 2.0f;  // infinity
    std::cout << "MAX_FLOAT = " << max_float << std::endl;
    std::cout << "MAX_FLOAT * 2 = " << huge_float << " (infinity)\n";
    std::cout << "Is infinity? " << std::isinf(huge_float) << std::endl;
    std::cout << std::endl;

    float min_float = std::numeric_limits<float>::min();
    float tiny_float = min_float / 2.0f;
    std::cout << "MIN_FLOAT = " << min_float << std::endl;
    std::cout << "MIN_FLOAT / 2 = " << tiny_float << " (subnormal)\n";
}

int main() {
    overflow_examples();
    return 0;
}
