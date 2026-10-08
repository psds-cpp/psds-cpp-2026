#include <iostream>


// run
// ./io_streams < io_streams_input.txt > io_streams_output.txt 2> io_streams_error.txt
int main() {
    int num_pairs;
    std::cin >> num_pairs;

    double left, right;
    for (int i = 0; i < num_pairs; ++i) {
        std::cin >> left >> right;

        if (right == 0) {
            std::cerr << "Error in pair " << i << ": Cannot divide " << left << " by zero!" << std::endl;
            continue;
        }
        double result = left / right;
        std::cout << "Pair " << i << ": " << left << " / " << right << " = " << result << std::endl;
    }
    return 0;
}