#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

#include "print_bits.cpp"


namespace fs = std::filesystem;

std::string CaptureOutput(void (*func)(long long, size_t), long long value, size_t bytes) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func(value, bytes);
    std::cout.rdbuf(old);
    return buffer.str();
}

fs::path FindSourceCode() {
    std::vector<fs::path> search_paths = {
        "01_week/tasks/print_bits/print_bits.cpp",
        "tasks/print_bits/print_bits.cpp",
        "print_bits/print_bits.cpp",
        "print_bits.cpp",
        "tasks/print_bits.cpp"
    };

    for (const auto& path : search_paths) {
        if (fs::exists(path) && fs::is_regular_file(path)) {
            return fs::absolute(path);
        }
    }

    return {};
}

TEST(CodeInspectionTest, NoBitsetInCode) {
    fs::path code_path = FindSourceCode();
    std::ifstream file(code_path);
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    ASSERT_TRUE(content.size()) << "Run the test from the root of repository\n";
    size_t bitset_pos = content.find("#include <bitset>");
    ASSERT_EQ(bitset_pos, std::string::npos)
        << "Обнаружено использование #include <bitset> в коде!";
    std::cerr << bitset_pos << std::endl;
    bitset_pos = content.find("bitset");
    EXPECT_EQ(bitset_pos, std::string::npos)
        << "Обнаружено использование bitset в коде!";
}

TEST(PrintBitsTest, FunctionSignature) {
    static_assert(std::is_same_v<decltype(&PrintBits), void (*)(long long, size_t)>,
        "function must have signature: void PrintBits(long long, size_t)");
}

TEST(PrintBitsTest, UnsignedNumbersOneBytes) {
    EXPECT_EQ(CaptureOutput(PrintBits, 0, 1), "0b0000'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 255, 1), "0b1111'1111\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 170, 1), "0b1010'1010\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 85, 1), "0b0101'0101\n");
}

TEST(PrintBitsTest, DifferentSizes) {
    EXPECT_EQ(CaptureOutput(PrintBits, 0xAA, 1), "0b1010'1010\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 0xAAAA, 2), "0b1010'1010'1010'1010\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 0xAAAAAAAA, 4), "0b1010'1010'1010'1010'1010'1010'1010'1010\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 0xAAAAAAAAAAAAAAAA, 8),
        "0b1010'1010'1010'1010'1010'1010'1010'1010'1010'1010'1010'1010'1010'1010'1010'1010\n");
}

TEST(PrintBitsTest, MinusOne) {
    EXPECT_EQ(CaptureOutput(PrintBits, -1, 1), "0b1111'1111\n");
    EXPECT_EQ(CaptureOutput(PrintBits, -1, 2), "0b1111'1111'1111'1111\n");
    EXPECT_EQ(CaptureOutput(PrintBits, -1, 4), "0b1111'1111'1111'1111'1111'1111'1111'1111\n");
    EXPECT_EQ(CaptureOutput(PrintBits, -1, 8),
        "0b1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111\n");
}

TEST(PrintBitsTest, ZeroValue) {
    EXPECT_EQ(CaptureOutput(PrintBits, 0, 1), "0b0000'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 0, 2), "0b0000'0000'0000'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 0, 4), "0b0000'0000'0000'0000'0000'0000'0000'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, 0, 8),
        "0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000\n");
}

TEST(PrintBitsTest, LongLong) {
    long long value = 0x123456789ABCDEF0;
    EXPECT_EQ(CaptureOutput(PrintBits, value, sizeof(value)),
        "0b0001'0010'0011'0100'0101'0110'0111'1000'1001'1010'1011'1100'1101'1110'1111'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, value, 6),
        "0b0101'0110'0111'1000'1001'1010'1011'1100'1101'1110'1111'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, value, 3), "0b1011'1100'1101'1110'1111'0000\n");
    EXPECT_EQ(CaptureOutput(PrintBits, value, 1), "0b1111'0000\n");
}

TEST(PrintBitsTest, NegativeValues) {
    {
        int8_t value = -42;
        EXPECT_EQ(CaptureOutput(PrintBits, value, sizeof(value)), "0b1101'0110\n");
        EXPECT_EQ(CaptureOutput(PrintBits, value, 2), "0b1111'1111'1101'0110\n");
    }
    {
        int16_t value = -42;
        EXPECT_EQ(CaptureOutput(PrintBits, value, sizeof(value)), "0b1111'1111'1101'0110\n");
    }
}

TEST(PrintBitsTest, LimitValues) {
    {
        int32_t value = std::numeric_limits<int32_t>::max();
        EXPECT_EQ(CaptureOutput(PrintBits, value, sizeof(value)), "0b0111'1111'1111'1111'1111'1111'1111'1111\n");
    }
    {
        int32_t value = std::numeric_limits<int32_t>::min();
        EXPECT_EQ(CaptureOutput(PrintBits, value, sizeof(value)), "0b1000'0000'0000'0000'0000'0000'0000'0000\n");
    }
}

TEST(PrintBitsTest, BoolValues) {
    bool is_true = true;
    bool is_false = false;
    EXPECT_EQ(CaptureOutput(PrintBits, is_true, sizeof(is_true)), "0b0000'0001\n");
    EXPECT_EQ(CaptureOutput(PrintBits, is_false, sizeof(is_true)), "0b0000'0000\n");;
}



