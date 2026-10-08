#include <iostream>

namespace {
    int var = 20;
} // unnamed namespace

namespace A {
    int var = 30;
} // namespace A

namespace A {
namespace B {
    int var = 40;
} // namespace B
} // namespace A

namespace B {
    int value = 50;
} // namespace B

namespace A { // open namespace A again
    int value = 60; // the same namespace with var = 30
} // namespace A

namespace A::B { // C++17
    int value = 70; // the same namespace with var 40
} // namespace A::B

void unnamed_namespace() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "var from unnamed namespace is accessible" << std::endl;
    std::cout << "var = " << var << std::endl;
    std::cout << std::endl;
}

void named_namespace() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "A::var = " << A::var << std::endl;
    std::cout << "A::B::var = " << A::B::var << std::endl;

    std::cout << "A::value = " << A::value << std::endl;
    std::cout << "B::value = " << B::value << std::endl;
    std::cout << "A::B::value = " << A::B::value << std::endl;
    std::cout << std::endl;
}

void using_namespace() {
    std::cout << __func__ << ':' << std::endl;
    {
        using namespace B;
        std::cout << "using namespace B" << std::endl;
        std::cout << "value = " << value << " is value from B" << std::endl;
    }
    {
        using namespace A::B;
        std::cout << "using namespace A::B" << std::endl;
        // std::cout << "var = " << var << std::endl; // compile error A::B::var and var from unnamed scope in one scope
    }
    {
        using A::value;
        std::cout << "using A::value" << std::endl;
        std::cout << "value = " << value << " is value from A" << std::endl;
        std::cout << "var = " << var << " is var from unnamed namespace" << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    unnamed_namespace();
    named_namespace();
    using_namespace();
    return 0;
}