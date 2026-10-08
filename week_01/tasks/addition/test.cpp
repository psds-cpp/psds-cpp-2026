#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <stdexcept>

#include "addition.cpp"

TEST(AdditionTest, FunctionSignature) {
    static_assert(std::is_same_v<decltype(&Addition), int64_t (*)(int, int)>,
        "function must have signature: int64_t Sum(int, int)");
}

TEST(AdditionTest, Simple) {
    EXPECT_EQ(Addition(2, 3), 5);
    EXPECT_EQ(Addition(0, 0), 0);
}

TEST(AdditionTest, PositiveAndNegative) {
    EXPECT_EQ(Addition(10, -3), 7);
    EXPECT_EQ(Addition(-5, 8), 3);
    EXPECT_EQ(Addition(-10, -5), -15);
    EXPECT_EQ(Addition(100, -100), 0);
    EXPECT_EQ(Addition(147'483'647, -2'147'483'647), -2'000'000'000);
}

TEST(AdditionTest, TryOverflow) {
    EXPECT_EQ(Addition(2'000'000'000, 1'000'000'000), 3'000'000'000);
    EXPECT_EQ(Addition(-2'120'056'018, -2'140'844'102), -4'260'900'120);
}

// // Main function is not need, because -lgtest_main is used
// int main(int argc, char** argv) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }