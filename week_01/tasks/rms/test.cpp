#include <gtest/gtest.h>

#include <cmath>
#include <numbers>
#include <type_traits>

#include "rms.cpp"

namespace {
    constexpr double EPSILON = 1e-6;
} // namespace

TEST(RMSTest, FunctionSignature) {
    static_assert(std::is_same_v<decltype(&CalculateRMS), double (*)(double*, size_t)>,
        "function must have signature: double CalculateRMS(double[], size_t)");
}

TEST(RMSTest, EmptyArray) {
    double data[] = {};
    EXPECT_DOUBLE_EQ(CalculateRMS(data, 0), 0.0);
}

TEST(RMSTest, SingleElement) {
    double data[] = {18.0};
    EXPECT_DOUBLE_EQ(CalculateRMS(data, 1), 18.0);
}

TEST(RMSTest, NegativeValues) {
    double data[] = {-1.0, 0.0, -2.0, -3.0};
    double expected = 1.870828693;
    EXPECT_NEAR(CalculateRMS(data, 4), expected, EPSILON);
}

TEST(RMSTest, MixedValues) {
    double data[] = {-3.0, -2.0, 2.0, 3.0};
    double expected = 2.549509757;
    EXPECT_NEAR(CalculateRMS(data, 4), expected, EPSILON);
}

TEST(RMSTest, SinWave) {
    using std::numbers::pi;
    const size_t size = 100;
    double data[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = 10 * std::sqrt(2) * sin(2 * pi * 50 * (i * 0.0002) + 30.0 / 360);
    }
    double expected = 10;
    EXPECT_NEAR(CalculateRMS(data, size), expected, EPSILON);
}

TEST(RMSTest, HarmonicSinWave) {
    using std::numbers::pi;
    const size_t size = 100;
    double data[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = 10 * std::sqrt(2) * sin(2 * pi * 50 * (i * 0.0002) + 30.0 / 360);
        data[i] += 3 * std::sqrt(2) * sin(2 * pi * 250 * (i * 0.0002) + 90.0 / 360);
        data[i] += 1 * std::sqrt(2) * sin(2 * pi * 350 * (i * 0.0002) - 45.0 / 360);
    }
    double expected = 10.488088482;
    EXPECT_NEAR(CalculateRMS(data, size), expected, EPSILON);
}

TEST(RMSTest, NullptrArrayTest) {
    EXPECT_DOUBLE_EQ(CalculateRMS(nullptr, 1), 0.0);
}

