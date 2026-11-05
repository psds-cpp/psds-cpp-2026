#include <gtest/gtest.h>

#include "cow_string.cpp"

TEST(CowStringTest, DefaultConstructor) {
    CowString s;
    EXPECT_EQ(s.Size(), 0);
    EXPECT_STREQ(s.ToCstr(), "");
    EXPECT_TRUE(s.ToString().empty());
}

TEST(CowStringTest, ConstructorFromCString) {
    CowString s("Hello");
    EXPECT_EQ(s.Size(), 5);
    EXPECT_STREQ(s.ToCstr(), "Hello");
    EXPECT_EQ(s.ToString(), "Hello");
}

TEST(CowStringTest, ConstructorFromStdString) {
    std::string str = "World";
    CowString s(str);
    EXPECT_EQ(s.Size(), 5);
    EXPECT_STREQ(s.ToCstr(), "World");
    EXPECT_EQ(s.ToString(), "World");
}

TEST(CowStringTest, ConstructorFromEmptyCString) {
    CowString s("");
    EXPECT_EQ(s.Size(), 0);
    EXPECT_STREQ(s.ToCstr(), "");
    EXPECT_TRUE(s.ToString().empty());
}

TEST(CowStringTest, CopyConstructorCOWSemantics) {
    CowString s1("Hello");
    CowString s2 = s1;

    EXPECT_EQ(s1.ToCstr(), s2.ToCstr());

    EXPECT_STREQ(s1.ToCstr(), "Hello");
    EXPECT_STREQ(s2.ToCstr(), "Hello");
}

TEST(CowStringTest, MoveConstructor) {
    CowString s1("Hello");
    const char* original_ptr = s1.ToCstr();

    CowString s2 = std::move(s1);

    EXPECT_EQ(s2.ToCstr(), original_ptr);
    EXPECT_STREQ(s2.ToCstr(), "Hello");

    EXPECT_EQ(s1.Size(), 0);
    EXPECT_STREQ(s1.ToCstr(), "");
}

TEST(CowStringTest, CopyAssignmentCOWSemantics) {
    CowString s1("Hello");
    CowString s2;

    s2 = s1;

    EXPECT_EQ(s1.ToCstr(), s2.ToCstr());

    EXPECT_STREQ(s1.ToCstr(), "Hello");
    EXPECT_STREQ(s2.ToCstr(), "Hello");
}

TEST(CowStringTest, CopyAssignment_SelfAssignment) {
    CowString s("Hello");
    const char* original_ptr = s.ToCstr();

    s = s;

    EXPECT_EQ(s.ToCstr(), original_ptr);
    EXPECT_STREQ(s.ToCstr(), "Hello");
}

TEST(CowStringTest, MoveAssignment) {
    CowString s1("Hello");
    CowString s2;

    const char* original_ptr = s1.ToCstr();

    s2 = std::move(s1);

    EXPECT_EQ(s2.ToCstr(), original_ptr);
    EXPECT_STREQ(s2.ToCstr(), "Hello");

    EXPECT_EQ(s1.Size(), 0);
    EXPECT_STREQ(s1.ToCstr(), "");
}

TEST(CowStringTest, ReadOperationsNoCopy) {
    CowString s1("Hello World");
    CowString s2 = s1;

    const char* original_ptr = s1.ToCstr();

    size_t size1 = s1.Size();
    size_t size2 = s2.Size();

    const char* cstr1 = s1.ToCstr();
    const char* cstr2 = s2.ToCstr();

    std::string str1 = s1.ToString();
    std::string str2 = s2.ToString();

    const CowString& s1_cref = s1;
    const CowString& s2_cref = s2;
    char ch1 = s1_cref[0];
    char ch2 = s2_cref[0];

    EXPECT_EQ(s1.ToCstr(), original_ptr);
    EXPECT_EQ(s1.ToCstr(), s2.ToCstr());

    EXPECT_EQ(size1, 11);
    EXPECT_EQ(size2, 11);
    EXPECT_STREQ(cstr1, "Hello World");
    EXPECT_STREQ(cstr2, "Hello World");
    EXPECT_EQ(str1, "Hello World");
    EXPECT_EQ(str2, "Hello World");
    EXPECT_EQ(ch1, 'H');
    EXPECT_EQ(ch2, 'H');
}

TEST(CowStringTest, WriteOperationCausesCopy) {
    CowString s1("Hello");
    CowString s2 = s1;

    const char* ptr1_before = s1.ToCstr();
    const char* ptr2_before = s2.ToCstr();

    EXPECT_EQ(ptr1_before, ptr2_before);

    s2[0] = 'J';

    const char* ptr1_after = s1.ToCstr();
    const char* ptr2_after = s2.ToCstr();

    EXPECT_NE(ptr1_after, ptr2_after);
    EXPECT_EQ(ptr1_before, ptr1_after);

    EXPECT_STREQ(s1.ToCstr(), "Hello");
    EXPECT_STREQ(s2.ToCstr(), "Jello");
}

TEST(CowStringTest, WriteOperationMultipleCopies) {
    CowString original("Hello");
    CowString copy1 = original;
    CowString copy2 = original;
    CowString copy3 = original;

    EXPECT_EQ(original.ToCstr(), copy1.ToCstr());
    EXPECT_EQ(original.ToCstr(), copy2.ToCstr());
    EXPECT_EQ(original.ToCstr(), copy3.ToCstr());

    copy2[1] = 'a';

    EXPECT_NE(original.ToCstr(), copy2.ToCstr());
    EXPECT_EQ(original.ToCstr(), copy1.ToCstr());
    EXPECT_EQ(original.ToCstr(), copy3.ToCstr());

    EXPECT_STREQ(original.ToCstr(), "Hello");
    EXPECT_STREQ(copy1.ToCstr(), "Hello");
    EXPECT_STREQ(copy2.ToCstr(), "Hallo");
    EXPECT_STREQ(copy3.ToCstr(), "Hello");
}

TEST(CowStringTest, AppendFromCStringCausesCopy) {
    CowString s1("Hello");
    CowString s2 = s1;

    const char* ptr1_before = s1.ToCstr();
    const char* ptr2_before = s2.ToCstr();
    EXPECT_EQ(ptr1_before, ptr2_before);

    s1.Append(" World");

    const char* ptr1_after = s1.ToCstr();
    const char* ptr2_after = s2.ToCstr();

    EXPECT_NE(ptr1_after, ptr2_after);
    EXPECT_EQ(ptr2_before, ptr2_after);

    EXPECT_STREQ(s1.ToCstr(), "Hello World");
    EXPECT_STREQ(s2.ToCstr(), "Hello");
}

TEST(CowStringTest, AppendFromStdString) {
    CowString s("Hello");
    std::string world = " World";

    s.Append(world);

    EXPECT_STREQ(s.ToCstr(), "Hello World");
    EXPECT_EQ(s.Size(), 11);
}

TEST(CowStringTest, AppendToEmptyString) {
    CowString s;
    s.Append("Hello");

    EXPECT_STREQ(s.ToCstr(), "Hello");
    EXPECT_EQ(s.Size(), 5);
}

TEST(CowStringTest, AppendMultipleTimes) {
    CowString s("Hello");

    s.Append(", ");
    s.Append("World");
    s.Append("!");

    EXPECT_STREQ(s.ToCstr(), "Hello, World!");
    EXPECT_EQ(s.Size(), 13);
}

TEST(CowStringTest, AppendChainedMultipleTimes) {
    CowString s("Hello");

    s.Append(", ").Append("World").Append("!");

    EXPECT_STREQ(s.ToCstr(), "Hello, World!");
    EXPECT_EQ(s.Size(), 13);
}

TEST(CowStringTest, AppendEmptyStringNoCopy) {
    CowString s1("Hello");
    CowString s2 = s1;

    const char* original_ptr = s1.ToCstr();

    s1.Append("");

    EXPECT_EQ(s1.ToCstr(), s2.ToCstr());
    EXPECT_EQ(s1.ToCstr(), original_ptr);

    EXPECT_STREQ(s1.ToCstr(), "Hello");
}

TEST(CowStringTest, SubstrDoesNotModifyOriginal) {
    CowString s("Hello World");
    CowString copy = s;

    CowString sub = s.Substr(0, 5);

    EXPECT_EQ(s.ToCstr(), copy.ToCstr());
    EXPECT_NE(s.ToCstr(), sub.ToCstr());

    EXPECT_STREQ(s.ToCstr(), "Hello World");
    EXPECT_STREQ(sub.ToCstr(), "Hello");
}

TEST(CowStringTest, SubstrDefaultParameters) {
    CowString s("Hello World");

    CowString sub1 = s.Substr();
    EXPECT_STREQ(sub1.ToCstr(), "Hello World");

    CowString sub2 = s.Substr(6);
    EXPECT_STREQ(sub2.ToCstr(), "World");

    CowString sub3 = s.Substr(0, 5);
    EXPECT_STREQ(sub3.ToCstr(), "Hello");

    CowString sub4 = s.Substr(0, CowString::npos);
    EXPECT_STREQ(sub4.ToCstr(), "Hello World");
}

TEST(CowStringTest, Substr_FullString) {
    CowString s("Hello World");

    CowString sub = s.Substr(0, s.Size());

    EXPECT_STREQ(sub.ToCstr(), "Hello World");
    EXPECT_EQ(sub.Size(), 11);
}

TEST(CowStringTest, Substr_Partial) {
    CowString s("Hello World");

    CowString sub = s.Substr(6, 5);

    EXPECT_STREQ(sub.ToCstr(), "World");
    EXPECT_EQ(sub.Size(), 5);
}

TEST(CowStringTest, SubstrCountGreaterThanAvailable) {
    CowString s("Hello");

    CowString sub = s.Substr(2, 10);

    EXPECT_STREQ(sub.ToCstr(), "llo");
    EXPECT_EQ(sub.Size(), 3);
}

TEST(CowStringTest, SubstrFromEmptyString) {
    CowString se;
    se.Clear();

    CowString sub1 = se.Substr(0, CowString::npos);
    EXPECT_STREQ(sub1.ToCstr(), "");
    EXPECT_EQ(sub1.Size(), 0);

    CowString sub2 = se.Substr(0, 5);
    EXPECT_STREQ(sub2.ToCstr(), "");
    EXPECT_EQ(sub2.Size(), 0);
}

TEST(CowStringTest, SubstrInvalidPos) {
    CowString s("Hello");

    auto sub1 = s.Substr(10);
    EXPECT_STREQ(sub1.ToCstr(), "");
    EXPECT_EQ(sub1.Size(), 0);

    auto sub2 = s.Substr(6, CowString::npos);
    EXPECT_STREQ(sub2.ToCstr(), "");
    EXPECT_EQ(sub2.Size(), 0);
}

TEST(CowStringTest, ClearCreatesCopy) {
    CowString s1("Hello");
    CowString s2 = s1;

    const char* ptr2_before = s2.ToCstr();
    EXPECT_EQ(s1.ToCstr(), s2.ToCstr());

    s1.Clear();
    EXPECT_NE(s1.ToCstr(), s2.ToCstr());
    EXPECT_EQ(s2.ToCstr(), ptr2_before);

    EXPECT_STREQ(s1.ToCstr(), "");
    EXPECT_EQ(s1.Size(), 0);
    EXPECT_STREQ(s2.ToCstr(), "Hello");
    EXPECT_EQ(s2.Size(), 5);
}

TEST(CowStringTest, ClearEmptyString) {
    CowString s;
    CowString copy = s;

    s.Clear();

    EXPECT_STREQ(s.ToCstr(), "");
    EXPECT_EQ(s.Size(), 0);
    EXPECT_STREQ(copy.ToCstr(), "");
    EXPECT_EQ(copy.Size(), 0);
}

TEST(CowStringTest, OperatorConstCharStar) {
    CowString s("Hello");

    const char* cstr = s;

    EXPECT_STREQ(cstr, "Hello");
}

TEST(CowStringTest, IndexOperatorRead) {
    CowString s("Hello");

    const CowString& s_cref = s;
    EXPECT_EQ(s_cref[0], 'H');
    EXPECT_EQ(s_cref[1], 'e');
    EXPECT_EQ(s_cref[4], 'o');
}

TEST(CowStringTest, IndexOperatorWriteCausesCopy) {
    CowString s1("Hello");
    CowString s2 = s1;

    const char* ptr1_before = s1.ToCstr();
    const char* ptr2_before = s2.ToCstr();
    EXPECT_EQ(ptr1_before, ptr2_before);

    s1[0] = 'J';

    EXPECT_NE(s1.ToCstr(), s2.ToCstr());
    EXPECT_EQ(s2.ToCstr(), ptr2_before);

    EXPECT_STREQ(s1.ToCstr(), "Jello");
    EXPECT_STREQ(s2.ToCstr(), "Hello");
}

TEST(CowStringTest, ImplicitConversionInComparisons) {
    CowString s("Hello");

    EXPECT_STREQ(s, "Hello");
    EXPECT_STRNE(s, "World");
}

TEST(CowStringTest, MultipleOperations) {
    CowString s1("Hello");
    CowString s2 = s1;
    CowString s3 = s2;

    EXPECT_EQ(s1.ToCstr(), s2.ToCstr());
    EXPECT_EQ(s2.ToCstr(), s3.ToCstr());

    s2.Append(" World");

    EXPECT_EQ(s1.ToCstr(), s3.ToCstr());
    EXPECT_NE(s1.ToCstr(), s2.ToCstr());

    s1[0] = 'J';

    EXPECT_NE(s1.ToCstr(), s2.ToCstr());
    EXPECT_NE(s1.ToCstr(), s3.ToCstr());
    EXPECT_NE(s2.ToCstr(), s3.ToCstr());

    EXPECT_STREQ(s1.ToCstr(), "Jello");
    EXPECT_STREQ(s2.ToCstr(), "Hello World");
    EXPECT_STREQ(s3.ToCstr(), "Hello");
}

TEST(CowStringTest, MemoryManagementDestructor) {
    CowString* s1 = new CowString("Hello");
    CowString* s2 = new CowString(*s1);

    const char* s1_ptr = s1->ToCstr();
    const char* s2_ptr = s2->ToCstr();

    EXPECT_EQ(s1_ptr, s2_ptr);

    delete s1;

    EXPECT_STREQ(s2->ToCstr(), "Hello");

    delete s2;
}

TEST(CowStringTest, AssignmentChain) {
    CowString a("A");
    CowString b("B");
    CowString c("C");

    a = b = c;

    EXPECT_EQ(a.ToCstr(), b.ToCstr());
    EXPECT_EQ(b.ToCstr(), c.ToCstr());
    EXPECT_EQ(a.ToCstr(), c.ToCstr());

    EXPECT_STREQ(a.ToCstr(), "C");
    EXPECT_STREQ(b.ToCstr(), "C");
    EXPECT_STREQ(c.ToCstr(), "C");
}

TEST(CowStringTest, LargeStringCOWBenefits) {

    std::string large(10000, 'A');
    CowString s1(large);

    std::vector<CowString> copies(10);
    for (auto& copy : copies) {
        copy = s1;
    }

    for (const auto& copy : copies) {
        EXPECT_EQ(s1.ToCstr(), copy.ToCstr());
    }

    copies[5][0] = 'B';

    EXPECT_NE(s1.ToCstr(), copies[5].ToCstr());

    for (size_t i = 0; i < copies.size(); ++i) {
        if (i != 5) {
            EXPECT_EQ(s1.ToCstr(), copies[i].ToCstr());
        }
    }

    EXPECT_EQ(s1.ToCstr()[0], 'A');
    EXPECT_EQ(copies[5].ToCstr()[0], 'B');

    for (size_t i = 1; i < 100; ++i) {
        EXPECT_EQ(s1.ToCstr()[i], 'A');
        EXPECT_EQ(copies[5].ToCstr()[i], 'A');
    }
}

TEST(CowStringTest, EmptyStringsShareData) {
    CowString s1;
    CowString s2;

    EXPECT_STREQ(s1.ToCstr(), "");
    EXPECT_EQ(s1.Size(), 0);
    EXPECT_STREQ(s2.ToCstr(), "");
    EXPECT_EQ(s2.Size(), 0);

    CowString s3 = s1;
    EXPECT_STREQ(s3.ToCstr(), "");
    EXPECT_EQ(s3.Size(), 0);
}

TEST(CowStringTest, FindMethod) {
    CowString s("Hello World");

    EXPECT_EQ(s.Find("World"), 6);
    EXPECT_EQ(s.Find("Hello"), 0);
    EXPECT_EQ(s.Find("Universe"), CowString::npos);
    EXPECT_EQ(s.Find('o'), 4);
    EXPECT_EQ(s.Find('x'), CowString::npos);
    EXPECT_EQ(s.Find(""), 0);
}

TEST(CowStringTest, EmptyMethod) {
    CowString s1("Hello");
    EXPECT_FALSE(s1.Empty());

    CowString s2;
    EXPECT_TRUE(s2.Empty());

    CowString s3("");
    EXPECT_TRUE(s3.Empty());

    s1.Clear();
    EXPECT_TRUE(s1.Empty());
}
