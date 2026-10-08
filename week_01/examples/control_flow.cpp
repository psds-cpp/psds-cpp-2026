#include <iostream>


void if_statement() {
    std::cout << __func__ << ':' << std::endl;
    int age = 30;
    if (age > 18 && age < 60 && age != 33) {
        std::cout << "condition is true" << std::endl;
    }
    std::cout << std::endl;
}

void if_else_statement() {
    std::cout << __func__ << ':' << std::endl;
    int number = 7;
    std::cout << "number = " << number;
    if (number % 2 == 0) {
        std::cout << " is even number\n";
    } else {
        std::cout << " is odd number\n";
    }
    std::cout << std::endl;
}

void if_else_full_statement() {
    std::cout << __func__ << ':' << std::endl;
    int score = 85;
    std::cout << "Your score  = " << score << std::endl;
    if (score >= 90) {
        std::cout << "Mark: A\n";
    } else if (score >= 80) {
        std::cout << "Mark: B\n";
    } else if (score >= 70) {
        std::cout << "Mark: C\n";
    } else {
        std::cout << "Mark: G (Good bye)\n";
    }
    std::cout << std::endl;
}

void if_with_init_statement() {
    std::cout << __func__ << ':' << std::endl;
    int value = 21;
    std::cout << "value = " << value << std::endl;
    if (int local_var = value; local_var > 10) {
        std::cout << "next value = " << ++local_var << std::endl;
    }
    std::cout << "value = " << value << std::endl;
    std::cout << std::endl;
}

void switch_statement_int() {
    std::cout << __func__ << ':' << std::endl;
    int value = 43;
    switch (value % 3) {
        case 1:
            std::cout << "remainder = 1" << std::endl; // it's required to substract 1 from the value
            break;
        case 2:
            std::cout << "remainder = 2" << std::endl; // it's required to add 1 to the value
            break;
        default:
            std::cout << "the value is devided by 3" << std::endl;
    }
    std::cout << std::endl;
}

void switch_statement_char() {
    std::cout << __func__ << ':' << std::endl;
    char operation = '+';
    int lhs = 10, rhs = 3;
    switch (operation) {
        case '+':
            std::cout << lhs + rhs << std::endl;
            break;
        case '-':
            std::cout << lhs - rhs << std::endl;
            break;
        case '/':
            std::cout << lhs / rhs << std::endl;
            break;
        case '*':
            std::cout << lhs * rhs << std::endl;
            break;
        default:
            std::cout << "unknown operation: " << operation << std::endl;
    }
    std::cout << std::endl;
}

void switch_statement_char_default() {
    std::cout << __func__ << ':' << std::endl;
    char grade = 'X';
    std::cout << "Оценка: " << grade << std::endl;

    switch (grade) {
        case 'A': std::cout << "Отлично!\n"; break;
        case 'B': std::cout << "Хорошо!\n"; break;
        case 'C': std::cout << "Удовлетворительно\n"; break;
        case 'D': std::cout << "Плохо\n"; break;
        case 'F': std::cout << "Неудовлетворительно\n"; break;
        default: std::cout << "Вы превзошли все ожидания\n";
    }
    std::cout << std::endl;
}

void switch_statement_enum_fallthrough() {
    std::cout << __func__ << ':' << std::endl;
    enum class Error {
        LOW_ERROR,
        MIDDLE_ERROR,
        HIGH_ERROR
    };

    Error error = Error::LOW_ERROR;
    switch (error) {
        case Error::LOW_ERROR:
            std::cout << "LOW_ERROR" << std::endl;
            [[fallthrough]];
        case Error::MIDDLE_ERROR:
            std::cout << "MIDDLE_ERROR" << std::endl;
            [[fallthrough]];
        case Error::HIGH_ERROR:
            std::cout << "HIGH_ERROR" << std::endl;
    }
    std::cout << std::endl;
}

void switch_statement_enum_iteration() {
    enum class CommandTypeCount {
        INIT,
        UPDATE,
        FINISH,
        COUNT
    };

    std::cout << __func__ << ':' << std::endl;
    for (int i = 0; i < static_cast<int>(CommandTypeCount::COUNT); ++i) {
        switch (static_cast<CommandTypeCount>(i)) {
            case CommandTypeCount::INIT: std::cout << "INIT" << std::endl; break;
            case CommandTypeCount::UPDATE: std::cout << "UPDATE" << std::endl; break;
            case CommandTypeCount::FINISH: std::cout << "FINISH" << std::endl; break;
            case CommandTypeCount::COUNT: std::cout << "COUNT" << std::endl; break;
            default: std::cout << "unknown enum" << std::endl; break;
        }
    }
    std::cout << std::endl;
}

void switch_statement_with_local_var_error() {
    std::cout << __func__ << ':' << std::endl;
    switch (2) {
        case 2:
            int x = 21; // initialization
            std::cout << x << '\n';
            break;
        default:
            // compilation error: jump to default:
            // would enter the scope of 'x' without initializing it
            std::cout << "default\n";
            break;
    }
}

void switch_statement_with_local_var() {
    std::cout << __func__ << ':' << std::endl;
    switch (2) {
        case 2: {
            int x = 21; // initialization
            std::cout << x << '\n';
            break;
        } // end of scope 'x'
        default:
            std::cout << "default\n";
            break;
    }
    std::cout << std::endl;
}

void switch_statement_with_init_statement() {
    std::cout << __func__ << ':' << std::endl;
    switch (int x = 21; 2) {
        case 2:
            std::cout << x << '\n';
            break;
        default:
            std::cout << "default\n";
            break;
    }
    std::cout << std::endl;
}

int main() {
    if_statement();
    if_else_statement();
    if_else_full_statement();
    if_with_init_statement();

    switch_statement_int();
    switch_statement_char();
    switch_statement_char_default();
    switch_statement_enum_fallthrough();
    switch_statement_enum_iteration();
    // switch_statement_with_local_var_error(); // compile error;
    switch_statement_with_local_var();
    switch_statement_with_init_statement();
    return 0;
}