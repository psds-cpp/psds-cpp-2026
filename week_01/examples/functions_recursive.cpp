uint64_t FibonacciRecursive(uint64_t pos) {
    if (pos < 2) {
        return 0;
    }
    if (pos == 2) {
        return 1;
    }
    return FibonacciRecursive(pos - 1) + FibonacciRecursive(pos - 2);
}

uint64_t Fibonacci(uint64_t pos) {
    if (pos < 2) {
        return 0;
    }
    uint64_t prev_2 = 0;
    uint64_t prev_1 = 1;
    uint64_t result = 1;
    for (uint64_t i = 2; i < pos; ++i) {
        result = prev_1 + prev_2;
        prev_2 = prev_1;
        prev_1 = result;
    }
    return result;
}

void PrintFibonacciRecursive() {
    std::cout << __func__ << std::endl;
    for (int i = 1; i < 30; ++i) {
        std::cout << FibonacciRecursive(i) << ' ';
    }
    std::cout << std::endl;
}

void PrintFibonacci() {
    std::cout << __func__ << std::endl;
    for (int i = 1; i < 30; ++i) {
        std::cout << Fibonacci(i) << ' ';
    }
    std::cout << std::endl;
}

int main() {
     PrintFibonacciRecursive();
     PrintFibonacci();
}