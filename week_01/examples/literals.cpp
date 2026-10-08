#include <iostream>

void integral_literals() {
    std::cout << __func__ << ':' << std::endl;
    int dec = 42;
    int oct = 042;
    int hex = 0x42;
    int bin = 0b101010;

    std::cout << "42 is " << dec << std::endl;
    std::cout << "042 is " << oct << std::endl;
    std::cout << "0x42 is " << hex << std::endl;
    std::cout << "0b101010 is " << bin << std::endl;
    std::cout << std::endl;
}

// Литерал для расстояния в метрах
constexpr long double operator""_m(long double meters) {
    return meters;
}

// Литерал для расстояния в сантиметрах
constexpr long double operator""_cm(long double cm) {
    return cm / 100.0;
}

// Литерал для расстояния в киллометрах (целочисленный для примера)
constexpr unsigned long long operator""_km(unsigned long long km) {
    return km * 1000;
}

void user_defined_literals() {
    std::cout << __func__ << ':' << std::endl;
    auto ivleeva = 13.0_cm;
    auto height = 1.96_m;
    auto to_the_moon = 384'400_km;

    std::cout << "13.0_cm in meters = " << ivleeva << std::endl;
    std::cout << "1.96_m in meters = " << height << std::endl;
    std::cout << "384'400_km in meters = " << to_the_moon << std::endl;
    std::cout << std::endl;
}

int main() {
    integral_literals();
    user_defined_literals();
    return 0;
}