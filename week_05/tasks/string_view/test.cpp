#include <gtest/gtest.h>

#include "string_view.cpp"

#include <string>

void ExpectEmpty(const StringView& sv) {
    EXPECT_TRUE(sv.Empty());
    EXPECT_EQ(sv.Size(), 0);
    EXPECT_EQ(sv.Length(), 0);
    EXPECT_EQ(sv.Data(), nullptr);
}

TEST(StringViewTest, DefaultConstructor) {
    StringView sv;
    EXPECT_TRUE(sv.Empty());
    EXPECT_EQ(sv.Size(), 0);
    EXPECT_EQ(sv.Length(), 0);
    EXPECT_EQ(sv.Data(), nullptr);
}

TEST(StringViewTest, CtorStdString) {
    std::string str = "Hello, World!";
    StringView sv(str);

    EXPECT_FALSE(sv.Empty());
    EXPECT_EQ(sv.Size(), str.size());
    EXPECT_EQ(sv.Length(), str.size());
    EXPECT_EQ(sv.Data(), str.data());
    EXPECT_EQ(sv.ToString(), str);
}

TEST(StringViewTest, CtorStdStringWithPos) {
    std::string str = "Hello, World!";

    StringView sv(str, 7);
    EXPECT_EQ(sv.Size(), 6);
    EXPECT_EQ(sv.ToString(), "World!");

    StringView sv2(str, 0);
    EXPECT_EQ(sv2.ToString(), str);
}

TEST(StringViewTest, CtorStdStringWithPosAndCount) {
    std::string str = "Hello, World!";

    StringView sv1(str, 0, 5);
    EXPECT_EQ(sv1.ToString(), "Hello");

    StringView sv2(str, 7, 5);
    EXPECT_EQ(sv2.ToString(), "World");

    StringView sv3(str, 7, 100);
    EXPECT_EQ(sv3.ToString(), "World!");

    StringView sv4(str, 7, StringView::npos);
    EXPECT_EQ(sv4.ToString(), "World!");
}

TEST(StringViewTest, CtorStdStringWithInvalidPos) {
    std::string str = "Hello";

    EXPECT_NO_THROW(StringView(str, 10));
    EXPECT_NO_THROW(StringView(str, 6));

    auto sv = StringView(str, 10);
    ExpectEmpty(sv);
}

TEST(StringViewTest, CtorCString) {
    const char* cstr = "Hello, World!";
    StringView sv(cstr);

    EXPECT_FALSE(sv.Empty());
    EXPECT_EQ(sv.Size(), std::strlen(cstr));
    EXPECT_EQ(sv.ToString(), cstr);
    EXPECT_EQ(sv.Data(), cstr);
}

TEST(StringViewTest, CtorCStringNullptr) {
    StringView sv(static_cast<const char*>(nullptr));
    ExpectEmpty(sv);
}

TEST(StringViewTest, CtorCStringAndLength) {
    const char* cstr = "Hello, World!";

    StringView sv1(cstr, 5);
    EXPECT_EQ(sv1.Size(), 5);
    EXPECT_EQ(sv1.ToString(), "Hello");

    StringView sv2(cstr + 7, 5);
    EXPECT_EQ(sv2.Size(), 5);
    EXPECT_EQ(sv2.ToString(), "World");
}

TEST(StringViewTest, CtorCStringAndLengthNullptr) {
    StringView sv1(nullptr, 0);
    EXPECT_TRUE(sv1.Empty());
    
    EXPECT_NO_THROW(StringView(nullptr, 5));
    auto sv = StringView(nullptr, 5);
    ExpectEmpty(sv);
}

TEST(StringViewTest, AccessMethods) {
    std::string str = "Hello";
    StringView sv(str);

    EXPECT_EQ(sv[0], 'H');
    EXPECT_EQ(sv[1], 'e');
    EXPECT_EQ(sv[4], 'o');

    EXPECT_EQ(sv.Front(), 'H');
    EXPECT_EQ(sv.Back(), 'o');
}

TEST(StringViewTest, RemovePrefix) {
    std::string str = "Hello, World!";
    StringView sv(str);

    sv.RemovePrefix(7);
    EXPECT_EQ(sv.ToString(), "World!");
    EXPECT_EQ(sv.Size(), 6);

    sv.RemovePrefix(5);
    EXPECT_EQ(sv.ToString(), "!");
    EXPECT_EQ(sv.Size(), 1);

    sv.RemovePrefix(10);
    EXPECT_TRUE(sv.Empty());
    EXPECT_EQ(sv.Size(), 0);
}

TEST(StringViewTest, RemoveSuffix) {
    std::string str = "Hello, World!";
    StringView sv(str);

    sv.RemoveSuffix(7);
    EXPECT_EQ(sv.ToString(), "Hello,");
    EXPECT_EQ(sv.Size(), 6);

    sv.RemoveSuffix(5);
    EXPECT_EQ(sv.ToString(), "H");
    EXPECT_EQ(sv.Size(), 1);

    sv.RemoveSuffix(10);
    EXPECT_TRUE(sv.Empty());
    EXPECT_EQ(sv.Size(), 0);
}

TEST(StringViewTest, Substr) {
    std::string str = "Hello, World!";
    StringView sv(str);

    StringView sub1 = sv.Substr(0, 5);
    EXPECT_EQ(sub1.ToString(), "Hello");

    StringView sub2 = sv.Substr(7, 5);
    EXPECT_EQ(sub2.ToString(), "World");

    StringView sub3 = sv.Substr(7);
    EXPECT_EQ(sub3.ToString(), "World!");

    StringView sub4 = sv.Substr(7, 100);
    EXPECT_EQ(sub4.ToString(), "World!");

    StringView sub5 = sv.Substr(13, 5);
    EXPECT_TRUE(sub5.Empty());
    EXPECT_EQ(sub5.ToString(), "");
}

TEST(StringViewTest, SubstrInvalidPos) {
    std::string str = "Hello";
    StringView sv(str);

    auto substr = sv.Substr(6);
    ExpectEmpty(substr);
}

TEST(StringViewTest, FindChar) {
    std::string str = "Hello, World!";
    StringView sv(str);

    EXPECT_EQ(sv.Find('H'), 0);
    EXPECT_EQ(sv.Find('o'), 4);
    EXPECT_EQ(sv.Find('!'), 12);
    EXPECT_EQ(sv.Find('z'), StringView::npos);

    EXPECT_EQ(sv.Find('o', 5), 8);
    EXPECT_EQ(sv.Find('l', 3), 3);

    EXPECT_EQ(sv.Find('H', 13), StringView::npos);
}

TEST(StringViewTest, FindStringView) {
    std::string str = "Hello, World! Hello again!";
    StringView sv(str);

    EXPECT_EQ(sv.Find(StringView("Hello")), 0);
    EXPECT_EQ(sv.Find(StringView("World")), 7);
    EXPECT_EQ(sv.Find(StringView("again")), 20);
    EXPECT_EQ(sv.Find(StringView("nonexistent")), StringView::npos);

    EXPECT_EQ(sv.Find(StringView("")), 0);

    EXPECT_EQ(sv.Find(StringView("Hello"), 1), 14);
    EXPECT_EQ(sv.Find(StringView("!"), 13), 25);

    EXPECT_EQ(sv.Find(StringView("Hello, World! Hello again! And more")), StringView::npos);
}

TEST(StringViewTest, FindInEmptyView) {
    StringView sv;

    EXPECT_EQ(sv.Find('a'), StringView::npos);
    EXPECT_EQ(sv.Find(StringView("test")), StringView::npos);

    StringView empty_target("");
    EXPECT_EQ(sv.Find(empty_target), 0);
}

TEST(StringViewTest, ToString) {
    std::string str = "Hello, World!";
    StringView sv1(str);
    EXPECT_EQ(sv1.ToString(), str);

    const char* cstr = "Test";
    StringView sv2(cstr);
    EXPECT_EQ(sv2.ToString(), "Test");

    StringView sv3 = sv1.Substr(7, 5);
    EXPECT_EQ(sv3.ToString(), "World");

    StringView sv4;
    EXPECT_EQ(sv4.ToString(), "");
}

TEST(StringViewTest, ObservesOriginalString) {
    std::string str = "Hello";
    StringView sv(str);

    const char* original_data = sv.Data();

    str[0] = 'J';
    str.append(", World!");

    EXPECT_EQ(sv.Data(), original_data);
    EXPECT_EQ(sv.ToString(), "Jello");
}

TEST(StringViewTest, WorksWithStringLiterals) {
    StringView sv1 = "Hello";
    EXPECT_EQ(sv1.ToString(), "Hello");

    StringView sv2("World");
    EXPECT_EQ(sv2.ToString(), "World");

    std::string result = sv1.ToString() + ", " + sv2.ToString();
    EXPECT_EQ(result, "Hello, World");
}

TEST(StringViewTest, NposConstant) {
    EXPECT_EQ(StringView::npos, static_cast<size_t>(-1));
    EXPECT_GT(StringView::npos, 1000000);  // Очень большое число
}

TEST(StringViewTest, IteratorLikeUsage) {
    std::string str = "Hello";
    StringView sv(str);

    int count_l = 0;
    for (size_t i = 0; i < sv.Size(); ++i) {
        if (sv[i] == 'l') {
            ++count_l;
        }
    }
    EXPECT_EQ(count_l, 2);

    bool found = false;
    for (size_t i = 0; i < sv.Size(); ++i) {
        if (sv[i] == 'o') {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST(StringViewTest, MemorySafety) {
    std::string str = "Hello";
    StringView sv1(str, 5);
    EXPECT_TRUE(sv1.Empty());
    EXPECT_EQ(sv1.ToString(), "");

    std::string temp("Temporary");
    StringView sv2(temp);
    EXPECT_EQ(sv2.ToString(), "Temporary");

    StringView sv3("Hello, World!");
    StringView sv4 = sv3.Substr(7);
    StringView sv5 = sv4.Substr(0, 5);
    EXPECT_EQ(sv5.ToString(), "World");

    EXPECT_EQ(sv3.Data() + 7, sv4.Data());
    EXPECT_EQ(sv4.Data(), sv5.Data());
}

TEST(StringViewTest, ComplexScenario) {
    std::string log_line = "[INFO] 2024-01-15 10:30:00 User 'admin' logged in from 192.168.1.1";
    StringView sv(log_line);

    size_t bracket_end = sv.Find(']');
    StringView level = sv.Substr(1, bracket_end - 1);
    EXPECT_EQ(level.ToString(), "INFO");

    size_t pos = bracket_end + 2;
    size_t data_end = sv.Find(' ', pos);
    StringView datetime = sv.Substr(pos, data_end - pos);
    EXPECT_EQ(datetime.ToString(), "2024-01-15");

    size_t user_start = sv.Find('\'', data_end);
    size_t user_end = sv.Find('\'', user_start + 1);
    StringView username = sv.Substr(user_start + 1, user_end - user_start - 1);
    EXPECT_EQ(username.ToString(), "admin");

    size_t ip_start = sv.Find("from") + 5;
    StringView ip = sv.Substr(ip_start);
    EXPECT_EQ(ip.ToString(), "192.168.1.1");

    ip.RemovePrefix(4);
    ip.RemoveSuffix(2);
    EXPECT_EQ(ip.ToString(), "168.1");
}

TEST(StringViewTest, PerformanceCharacteristics) {
    std::string large_string(1000000, 'A');
    StringView sv(large_string);

    EXPECT_EQ(sv.Size(), 1000000);
    EXPECT_EQ(sv.Data(), large_string.data());

    StringView substr = sv.Substr(500000, 1000);
    EXPECT_EQ(substr.Size(), 1000);
    EXPECT_EQ(substr.Data(), large_string.data() + 500000);

    std::string copy = sv.ToString();
    EXPECT_EQ(copy.size(), 1000000);
}