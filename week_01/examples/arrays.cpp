#include <cstring>
#include <iostream>

void _print_array(int array[], size_t size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void array() {
    std::cout << __func__ << ": " << std::endl;
    int arr1[5];                   // неинициализированный массив
    int arr2[5] = {1, 2, 3, 4, 5}; // явная инициализация
    int arr3[] = {1, 2, 3, 4, 5};  // автоматическое определение размера
    int arr4[5] = {1, 2};          // остальные элементы = 0
    int arr5[5] = {};              // все элементы = 0

    (std::cout << "arr1 = ", _print_array(arr1, std::size(arr1))); // UB
    (std::cout << "arr2 = ", _print_array(arr2, std::size(arr2)));
    (std::cout << "arr3 = ", _print_array(arr3, std::size(arr3)));
    (std::cout << "arr4 = ", _print_array(arr4, std::size(arr4)));
    (std::cout << "arr5 = ", _print_array(arr5, std::size(arr5)));
    std::cout << std::endl;
}


void not_array_with_auto() {
    std::cout << __func__ << ": " << std::endl;
    int a[] = {1, 2, 3, 4, 5};
    auto b = {1, 2, 3, 4, 5};
    std::cout << "a type = " << typeid(a).name() << std::endl;
    std::cout << "b type = " << typeid(b).name() << std::endl;
    std::cout << std::endl;
}

void array_size() {
    std::cout << __func__ << ": " << std::endl;
    {
        const int size = 5;
        int array[size] = {1, 2, 3};
        std::cout << "size = " << size << std::endl;
    }
    {
        constexpr int size = 5;
        int array[size] = {1, 2, 3};
        std::cout << "size = " << size << std::endl;
    }
    {
        int array[] = {2, 4, 5, 6, 7};
        size_t size = sizeof(array) / sizeof(int);
        std::cout << "size = " << size << std::endl;
    }
    {
        int array[] = {2, 4, 5, 6, 7};
        size_t size = sizeof(array) / sizeof(array[0]);
        std::cout << "size = " << size << std::endl;
    }
    {
        int array[] = {2, 4, 5, 6, 7};
        size_t size = std::size(array); // c++17
        std::cout << "size = " << size << std::endl;
    }
    std::cout << std::endl;
}

void char_array() {
    std::cout << __func__ << ": " << std::endl;
    char str_one[] = "Hello"   " "   "bro";
    char str_two[] = {'H', 'e', 'l', 'l', 'o', ' ', 'b', 'r', 'o', '\0'};
    std::cout << "size str_one = " << std::size(str_one) << std::endl;
    std::cout << "size str_two = " << std::size(str_two) << std::endl;

    for (auto c : str_one) {
        std::cout << static_cast<int>(c) << " = " << c << "; ";
    }
    std::cout << std::endl;
    for (auto c : str_two) {
        std::cout << static_cast<int>(c) << " = " << c << "; ";
    }
    std::cout << std::endl;

    std::cout << std::boolalpha;
    std::cout << "str_one == str_two ? " << (std::strcmp(str_one, str_two) == 0) << std::endl; //  == 0 is equal
    std::cout << std::noboolalpha;

    std::cout << std::endl;
}

void _print_array(int array[][3], int row) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void two_dimensional_array() {
    std::cout << __func__ << ": " << std::endl;
    // int matrix1[3][3];                                     // неинициализированный массив 3x3
    int matrix2[2][3] = {{1, 2, 3}, {4, 5, 6}};      // явная инициализация
    int matrix3[][3] = {{1, 2, 3}, {4, 5, 6}};       // автоопределение строк
    int matrix4[3][3] = {{1}, {4, 5}, {7, 8, 9}}; // частичная инициализация
    int matrix5[3][3] = {};                                // инициализация нулями
    int matrix6[3][3] = {1, 2, 3, 4, 5, 6};                // плоская инициализация остальные элементы 0

    // _print_array(matrix1, 3); // UB
    _print_array(matrix2, 2);
    _print_array(matrix3, 2);
    _print_array(matrix4, 3);
    _print_array(matrix5, 3);
    _print_array(matrix6, 3);
    std::cout << std::endl;
}

void uniform_init_two_dimensional_array() {
    std::cout << __func__ << ": " << std::endl;
    int matrix2[2][3]{{1, 2, 3}, {4, 5, 6}};      // явная инициализация
    int matrix3[][3]{{1, 2, 3}, {4, 5, 6}};       // автоопределение строк
    int matrix4[3][3]{{1}, {4, 5}, {7, 8, 9}}; // частичная инициализация
    int matrix5[3][3]{};                                // инициализация нулями
    int matrix6[3][3]{1, 2, 3, 4, 5, 6};                // плоская инициализация остальные элементы 0

    _print_array(matrix2, 2);
    _print_array(matrix3, 2);
    _print_array(matrix4, 3);
    _print_array(matrix5, 3);
    _print_array(matrix6, 3);
    std::cout << std::endl;
}

int main() {
    array();
    not_array_with_auto();
    array_size();
    char_array();
    two_dimensional_array();
    uniform_init_two_dimensional_array();
    return 0;
}