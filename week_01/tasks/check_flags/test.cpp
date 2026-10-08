#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "check_flags.cpp"


class PrintCheckFlagsTest : public ::testing::Test {
protected:
    void SetUp() override {
        original_cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(test_output.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(original_cout_buf);
    }

    std::string GetOutput() {
        return test_output.str();
    }

    void ClearOutput() {
        test_output.str("");
        test_output.clear();
    }

    std::stringstream test_output;
    std::streambuf* original_cout_buf;
};

CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

TEST(SignatureTest, FunctionSignature) {
    static_assert(std::is_same_v<decltype(&PrintCheckFlags), void (*)(CheckFlags)>,
        "function must have signature: void PrintCheckFlags(CheckFlags)");
}

TEST_F(PrintCheckFlagsTest, NoneFlag) {
    PrintCheckFlags(CheckFlags::NONE);
    EXPECT_EQ(GetOutput(), "[]");
}

TEST_F(PrintCheckFlagsTest, AllFlag) {
    PrintCheckFlags(CheckFlags::ALL);
    EXPECT_EQ(GetOutput(), "[TIME,DATE,USER,CERT,KEYS,DEST]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER |
        CheckFlags::CERT | CheckFlags::KEYS | CheckFlags::DEST);
    EXPECT_EQ(GetOutput(), "[TIME,DATE,USER,CERT,KEYS,DEST]");
}

TEST_F(PrintCheckFlagsTest, SingleFlags) {
    PrintCheckFlags(CheckFlags::TIME);
    EXPECT_EQ(GetOutput(), "[TIME]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::DATE);
    EXPECT_EQ(GetOutput(), "[DATE]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::USER);
    EXPECT_EQ(GetOutput(), "[USER]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::CERT);
    EXPECT_EQ(GetOutput(), "[CERT]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::KEYS);
    EXPECT_EQ(GetOutput(), "[KEYS]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::DEST);
    EXPECT_EQ(GetOutput(), "[DEST]");
}

TEST_F(PrintCheckFlagsTest, MultipleFlags) {
    PrintCheckFlags(CheckFlags::TIME | CheckFlags::DATE);
    EXPECT_EQ(GetOutput(), "[TIME,DATE]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::USER | CheckFlags::CERT | CheckFlags::KEYS);
    EXPECT_EQ(GetOutput(), "[USER,CERT,KEYS]");

    ClearOutput();
    PrintCheckFlags(CheckFlags::TIME | CheckFlags::DEST);
    EXPECT_EQ(GetOutput(), "[TIME,DEST]");
}

TEST_F(PrintCheckFlagsTest, MultipleFlagsOrder) {
    PrintCheckFlags(CheckFlags::DEST | CheckFlags::TIME | CheckFlags::USER);
    EXPECT_EQ(GetOutput(), "[TIME,USER,DEST]");
}

TEST_F(PrintCheckFlagsTest, OutOfRange) {
    PrintCheckFlags(static_cast<CheckFlags>(0xFF));
    EXPECT_EQ(GetOutput(), "");

    ClearOutput();
    PrintCheckFlags(static_cast<CheckFlags>(100));
    EXPECT_EQ(GetOutput(), "");

    ClearOutput();
    PrintCheckFlags(static_cast<CheckFlags>(1 << 6));
    EXPECT_EQ(GetOutput(), "");

    ClearOutput();
    PrintCheckFlags(static_cast<CheckFlags>(static_cast<uint8_t>(CheckFlags::ALL) + 1));
    EXPECT_EQ(GetOutput(), "");

    ClearOutput();
    PrintCheckFlags(static_cast<CheckFlags>(-1));
    EXPECT_EQ(GetOutput(), "");
}
