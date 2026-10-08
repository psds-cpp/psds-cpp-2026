#include <bitset>
#include <cstdint>
#include <iostream>


void increment_decrement() {
    std::cout << __func__ << std::endl;
    int a = 5;
    std::cout << "Значение: a = " << a << std::endl;
    std::cout << "++a = " << ++a;                     // if combine this 2 row in one
    std::cout << ", теперь a = " << a << std::endl;   // it is potential UB
    std::cout << "a++ = " << a++;
    std::cout << ", теперь a = " << a << std::endl;
    std::cout << "Значение: a = " << a << std::endl;
    std::cout << "--a = " << --a;
    std::cout << ", теперь a = " << a << std::endl;
    std::cout << "a-- = " << a--;
    std::cout << ", теперь a = " << a << std::endl;
    std::cout << std::endl;
}

void arithmetic_operators() {
    std::cout << __func__ << std::endl;
    int a = 15, b = 4;
    double x = 7.5, y = 2.4;

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "x = " << x << ", y = " << y << std::endl;

    std::cout << "+a = " << +a << ", -a = " << -a << std::endl;
    std::cout << "+x = " << +x << ", -x = " << -x << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << " (целочисленное деление)\n";
    std::cout << "a % b = " << a % b << " (остаток от деления)\n";
    std::cout << "x / y = " << x / y << " (деление с плавающей точкой)\n";
    std::cout << "a * 1.0 / b = " << a * 1.0 / b << " (с плавающей точкой)\n";
    std::cout << std::endl;
}

void bitwise_operators() {
    std::cout << __func__ << std::endl;
    uint8_t a = 0b10101010;  // 170
    uint8_t b = 0b11001100;  // 204

    std::cout << "a = " << std::bitset<8>(a) << " (" << +a << ")\n";
    std::cout << "b = " << std::bitset<8>(b) << " (" << +b << ")\n";

    std::cout << "~a = " << std::bitset<8>(~a) << " (" << ~a << ")\n";                     // Побитовое НЕ
    std::cout << "a & b = " << std::bitset<8>(a & b) << " (" << (a & b) << ")\n";      // Побитовое И
    std::cout << "a | b = " << std::bitset<8>(a | b) << " (" << (int)(a | b) << ")\n"; // Побитовое ИЛИ
    std::cout << "a ^ b = " << std::bitset<8>(a ^ b) << " (" << (int)(a ^ b) << ")\n"; // Побитовый XOR

    std::cout << "a << 2 = " << std::bitset<8>(a << 2) << " (" << (a << 2) << ")\n";   // Сдвиг влево
    std::cout << "a >> 2 = " << std::bitset<8>(a >> 2) << " (" << (a >> 2) << ")\n";   // Сдвиг вправо
    std::cout << std::endl;
}

void bit_set() {
    std::cout << __func__ << std::endl;
    uint8_t x = 0b11001100;
    unsigned pos = 5;
    std::cout << "x = " << std::bitset<8>(x) << '\n';

    x |= (1u << pos); // set bit in pos to 1
    std::cout << "after set bit in pos = " << pos << " to 1:\n";
    std::cout << "x = " << std::bitset<8>(x) << '\n';

    x &= (1u << pos); // set bit in pos to 0
    std::cout << "after set bit in pos = " << pos << " to 0:\n";
    std::cout << "x = " << std::bitset<8>(x) << '\n';

    x ^= (1u << pos); // inverse bit in pos
    std::cout << "after inverse bit in pos = " << pos << ":\n";
    std::cout << "x = " << std::bitset<8>(x) << '\n';

    bool y = (x >> pos) & 1u; // read a bit in pos (x & (1u << pos))
    std::cout << "bit in pos = " << y << ":\n";
    std::cout << std::endl;
}

void bit_flags() {
    std::cout << __func__ << std::endl;
    int flags = 0;
    const int READ = 1 << 0;    // 0001
    const int WRITE = 1 << 1;   // 0010
    const int EXECUTE = 1 << 2; // 0100

    std::cout << std::boolalpha;
    std::cout << "flags = " << std::bitset<4>(flags) << '\n';
    flags |= READ | WRITE | EXECUTE;
    std::cout << "(flags |= READ | WRITE | EXECUTE)" << '\n';
    std::cout << "flags = " << std::bitset<4>(flags) << '\n';
    bool res = flags & READ;
    std::cout << "is READ set? (flags & READ) = " << res << '\n';

    flags &= ~WRITE; // сброс флага WRITE
    std::cout << "(flags &= ~WRITE) // set WRITE to 0" << '\n';
    std::cout << "flags = " << std::bitset<4>(flags) << std::endl;
    std::cout << std::noboolalpha;
    std::cout << std::endl;
}

void logical_operators() {
    std::cout << __func__ << std::endl;
    bool t = true, f = false;
    std::cout << std::boolalpha;
    std::cout << "t = " << t << ", f = " << f << std::endl;

    std::cout << "!t = " << !t << ", !f = " << !f << std::endl;

    std::cout << "t && t = " << (t && t) << std::endl;
    std::cout << "t && f = " << (t && f) << std::endl;
    std::cout << "f && f = " << (f && f) << std::endl;

    std::cout << "t || t = " << (t || t) << std::endl;
    std::cout << "f || t = " << (f || t) << std::endl;
    std::cout << "f || f = " << (f || f) << std::endl;
    std::cout << std::noboolalpha;
    std::cout << std::endl;
}

bool _get_bool(bool res, char c) { // print char and return bool
    std::cout << "evaluate '" << c << "' ";
    return res;
}

void short_circuit_evaluation() {
    std::cout << __func__ << std::endl;
    std::cout << std::boolalpha;
    std::cout << "true && false && true : ";
    bool res = _get_bool(true, 'a') &&
               _get_bool(false, 'b') &&
               _get_bool(true, 'a');
    std::cout << ": result = " << res << std::endl;

    std::cout << "true || false || true : ";
    res = _get_bool(true, 'a') ||
          _get_bool(false, 'b') ||
          _get_bool(true, 'a');
    std::cout << ": result = " << res << std::endl;
    std::cout << std::noboolalpha;
    std::cout << std::endl;
}

void integer_comparison() {
    std::cout << __func__ << std::endl;
    int a = 2, b = 3, c = 2;
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

    std::cout << std::boolalpha;
    std::cout << a << " == " << b << ": " << (a == b) << std::endl;
    std::cout << a << " == " << c << ": " << (a == c) << std::endl;
    std::cout << a << " != " << b << ": " << (a != b) << std::endl;
    std::cout << a << " != " << c << ": " << (a != c) << std::endl;
    std::cout << a << " < " << b << ": " << (a < b) << std::endl;
    std::cout << a << " < " << c << ": " << (a < c) << std::endl;
    std::cout << a << " > " << b << ": " << (a > b) << std::endl;
    std::cout << a << " > " << c << ": " << (a > c) << std::endl;
    std::cout << a << " <= " << b << ": " << (a <= b) << std::endl;
    std::cout << a << " <= " << c << ": " << (a <= c) << std::endl;
    std::cout << a << " >= " << b << ": " << (a >= b) << std::endl;
    std::cout << a << " >= " << c << ": " << (a >= c) << std::endl;
    std::cout << std::noboolalpha;
    std::cout << std::endl;
}

void ternary_operator() {
    std::cout << __func__ << std::endl;

    bool condition = false;
    std::cout << "condition = " << condition << " ";
    condition ? std::cout << "is True\n" : std::cout << "is False\n";

    condition = true;
    std::cout << "condition = " << condition << " ";
    condition ? std::cout << "is True\n" : std::cout << "is False\n";

    int a = 2, b = 3;
    int min_value = (a < b) ? a : b;
    std::cout << "min_value = " << min_value << std::endl;

    std::cout << std::endl;
}

void comma_operator() {
    std::cout << __func__ << std::endl;
    int n = 1;
    int m = (++n, std::cout << "n = " << n << '\n', ++n, 2 * n);
    std::cout << "n = " << (++n, n) << '\n';
    std::cout << "m = " << m << std::endl;
    std::cout << std::endl;
}

void ternary_operator_with_comma() {
    std::cout << __func__ << std::endl;
    bool condition = false;
    std::string str = "";

    // condition ? std::cout << "is True\n" : str = "is False\n"; // compilation error

    condition ? std::cout << "is True\n" : (str = "is False\n", std::cout);
    std::cout << "(str == \"is False\\n\") = " << ((str == "is False\n") ? " yes " : " no ") << std::endl;
    std::cout << std::endl;
}

int main() {
    increment_decrement();
    arithmetic_operators();
    bitwise_operators();
    bit_set();
    bit_flags();
    logical_operators();
    short_circuit_evaluation();
    integer_comparison();
    ternary_operator();
    comma_operator();
    ternary_operator_with_comma();
    return 0;
}