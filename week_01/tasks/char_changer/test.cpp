#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "char_changer.cpp"


TEST(SignatureTest, FunctionSignature) {
    static_assert(std::is_same_v<decltype(&CharChanger), size_t (*)(char*, size_t, char)>,
        "function must have signature: size_t CharChanger(char*, size_t, char)");
}

void CheckAnswer(char array[], size_t size, char del, char expected[], size_t expected_size) {
    EXPECT_EQ(CharChanger(array, size, del), expected_size);
    EXPECT_EQ(std::strcmp(array, expected), 0u);
}

TEST(CharChangerTest, SimpleExample) {
    {
        char array[] = "snake";
        const size_t size = std::size(array);
        char expected[size] = "SNAKE";
        size_t expected_size = 5;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "SSSS";
        const size_t size = std::size(array);
        char expected[size] = "S4";
        size_t expected_size = 2;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "aaaaa";
        const size_t size = std::size(array);
        char expected[size] = "A5";
        size_t expected_size = 2;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "cccccccccc";
        const size_t size = std::size(array);
        char expected[size] = "C0";
        size_t expected_size = 2;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "cccccccccccccccccccc";
        const size_t size = std::size(array);
        char expected[size] = "C0";
        size_t expected_size = 2;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "0123456789";
        const size_t size = std::size(array);
        char expected[size] = "**********";
        size_t expected_size = 10;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "ABCDEF";
        const size_t size = std::size(array);
        char expected[size] = "ABCDEF";
        size_t expected_size = 6;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "abcdef";
        const size_t size = std::size(array);
        char expected[size] = "ABCDEF";
        size_t expected_size = 6;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "     ";
        const size_t size = std::size(array);
        char expected[size] = ",";
        size_t expected_size = 1;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "   a   ";
        const size_t size = std::size(array);
        char expected[size] = ",A,";
        size_t expected_size = 3;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "     ";
        const size_t size = std::size(array);
        char expected[size] = " ";
        size_t expected_size = 1;
        CheckAnswer(array, size, ' ', expected, expected_size);
    }
    {
        char array[] = "*/){@#$^&<,";
        const size_t size = std::size(array);
        char expected[size] = "___________";
        size_t expected_size = 11;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
}

TEST(CharChangerTest, DontChangeAfterChange) {
    {
        char array[] = "aAaAaA";
        const size_t size = std::size(array);
        char expected[size] = "AAAAAA";
        size_t expected_size = 6;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "aaaAAaaAAAbA";
        const size_t size = std::size(array);
        char expected[size] = "A3A2A2A3BA";
        size_t expected_size = 10;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
}

TEST(CharChangerTest, DigitComplex) {
    {
        char array[] = "011166800000000000";
        const size_t size = std::size(array);
        char expected[size] = "**3*2**0";
        size_t expected_size = 8;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
}

TEST(CharChangerTest, DelimiterComplex) {
    {
        char array[] = "a   BC d    EFg";
        const size_t size = std::size(array);
        char expected[size] = "A,BC,D,EFG";
        size_t expected_size = 10;
        CheckAnswer(array, size, ',', expected, expected_size);
    }
    {
        char array[] = "a   BC d    EFg";
        const size_t size = std::size(array);
        char expected[size] = "AABCADAEFG";
        size_t expected_size = 10;
        CheckAnswer(array, size, 'A', expected, expected_size);
    }
    {
        char array[] = "a   BC d    EFg";
        const size_t size = std::size(array);
        char expected[size] = "A BC D EFG";
        size_t expected_size = 10;
        CheckAnswer(array, size, ' ', expected, expected_size);
    }
    {
        char array[] = "192 1 0 255";
        const size_t size = std::size(array);
        char expected[size] = "***-*-*-**2";
        size_t expected_size = 11;
        CheckAnswer(array, size, '-', expected, expected_size);
    }
}

TEST(CharChangerTest, OtherSymbolComplex) {
    char array[] = "@&& <<< ? ,,, % ___";
    const size_t size = std::size(array);
    char expected[size] = "__2,_3,_,_3,_,_3";
    size_t expected_size = 16;
    CheckAnswer(array, size, ',', expected, expected_size);
}

TEST(CharChangerTest, BasicExample) {
    char array[] = "1233-fhhhHjo _L3*&((";
    const size_t size = std::size(array);
    char expected[size] = "***2_FH3HJO,_L*___2";
    size_t expected_size = 19;
    CheckAnswer(array, size, ',', expected, expected_size);
}

TEST(CharChangerTest, ComplexExample) {
    char array[] = "   ,((   9998344   ___appleEE*98";
    const size_t size = std::size(array);
    char expected[size] = "___2_*3***2__3AP2LEE2_**";
    size_t expected_size = 24;
    CheckAnswer(array, size, '_', expected, expected_size);
}