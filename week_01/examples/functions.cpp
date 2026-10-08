#include <iostream>


int PrintValue(int value) {
    std::cout << "value = " << value << std::endl;
    return value;
}

void Nothing(int, int, int) {}

void order_of_evaluation() {
    // compile using g++ and clang++
    std::cout << __func__ << ':' << std::endl;
    Nothing(PrintValue(1), PrintValue(2), PrintValue(3));
    int value = PrintValue(1) + PrintValue(2) * (PrintValue(3) + PrintValue(4));
    std::cout << "value = " << value << std::endl;
    std::cout << std::endl;
}

void PrintValues(int x, float f = 0.0, char c = 'a') {
    std::cout << "x = " << x << ", f = " << f << ", c = " << c << std::endl;
}

void default_arguments() {
    std::cout << __func__ << ':' << std::endl;
    int x = 10;
    float y = 3.14;
    char z = 'z';
    PrintValues(x, y, z);
    PrintValues(x, y);
    PrintValues(x);
    std::cout << std::endl;
}

void PrintArray(int arr[], size_t size) {
    std::cout << "{";
    if (size == 0) {
        std::cout << "}" << std::endl;
        return;
    }
    for (size_t i = 0; i < size - 1; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[size - 1] << '}' << std::endl;
}

void function_with_array() {
    std::cout << __func__ << ':' << std::endl;
    int x[] = {1, 2, 3, 4, 5};
    size_t size = std::size(x);
    PrintArray(x, size);
    PrintArray(nullptr, 0);
    std::cout << std::endl;
}

void PrintCharArray(char arr[]) {
    std::cout << "{";
    for (size_t i = 0; arr[i] != '\0'; ++i) {
        std::cout << "\'" << arr[i] << "\', ";
    }
    std::cout << "\'\\0\'" << "}" << std::endl;
}

void function_with_char_array() {
    std::cout << __func__ << ':' << std::endl;
    char x[] = "Hello, my friend!";
    PrintCharArray(x);
    char y[] = "";
    PrintCharArray(y);
    std::cout << std::endl;
}

void function_type() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "int(int) = " << typeid(PrintValue).name() << std::endl;
    std::cout << "void(int, int, int) = " << typeid(Nothing).name() << std::endl;
    std::cout << "void(void) = " << typeid(function_type).name() << std::endl;
    std::cout << "void(int, float, char) = " << typeid(PrintValues).name() << std::endl;
    std::cout << "void(int[], size_t) = " << typeid(PrintArray).name() << std::endl;
    std::cout << "void(char[]) = " << typeid(PrintCharArray).name() << std::endl;
    std::cout << std::endl;
}

int main() {
    order_of_evaluation();
    default_arguments();
    function_with_array();
    function_with_char_array();
    function_type();
}