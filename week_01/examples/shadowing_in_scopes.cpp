#include <iostream>


int var = 10; // global scope

void use_global_scope_from_function() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "var = " << var  << std::endl;
    std::cout << std::endl;
}

void simple_shadowing() {
    std::cout << __func__ << ':' << std::endl;
    int x = 42;
    std::cout << "x = " << x << std::endl; // x = 42
    {
        x = 33; // update value of x from outer scope
        std::cout << "x = " << x << std::endl; // x = 33
        int x = 24; // shadowing
        std::cout << "x = " << x << std::endl; // x = 24
    } // end of local x
    std::cout << "x = " << x << std::endl; // x = 33
    std::cout << std::endl;
}

void shadowing_of_global_var_in_func() { // function block scope
    std::cout << __func__ << ':' << std::endl;
    std::cout << "global scope var = " << var  << std::endl;
    int var = 20; // shadowing of global var = 10
    std::cout << "local function block scope var = " << var << std::endl;
    std::cout << "::var = " << ::var << " - access to global scope"  << std::endl;
    { // more local block scope
        std::cout << "{\n\tinside more local block scope in " << __func__ << ':' << std::endl;
        std::cout << "outer of current block scope var = " << var << std::endl;
        int var = 30; // shadowing of local var in shadowing_func
        std::cout << "\tlocal block scope var = " << var << std::endl;
        std::cout << "\t::var = " << ::var << " - again access to global scope"  << std::endl;
        std::cout << "\tbut function block scope var is unreachable now\n}" << std::endl;
    }
    std::cout << "after ends of block scope, local function block scope var = " << var << std::endl;
    // int var = 40; // compilation error, because redefinition var in the same scope
    std::cout << std::endl;
}

int main() {
    std::cout << "use_global_scope_from_" << __func__ << ':' << std::endl;
    std::cout << "var = " << var  << std::endl;
    std::cout << std::endl;

    use_global_scope_from_function();
    simple_shadowing()
    shadowing_in_func();
    return 0;
}