#include <iostream>

void while_loop() {
    std::cout << __func__ << ':' << std::endl;
    int value = 0, sum = 0;
    while (std::cin >> value) {
        sum += value;
    }
    std::cout << "sum = " << sum << std::endl;
    std::cout << std::endl;
}

void do_while_loop() {
    std::cout << __func__ << ':' << std::endl;
    int userChoice = 3;
    do {
        std::cout << "Select:\n";
        std::cout << "1 - to continue\n";
        std::cout << "2 - to exit\n";
        std::cout << "Your choice: " << userChoice;
        if (userChoice == 1) {
            std::cout << "continue...\n";
            userChoice = 2;
            continue;
        }
        if (userChoice != 2) {
            std::cout << "continue anyway...\n";
            userChoice = 1;
        }
    } while (userChoice != 2);
    std::cout << "Good bye, my friend\n";
    std::cout << std::endl;
}

void do_while_infinite_loop_with_error() {
    std::cout << __func__ << ':' << std::endl;
    int error = 0;
    int id = 0;
    do {
        std::cout << "Do something...\n";
        if (id % 4 == 3) {
            error = 1;
        }
        if (error) {
            std::cout << "ERROR: something went wrong\n";
            break;
        }
        ++id;
    } while (true);
    std::cout << std::endl;
}

void for_loop() {
    std::cout << __func__ << ':' << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << i << '\t' << i * i << '\n';
    }
    std::cout << std::endl;

    for (int i = 0, j = 0; i < 10; ++i, j += 2) {
        std::cout << i << " * " << j << " = "  << i * j << '\n';
    }
    std::cout << std::endl;
}

void range_based_for_loop() {
    std::cout << __func__ << ':' << std::endl;
    char str[] = "separating";
    for (auto c : str) {
        std::cout << c << " ";
    }
    std::cout << std::endl << std::endl;
}

void nested_for_loop() {
    std::cout << __func__ << ':' << std::endl;
    const size_t size = 3;
    int matrix[][size] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = size - 1; j < size; --j) {
            std::cout << matrix[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void break_loop() {
    std::cout << __func__ << ':' << std::endl;
    char break_symbol = 'k';
    for (char c = 'a'; c < 'z'; c += 2) {
        if (c >= break_symbol) {
            break;
        }
        std::cout << c << " ";
    }
    std::cout << std::endl << std::endl;
}

void continue_loop() {
    std::cout << __func__ << ':' << std::endl;
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    while_loop();
    do_while_loop();
    do_while_infinite_loop_with_error();
    for_loop();
    range_based_for_loop();
    nested_for_loop();
    break_loop();
    continue_loop();
    return 0;
}