#include <gtest/gtest.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "quadratic.cpp"


TEST(SignatureTest, FunctionSignature) {
    static_assert(std::is_same_v<decltype(&SolveQuadratic), void (*)(int, int, int)>,
        "function must have signature: void SolveQuadratic(int, int, int)");
}

std::string CaptureOutput(int a, int b, int c) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    SolveQuadratic(a, b, c);

    std::cout.rdbuf(old);
    return buffer.str();
}

TEST(SolveQuadraticTest, TwoRealRoots) {
    auto output = CaptureOutput(1, -3, 2);
    EXPECT_EQ(output, "1 2");

    output = CaptureOutput(2, -5, -3);
    EXPECT_EQ(output, "-0.5 3");
}

TEST(SolveQuadraticTest, OneRealRoot) {
    auto output = CaptureOutput(1, -2, 1);
    EXPECT_EQ(output, "1");

    output = CaptureOutput(4, 4, 1);
    EXPECT_EQ(output, "-0.5");

    output = CaptureOutput(9, -12, 4);
    EXPECT_EQ(output, std::to_string(2. / 3));
}

TEST(SolveQuadraticTest, NoRealRoots) {
    auto output = CaptureOutput(1, 1, 1);
    EXPECT_EQ(output, "no solutions");

    output = CaptureOutput(2, 0, 5);
    EXPECT_EQ(output, "no solutions");

    output = CaptureOutput(0, 0, 7);
    EXPECT_EQ(output, "no solutions");

    output = CaptureOutput(2, 0, 6);
    EXPECT_EQ(output, "no solutions");

    output = CaptureOutput(8, -8, 14);
    EXPECT_EQ(output, "no solutions");
}

TEST(SolveQuadraticTest, LinearEquation) {
    auto output = CaptureOutput(0, 2, -4);
    EXPECT_EQ(output, "2");

    output = CaptureOutput(0, -3, 6);
    EXPECT_EQ(output, "2");

    output = CaptureOutput(0, 3, 4);
    EXPECT_EQ(output, "-1.33333");
}

TEST(SolveQuadraticTest, SpecialCases) {
    auto output = CaptureOutput(0, 0, 0);
    EXPECT_EQ(output, "infinite solutions");

    output = CaptureOutput(0, 0, 5);
    EXPECT_EQ(output, "no solutions");
}

TEST(SolveQuadraticTest, ZeroRoots) {
    auto output = CaptureOutput(1, 0, 0);
    EXPECT_EQ(output, "0");

    output = CaptureOutput(2, 0, 0);
    EXPECT_EQ(output, "0");
}

TEST(SolveQuadraticTest, ComplexCases) {
    auto output = CaptureOutput(1, 0, -2);
    double root1 = -std::sqrt(2);
    double root2 = std::sqrt(2);

    std::stringstream expected;
    expected << root1 << " " << root2;
    EXPECT_EQ(output, expected.str());
}

TEST(SolveQuadraticTest, NegativeZeroHandling) {
    auto output = CaptureOutput(1, 0, -1);
    EXPECT_EQ(output, "-1 1");

    output = CaptureOutput(1, 1, 0);
    EXPECT_EQ(output, "-1 0");
}

TEST(SolveQuadraticTest, LargeNumbers) {
    auto output = CaptureOutput(1'000'000, 2'000'000, 1'000'000);
    EXPECT_EQ(output, "-1");
}