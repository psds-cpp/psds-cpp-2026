#include <iostream>
#include <limits>
#include <iomanip>


void promotions() {
    std::cout << __func__ << ':' << std::endl;
    char c = 'A';
    short s = 100;
    bool b = true;

    int i1 = c;    // char -> int (promotion)
    int i2 = s;    // short -> int (promotion)
    int i3 = b;    // bool -> int (promotion)

    std::cout << std::boolalpha;
    std::cout << "char -> int: " << c << " -> " << i1 << " (safe)\n";
    std::cout << "short -> int: " << s << " -> " << i2 << " (safe)\n";
    std::cout << "bool -> int: " << b << " -> " << i3 << " (safe)\n";

    float f = 3.141592f;
    double d = f;  // float -> double (promotion)
    std::cout << std::setprecision(15) << "float -> double: " << f << " -> " << d << " (safe)\n";
    std::cout << std::endl;
}

void integral_promotions_details() {
    std::cout << __func__ << ':' << std::endl;
    char c = 'X';
    unsigned char uc = 200;
    short s = 32000;
    bool b = true;

    auto expr1 = c + uc;   // оба -> int
    auto expr2 = s + b;    // оба -> int
    auto expr3 = c * s;    // оба -> int
    auto expr4 = b + b;    // оба -> int = 2

    std::cout << "char + unsigned char: type =" << typeid(expr1).name() << ", value = " << expr1 << std::endl;
    std::cout << "short + bool: type = " << typeid(expr2).name() << ", value = " << expr2 << std::endl;
    std::cout << "char * short: type = " << typeid(expr3).name() << ", value = " << expr3 << std::endl;
    std::cout << "bool + bool: type = " << typeid(expr4).name() << ", value = " << expr4 << std::endl;
    std::cout << std::endl;
}

void conversions() {
    std::cout << __func__ << ':' << std::endl;
    int large_int = 1000000;
    short small_short = large_int;  // int -> short (conversion)
    char small_char = large_int;    // int -> char (conversion)

    std::cout << "int -> short: " << large_int << " -> " << small_short << std::endl;
    std::cout << "int -> char: " << large_int << " -> " << static_cast<int>(small_char) << std::endl;

    int i_neg = -1;
    int i_pos = 42;
    unsigned u = 1;
    auto res_with_neg = i_neg + u;
    auto res_with_pos = i_pos + u;
    std::cout << "(-1 + 1u) = " << res_with_neg << ", type = " << typeid(res_with_pos).name() << std::endl;
    std::cout << "(42 + 1u) = " << res_with_pos << ", type = " << typeid(res_with_pos).name() << std::endl;
    std::cout << "(-1 < 1u) = " << std::boolalpha << (i_neg < u) << std::endl;

    long l = 100;
    long long ll = 100;
    std::cout << "sizeof(long) = " << sizeof(l) << ", sizeof(long long) = " << sizeof(ll) << std::endl;
    std::cout << "l type = " << typeid(l).name() << ", ll type = " << typeid(ll).name() << std::endl;
    std::cout << "(l + ll) has type " << typeid(l + ll).name() << std::endl;


    double big_double = 3.141592653589793;
    float small_float = big_double;       // double -> float (conversion)
    int i_double = big_double;            // double -> int (conversion)
    int i_double_neg = -big_double;       // double -> int (conversion)
    unsigned u_double_neg = -big_double;  // double -> unsigned int (conversion)
    std::cout << "double -> float: " << std::setprecision(15) << big_double
              << " -> " << small_float << " (precision loss)\n";
    std::cout << "double -> int: " <<  big_double << " -> " << i_double << std::endl;
    std::cout << "double -> int: " <<  -big_double << " -> " << i_double_neg << std::endl;
    std::cout << "double -> unsigned int: " <<  -big_double << " -> " << u_double_neg << std::endl;
    std::cout << std::endl;


}

void floating_point_to_bool() {
    std::cout << __func__ << ':' << std::endl;
    double positive = 3.14;
    double negative = -2.71;
    double zero = 0.0;
    double tiny = 1e-308;  // Очень маленькое, но не ноль
    double infinity = std::numeric_limits<double>::infinity();
    double nan = std::numeric_limits<double>::quiet_NaN();

    std::cout << std::boolalpha;
    std::cout << "3.14 -> bool: " << static_cast<bool>(positive) << std::endl;
    std::cout << "-2.71 -> bool: " << static_cast<bool>(negative) << std::endl;
    std::cout << "0.0 -> bool: " << static_cast<bool>(zero) << std::endl;
    std::cout << "1e-308 -> bool: " << static_cast<bool>(tiny) << std::endl;
    std::cout << "infinity -> bool: " << static_cast<bool>(infinity) << std::endl;
    std::cout << "NaN -> bool: " << static_cast<bool>(nan) << std::endl;

    std::cout << "\nImplicit floating-point to bool conversions:\n";
    if (positive) std::cout << "3.14 is true\n";
    if (negative) std::cout << "-2.71 is true\n";
    if (!zero) std::cout << "0.0 is false\n";
    if (nan) std::cout << "NaN is true\n";

    std::cout << "\nFeatures of NaN:\n";
    std::cout << "NaN == NaN: " << (nan == nan) << " (false!)\n";
    std::cout << "NaN != NaN: " << (nan != nan) << " (true!)\n";
    std::cout << std::endl;
}

void bool_to_another_type() {
    std::cout << __func__ << ':' << std::endl;
    bool is_true = true;
    bool is_false = false;

    int i_true = is_true;
    int i_false = is_false;
    double d_true = is_true;
    double d_false = is_false;

    std::cout << std::boolalpha;
    std::cout << is_true << " in double = " << d_true << ", in int = " << i_true << std::endl;
    std::cout << is_false << " in double = " << d_false << ", in int = " << i_false << std::endl;
    std::cout << std::endl;
}

void explicit_cast() {
    std::cout << __func__ << ':' << std::endl;
    double pi = 3.14159;
    std::cout << "C-style cast is (int)pi = " << (int)pi << std::endl;
    std::cout << "Functional notation cast is int(pi) = " << int(pi) << std::endl;
    std::cout << "static_cast<int>(pi) = " << static_cast<int>(pi) << std::endl;
    std::cout << std::endl;

    int i = -42;
    std::cout << "i = " << i << ", static_cast<unsigned>(i) = " << static_cast<unsigned>(i) << std::endl;

    char c = 'D';
    std::cout << "c = " << c << ", static_cast<double>(c) = " << static_cast<double>(c) << std::endl;
    std::cout << std::endl;
}

int main() {
    promotions();
    integral_promotions_details();
    conversions();
    floating_point_to_bool();
    bool_to_another_type();
    explicit_cast();
    return 0;
}