#include <gtest/gtest.h>

#include <random>

#include "stack.cpp"


TEST(StackTest, EmptyStack) {
    Stack s;

    EXPECT_TRUE(s.Empty());
    EXPECT_EQ(s.Size(), 0);
}

TEST(StackTest, PushElements) {
    Stack s;

    s.Push(1);
    EXPECT_FALSE(s.Empty());
    EXPECT_EQ(s.Size(), 1);
    EXPECT_EQ(s.Top(), 1);

    s.Push(-1);
    EXPECT_EQ(s.Size(), 2);
    EXPECT_EQ(s.Top(), -1);

    s.Push(9);
    EXPECT_EQ(s.Size(), 3);
    EXPECT_EQ(s.Top(), 9);
}

TEST(StackTest, PopElements) {
    Stack s;
    s.Push(1);
    s.Push(-1);
    s.Push(9);

    EXPECT_EQ(s.Top(), 9);
    EXPECT_TRUE(s.Pop());
    EXPECT_EQ(s.Size(), 2);
    EXPECT_EQ(s.Top(), -1);

    EXPECT_TRUE(s.Pop());
    EXPECT_EQ(s.Size(), 1);
    EXPECT_EQ(s.Top(), 1);

    EXPECT_TRUE(s.Pop());
    EXPECT_TRUE(s.Empty());
    EXPECT_EQ(s.Size(), 0);
}

TEST(StackTest, PopFromEmptyStack) {
    Stack s;
    EXPECT_TRUE(s.Empty());
    EXPECT_EQ(s.Size(), 0);

    EXPECT_FALSE(s.Pop());
    EXPECT_FALSE(s.Pop());

    EXPECT_TRUE(s.Empty());
    EXPECT_EQ(s.Size(), 0);
}

TEST(StackTest, TopElement) {
    Stack s;

    s.Push(42);
    EXPECT_EQ(s.Top(), 42);

    s.Top() = 100;
    EXPECT_EQ(s.Top(), 100);
}

TEST(StackTest, TopElementForConstStack) {
    Stack s;

    s.Push(42);
    s.Top() = 100;

    const Stack& const_ref = s;
    EXPECT_EQ(const_ref.Top(), 100);
}

TEST(StackTest, TopOnEmptyStack) {
    Stack s;
    EXPECT_NO_THROW(s.Top());

    const Stack& const_ref = s;
    EXPECT_NO_THROW(const_ref.Top());
}

TEST(StackTest, SwapStacks) {
    Stack s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack s2;
    s2.Push(4);
    s2.Push(5);

    EXPECT_EQ(s1.Size(), 3);
    EXPECT_EQ(s1.Top(), 3);
    EXPECT_EQ(s2.Size(), 2);
    EXPECT_EQ(s2.Top(), 5);

    s1.Swap(s2);
    EXPECT_EQ(s1.Size(), 2);
    EXPECT_EQ(s1.Top(), 5);
    EXPECT_EQ(s2.Size(), 3);
    EXPECT_EQ(s2.Top(), 3);

    s1.Swap(s2);
    EXPECT_EQ(s1.Size(), 3);
    EXPECT_EQ(s1.Top(), 3);
    EXPECT_EQ(s2.Size(), 2);
    EXPECT_EQ(s2.Top(), 5);
}

TEST(StackTest, SwapWithEmptyStack) {
    Stack s1;
    s1.Push(1);
    s1.Push(2);

    Stack s2;

    s1.Swap(s2);
    EXPECT_TRUE(s1.Empty());
    EXPECT_EQ(s1.Size(), 0);
    EXPECT_EQ(s2.Size(), 2);
    EXPECT_EQ(s2.Top(), 2);
}

TEST(StackTest, SwapWithSelf) {
    Stack s;
    s.Push(1);
    s.Push(2);

    EXPECT_NO_THROW(s.Swap(s));
    EXPECT_EQ(s.Size(), 2);
    EXPECT_EQ(s.Top(), 2);
}

TEST(StackTest, ClearStack) {
    Stack s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    EXPECT_EQ(s.Size(), 3);

    s.Clear();

    EXPECT_TRUE(s.Empty());
    EXPECT_EQ(s.Size(), 0);
}

TEST(StackTest, CompareStacks) {
    Stack s1;
    s1.Push(1);
    s1.Push(2);

    Stack s2;
    s2.Push(1);
    s2.Push(2);

    Stack s3;
    s3.Push(1);
    s3.Push(3);

    EXPECT_TRUE(s1 == s1);
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);

    EXPECT_FALSE(s1 != s1);
    EXPECT_FALSE(s1 != s2);
    EXPECT_TRUE(s1 != s3);
}

TEST(StackTest, CompareStacksWithDifferentSize) {
    Stack s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack s2;
    s2.Push(2);
    s2.Push(3);

    EXPECT_FALSE(s1 == s2);
    EXPECT_TRUE(s1 != s2);
}

TEST(StackTest, CompareEmptyStacks) {
    Stack s4;
    Stack s5;
    EXPECT_TRUE(s4 == s5);
    EXPECT_FALSE(s4 != s5);
}

TEST(StackTest, LifoBehavior) {
    Stack s;
    for (int i = 0; i < 5; ++i) {
        s.Push(i);
        EXPECT_EQ(s.Top(), i);
    }
    for (int i = 5; i > 0; --i) {
        EXPECT_EQ(s.Top(), i - 1);
        s.Pop();
    }
    EXPECT_TRUE(s.Empty());
}

TEST(StackTest, MultipleOperations) {
    Stack s;

    s.Push(10);
    s.Push(20);
    s.Pop();
    EXPECT_EQ(s.Top(), 10);

    s.Push(30);
    s.Push(40);
    EXPECT_EQ(s.Size(), 3);

    s.Pop();
    s.Pop();
    EXPECT_EQ(s.Top(), 10);
    EXPECT_EQ(s.Size(), 1);

    s.Pop();
    EXPECT_TRUE(s.Empty());
}

TEST(StackTest, ManyElements) {
    Stack s;
    const int COUNT = 1'000'000;

    for (int i = 0; i < COUNT; ++i) {
        s.Push(i);
        EXPECT_EQ(s.Top(), i);
        EXPECT_EQ(s.Size(), i + 1);
    }

    for (int i = COUNT - 1; i >= 0; --i) {
        EXPECT_EQ(s.Top(), i);
        s.Pop();
    }

    EXPECT_TRUE(s.Empty());
    EXPECT_EQ(s.Size(), 0);
}

TEST(StackTest, ConstMethods) {
    Stack s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    const Stack& cs = s;

    EXPECT_FALSE(cs.Empty());
    EXPECT_EQ(cs.Size(), 3);
    EXPECT_EQ(cs.Top(), 3);
    EXPECT_TRUE(cs == cs);
    EXPECT_FALSE(cs != cs);
}

TEST(StackTest, CopyCtor) {
    Stack original;
    original.Push(1);
    original.Push(2);
    original.Push(3);

    Stack copy(original);

    EXPECT_EQ(copy.Size(), 3);
    EXPECT_EQ(copy.Top(), 3);
    EXPECT_TRUE(copy == original);
}

TEST(StackTest, CopyCtorWithCopyModification) {
    Stack original;
    original.Push(1);
    original.Push(2);
    original.Push(3);

    Stack copy(original);
    copy.Pop();
    EXPECT_EQ(copy.Size(), 2);
    EXPECT_EQ(copy.Top(), 2);
    EXPECT_EQ(original.Size(), 3);
    EXPECT_EQ(original.Top(), 3);
    EXPECT_FALSE(copy == original);
}

TEST(StackTest, CopyAssignmentOperator) {
    Stack s1;
    s1.Push(10);
    s1.Push(20);
    s1.Push(30);

    Stack s2;
    s2.Push(40);
    s2.Push(50);

    s2 = s1;
    EXPECT_EQ(s2.Size(), 3);
    EXPECT_EQ(s2.Top(), 30);
    EXPECT_TRUE(s2 == s1);

    s2.Pop();
    EXPECT_EQ(s2.Size(), 2);
    EXPECT_EQ(s2.Top(), 20);
    EXPECT_EQ(s1.Size(), 3);
    EXPECT_EQ(s1.Top(), 30);
    EXPECT_FALSE(s2 == s1);
}

TEST(StackTest, CopyEmptyStack) {
    Stack empty1;
    Stack empty2(empty1);

    EXPECT_TRUE(empty2.Empty());
    EXPECT_EQ(empty2.Size(), 0);

    Stack empty3;
    empty3 = empty1;

    EXPECT_TRUE(empty3.Empty());
    EXPECT_EQ(empty3.Size(), 0);
}

TEST(StackTest, ChainAssignment) {
    Stack s1, s2, s3;

    s1.Push(1);
    s1.Push(2);

    s3 = s2 = s1;

    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s2 == s3);
    EXPECT_TRUE(s1 == s3);

    EXPECT_EQ(s1.Size(), 2);
    EXPECT_EQ(s2.Size(), 2);
    EXPECT_EQ(s3.Size(), 2);

    EXPECT_EQ(s1.Top(), 2);
    EXPECT_EQ(s2.Top(), 2);
    EXPECT_EQ(s3.Top(), 2);
}