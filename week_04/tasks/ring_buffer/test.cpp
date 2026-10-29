#include <gtest/gtest.h>

#include <vector>

#include "ring_buffer.cpp"


TEST(RingBufferTest, CtorCapacity) {
    RingBuffer buffer(5);

    EXPECT_EQ(buffer.Capacity(), 5);
    EXPECT_EQ(buffer.Size(), 0);
    EXPECT_TRUE(buffer.Empty());
    EXPECT_FALSE(buffer.Full());
}

TEST(RingBufferTest, CtorCapacityAndInitialValue) {
    RingBuffer buffer(5, 42);

    EXPECT_EQ(buffer.Capacity(), 5);
    EXPECT_EQ(buffer.Size(), 5);
    EXPECT_FALSE(buffer.Empty());
    EXPECT_TRUE(buffer.Full());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buffer[i], 42);
    }
}

TEST(RingBufferTest, CtorInitializerList) {
    RingBuffer buffer = {1, 2, 3, 4, 5};

    EXPECT_EQ(buffer.Capacity(), 5);
    EXPECT_EQ(buffer.Size(), 5);
    EXPECT_FALSE(buffer.Empty());
    EXPECT_TRUE(buffer.Full());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buffer[i], static_cast<int>(i + 1));
    }
}

TEST(RingBufferTest, ZeroCapacity) {
    {
        RingBuffer buffer(0);
        EXPECT_EQ(buffer.Capacity(), 1);
        EXPECT_EQ(buffer.Size(), 0);
        EXPECT_TRUE(buffer.Empty());
        EXPECT_FALSE(buffer.Full());
    }
    {
        RingBuffer buffer(0, 42);
        EXPECT_EQ(buffer.Capacity(), 1);
        EXPECT_EQ(buffer.Size(), 1);
        EXPECT_FALSE(buffer.Empty());
        EXPECT_TRUE(buffer.Full());
        EXPECT_EQ(buffer[0], 42);
    }
    {
        RingBuffer buffer({});
        EXPECT_EQ(buffer.Capacity(), 1);
        EXPECT_EQ(buffer.Size(), 0);
        EXPECT_TRUE(buffer.Empty());
        EXPECT_FALSE(buffer.Full());
    }
}

TEST(RingBufferTest, PushToEmptyBuffer) {
    RingBuffer buffer(3);

    buffer.Push(10);
    EXPECT_EQ(buffer.Size(), 1);
    EXPECT_EQ(buffer.Front(), 10);
    EXPECT_EQ(buffer.Back(), 10);

    buffer.Push(20);
    EXPECT_EQ(buffer.Size(), 2);
    EXPECT_EQ(buffer.Front(), 20);
    EXPECT_EQ(buffer.Back(), 10);

    buffer.Push(30);
    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_TRUE(buffer.Full());
    EXPECT_EQ(buffer.Front(), 30);
    EXPECT_EQ(buffer.Back(), 10);
}

TEST(RingBufferTest, OverflowBehavior) {
    RingBuffer buffer(3);

    buffer.Push(1);
    buffer.Push(2);
    buffer.Push(3);
    buffer.Push(4);

    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer.Front(), 4);
    EXPECT_EQ(buffer.Back(), 2);

    buffer.Push(5);
    EXPECT_EQ(buffer.Front(), 5);
    EXPECT_EQ(buffer.Back(), 3);

    buffer.Push(6);
    EXPECT_EQ(buffer.Front(), 6);
    EXPECT_EQ(buffer.Back(), 4);
}

TEST(RingBufferTest, PopFromBuffer) {
    RingBuffer buffer = {1, 2, 3};

    buffer.Pop();
    EXPECT_EQ(buffer.Size(), 2);
    EXPECT_EQ(buffer.Back(), 2);

    buffer.Pop();
    EXPECT_EQ(buffer.Size(), 1);
    EXPECT_EQ(buffer.Back(), 3);

    buffer.Pop();
    EXPECT_TRUE(buffer.Empty());
    EXPECT_EQ(buffer.Size(), 0);

    EXPECT_NO_THROW(buffer.Pop());
    EXPECT_TRUE(buffer.Empty());
}

TEST(RingBufferTest, TryPush) {
    RingBuffer buffer(2);

    EXPECT_TRUE(buffer.TryPush(1));
    EXPECT_TRUE(buffer.TryPush(2));
    EXPECT_FALSE(buffer.TryPush(3));
    EXPECT_TRUE(buffer.Full());
    EXPECT_EQ(buffer.Size(), 2);
    EXPECT_EQ(buffer.Front(), 2);
    EXPECT_EQ(buffer.Back(), 1);

    buffer.Pop();
    EXPECT_EQ(buffer.Size(), 1);
    EXPECT_TRUE(buffer.TryPush(3));
    EXPECT_EQ(buffer.Size(), 2);
    EXPECT_EQ(buffer.Front(), 3);
    EXPECT_EQ(buffer.Back(), 2);
}

TEST(RingBufferTest, TryPop) {
    RingBuffer buffer = {10, 20, 30};
    int value;

    EXPECT_TRUE(buffer.TryPop(value));
    EXPECT_EQ(value, 10);
    EXPECT_EQ(buffer.Size(), 2);

    EXPECT_TRUE(buffer.TryPop(value));
    EXPECT_EQ(value, 20);
    EXPECT_EQ(buffer.Size(), 1);

    EXPECT_TRUE(buffer.TryPop(value));
    EXPECT_EQ(value, 30);
    EXPECT_TRUE(buffer.Empty());

    EXPECT_FALSE(buffer.TryPop(value));
}

TEST(RingBufferTest, OperatorIndex) {
    RingBuffer buffer(5);

    buffer.Push(10);
    buffer.Push(20);
    buffer.Push(30);

    EXPECT_EQ(buffer[0], 10);
    EXPECT_EQ(buffer[1], 20);
    EXPECT_EQ(buffer[2], 30);

    buffer[1] = 200;
    EXPECT_EQ(buffer[1], 200);
}

TEST(RingBufferTest, ConstOperatorIndex) {
    const RingBuffer buffer = {1, 2, 3, 4, 5};

    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[4], 5);
}

TEST(RingBufferTest, FrontAndBack) {
    RingBuffer buffer(5);

    buffer.Push(1);
    EXPECT_EQ(buffer.Front(), 1);
    EXPECT_EQ(buffer.Back(), 1);

    buffer.Push(2);
    EXPECT_EQ(buffer.Front(), 2);
    EXPECT_EQ(buffer.Back(), 1);

    buffer.Push(3);
    buffer.Push(4);
    buffer.Push(5);
    EXPECT_EQ(buffer.Front(), 5);
    EXPECT_EQ(buffer.Back(), 1);

    buffer.Front() = 500;
    buffer.Back() = 100;
    EXPECT_EQ(buffer.Front(), 500);
    EXPECT_EQ(buffer.Back(), 100);
}

TEST(RingBufferTest, EmptyAndFull) {
    RingBuffer buffer(3);

    EXPECT_TRUE(buffer.Empty());
    EXPECT_FALSE(buffer.Full());

    buffer.Push(1);
    EXPECT_FALSE(buffer.Empty());
    EXPECT_FALSE(buffer.Full());

    buffer.Push(2);
    buffer.Push(3);
    EXPECT_FALSE(buffer.Empty());
    EXPECT_TRUE(buffer.Full());

    buffer.Pop();
    EXPECT_FALSE(buffer.Empty());
    EXPECT_FALSE(buffer.Full());

    buffer.Pop();
    buffer.Pop();
    EXPECT_TRUE(buffer.Empty());
    EXPECT_FALSE(buffer.Full());
}

TEST(RingBufferTest, SizeAndCapacity) {
    RingBuffer buffer(10);

    EXPECT_EQ(buffer.Capacity(), 10);
    EXPECT_EQ(buffer.Size(), 0);

    for (int i = 0; i < 7; ++i) {
        buffer.Push(i);
    }

    EXPECT_EQ(buffer.Capacity(), 10);
    EXPECT_EQ(buffer.Size(), 7);

    for (int i = 0; i < 10; ++i) {
        buffer.Push(i * 10);
    }

    EXPECT_EQ(buffer.Capacity(), 10);
    EXPECT_EQ(buffer.Size(), 10);
}

TEST(RingBufferTest, Clear) {
    RingBuffer buffer = {1, 2, 3, 4, 5};

    EXPECT_FALSE(buffer.Empty());
    buffer.Clear();

    EXPECT_TRUE(buffer.Empty());
    EXPECT_EQ(buffer.Size(), 0);
    EXPECT_EQ(buffer.Capacity(), 5);

    buffer.Push(100);
    EXPECT_EQ(buffer.Size(), 1);
    EXPECT_EQ(buffer.Front(), 100);
    EXPECT_EQ(buffer.Back(), 100);
}

TEST(RingBufferTest, ResizeIncrease) {
    RingBuffer buffer(3);
    buffer.Push(1);
    buffer.Push(2);
    buffer.Push(3);

    EXPECT_EQ(buffer.Capacity(), 3);
    EXPECT_EQ(buffer.Size(), 3);

    buffer.Resize(5);
    EXPECT_EQ(buffer.Capacity(), 5);
    EXPECT_EQ(buffer.Size(), 3);

    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);

    buffer.Push(4);
    buffer.Push(5);
    EXPECT_EQ(buffer.Size(), 5);
    EXPECT_TRUE(buffer.Full());
    EXPECT_EQ(buffer[3], 4);
    EXPECT_EQ(buffer[4], 5);
}

TEST(RingBufferTest, ResizeDecrease) {
    RingBuffer buffer(5);

    for (int i = 0; i < 5; ++i) {
        buffer.Push(i);
    }

    buffer.Resize(3);

    EXPECT_EQ(buffer.Capacity(), 3);
    EXPECT_EQ(buffer.Size(), 3);

    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);
}

TEST(RingBufferTest, ResizeDecreaseForNotFullBuffer) {
    RingBuffer buffer(5);
    buffer.Push(1);
    buffer.Push(2);

    buffer.Resize(3);

    EXPECT_EQ(buffer.Capacity(), 3);
    EXPECT_EQ(buffer.Size(), 2);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);

    buffer.Resize(5);
    buffer.Push(3);
    buffer.Push(4);
    buffer.Resize(3);

    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);
}

TEST(RingBufferTest, ResizeWithOverflow) {
    RingBuffer buffer(5);

    for (int i = 0; i < 7; ++i) {
        buffer.Push(i);
    }
    // buffer = {2, 3, 4, 5, 6}
    buffer.Resize(3);

    EXPECT_EQ(buffer.Capacity(), 3);
    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 6);
}

TEST(RingBufferTest, ResizeToSameSize) {
    RingBuffer buffer = {1, 2, 3};

    buffer.Resize(3);

    EXPECT_EQ(buffer.Capacity(), 3);
    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
}

TEST(RingBufferTest, ResizeZero) {
    RingBuffer buffer(3);
    buffer.Push(1);

    EXPECT_NO_THROW(buffer.Resize(0));
    EXPECT_EQ(buffer.Size(), 1);
    EXPECT_EQ(buffer[0], 1);
}

TEST(RingBufferTest, VectorConversion) {
    RingBuffer buffer(5);

    buffer.Push(1);
    buffer.Push(2);
    buffer.Push(3);

    std::vector<int> vec = buffer.Vector();

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);

    buffer.Push(4);
    buffer.Push(5);
    buffer.Push(6);

    vec = buffer.Vector();
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[4], 6);
}

TEST(RingBufferTest, VectorFromComplexBuffer) {
    RingBuffer buffer(4);

    buffer.Push(1);
    buffer.Push(2);
    buffer.Push(3);
    buffer.Push(4);

    buffer.Pop();
    buffer.Pop();

    buffer.Push(5);
    buffer.Push(6);

    std::vector<int> vec = buffer.Vector();

    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 5);
    EXPECT_EQ(vec[3], 6);
}

TEST(RingBufferTest, CopyConstructor) {
    RingBuffer original(5);
    original.Push(1);
    original.Push(2);
    original.Push(3);

    RingBuffer copy(original);

    EXPECT_EQ(copy.Capacity(), 5);
    EXPECT_EQ(copy.Size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);

    original.Push(4);
    EXPECT_EQ(original.Size(), 4);
    EXPECT_EQ(copy.Size(), 3);
}

TEST(RingBufferTest, CopyAssignment) {
    RingBuffer b1(5);
    b1.Push(1);
    b1.Push(2);

    RingBuffer b2(3);
    b2.Push(10);
    b2.Push(20);
    b2.Push(30);

    b2 = b1;

    EXPECT_EQ(b2.Capacity(), 5);
    EXPECT_EQ(b2.Size(), 2);
    EXPECT_EQ(b2[0], 1);
    EXPECT_EQ(b2[1], 2);

    RingBuffer& ref = b1;
    b1 = ref;
    EXPECT_EQ(b1.Size(), 2);
}

TEST(RingBufferTest, ComplexScenario) {
    RingBuffer buffer(4);

    buffer.Push(1);
    buffer.Push(2);
    buffer.Push(3);
    buffer.Push(4);

    buffer.Push(5);
    buffer.Push(6);

    buffer.Pop();
    buffer.Pop();

    buffer.Push(7);
    buffer.Push(8);
    buffer.Push(9);

    EXPECT_EQ(buffer.Size(), 4);
    EXPECT_EQ(buffer[0], 6);
    EXPECT_EQ(buffer[1], 7);
    EXPECT_EQ(buffer[2], 8);
    EXPECT_EQ(buffer[3], 9);
}

TEST(RingBufferTest, ComplexScenarioTwo) {
    RingBuffer buffer(3);

    buffer.Push(1);
    buffer.Push(2);
    buffer.Pop();
    buffer.Push(3);
    buffer.Pop();
    buffer.Push(4);
    buffer.Push(5);
    buffer.Push(6);
    buffer.Push(7);

    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 7);
}

TEST(RingBufferTest, LargeBufferOperations) {
    constexpr size_t LARGE_SIZE = 1'000'000;
    RingBuffer buffer(LARGE_SIZE);

    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        buffer.Push(static_cast<int>(i));
    }

    EXPECT_EQ(buffer.Size(), LARGE_SIZE);
    EXPECT_TRUE(buffer.Full());

    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        EXPECT_EQ(buffer[i], static_cast<int>(i));
    }

    // Быстрое очищение
    while (!buffer.Empty()) {
        buffer.Pop();
    }

    EXPECT_TRUE(buffer.Empty());
}

TEST(RingBufferTest, WrapAroundBehavior) {
    RingBuffer buffer(5);

    for (int i = 0; i < 5; ++i) {
        buffer.Push(i + 1);
    }

    buffer.Pop();
    buffer.Pop();

    buffer.Push(6);
    buffer.Push(7);

    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);
    EXPECT_EQ(buffer[3], 6);
    EXPECT_EQ(buffer[4], 7);
}