#include <iostream>


int uninitialized_var; // global scope

void use_uninitialized_var_in_func() {
    std::cout << __func__ << ':' << std::endl;
    int y, x;
    std::cout << "uninitialized y = " << y << ", x = " << x << std::endl; // UB
    std::cout << std::endl;
}

void incorrect_shadowing() {
    std::cout << __func__ << ':' << std::endl;
    int x = 42;
    std::cout << "x = " << x << std::endl;
    {
        int x = x; // UB, x != 42, because inner x is in scope before `= x`
        std::cout << "local x != 42, x = " << x << std::endl;
    }
    int y = x; // y = 42
    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "use_global_scope_from_" << __func__ << ':' << std::endl;
    std::cout << "uninitialized_global_var = " << uninitialized_var  << std::endl;
    std::cout << std::endl;
    int x;
    std::cout << __func__ << ": uninitialized x = " << x << std::endl; // UB

    use_uninitialized_var_in_func();
    incorrect_shadowing();
    return 0;
}