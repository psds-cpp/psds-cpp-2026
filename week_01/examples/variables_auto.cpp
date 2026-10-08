#include <iostream>


void variable_definition_with_auto() {
    std::cout << __func__ << ':' << std::endl;
    auto b = false;   // bool

    auto i = 42;      // int
    auto u = 42u;     // unsigned int
    auto ull = 42Ull; // unsigned long long
    auto ihe = 0x1e5; // int
    auto l = 42l;     // long
    auto x = 9223'372'036'854'775'806; // long (if long has 8 bytes)

    auto d = 3.14;    // double
    auto dp = .1;     // double
    auto de = 1e5;    // double
    auto f = 3.14f;   // float
    auto ld = 42.l;   // long double

    auto c = 'a';     // char
    auto u8c = u8'a'; // char
    auto u16c = u'a'; // char16_t
    auto u32c = U'a'; // char32_t
    auto wc = L'a';   // wchar_t

    auto s = "abc";   // const char*
    auto rs = R"(popular escape-sequences in "C++" '\n' '\t')";// const char*

    std::cout << "b = " << b  << " has type = " << typeid(b).name() << std::endl;
    std::cout << "i = " << i << " has type = " << typeid(i).name() << std::endl;
    std::cout << "u = " << u << " has type = " << typeid(u).name() << std::endl;
    std::cout << "ull = " << ull << " has type = " << typeid(ull).name() << std::endl;
    std::cout << "ihe = " << ihe << " has type = " << typeid(ihe).name() << std::endl;
    std::cout << "l = " << l << " has type = " << typeid(l).name() << std::endl;
    std::cout << "x = " << x  << " has type = " << typeid(x).name() << std::endl;

    std::cout << "d = " << d << " has type = " << typeid(d).name() << std::endl;
    std::cout << "dp = " << dp << " has type = " << typeid(dp).name() << std::endl;
    std::cout << "de = " << de << " has type = " << typeid(de).name() << std::endl;
    std::cout << "f = " << f << " has type = " << typeid(f).name() << std::endl;
    std::cout << "ld = " << ld << " has type = " << typeid(ld).name() << std::endl;

    std::cout << "c = " << c << " has type = " << typeid(c).name() << std::endl;
    std::cout << "u8c = " << u8c << " has type = " << typeid(u8c).name() << std::endl;
    std::cout << "u16c = " << u16c << " has type = " << typeid(u16c).name() << std::endl;
    std::cout << "u32c = " << u32c << " has type = " << typeid(u32c).name() << std::endl;
    std::cout << "wc = " << wc << " has type = " << typeid(wc).name() << std::endl;

    std::cout << "s type for " << s << " has type = " << typeid(s).name() << std::endl;
    std::cout << "rs type for " << rs << " has type = " << typeid(rs).name() << std::endl;

    std::cout << std::endl;
}

int main() {
    variable_definition_with_auto();
    return 0;
}