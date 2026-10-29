#include <gtest/gtest.h>

#include <vector>
#include <stack>

#include "queue.cpp"


TEST(QueueTest, DefaultCtor) {
    Queue q;
    EXPECT_TRUE(q.Empty());
    EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, VectorCtor) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Queue q(vec);

    EXPECT_EQ(q.Size(), 5);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(q.Front(), vec[i]);
        EXPECT_TRUE(q.Pop());
    }
    EXPECT_TRUE(q.Empty());
    EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, StackCtor) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::stack<int> s;
    for (size_t i = 0; i < vec.size(); ++i) {
        s.push(vec[i]);
    }
    Queue q(s);

    EXPECT_EQ(q.Size(), 5);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(q.Front(), vec[i]);
        EXPECT_TRUE(q.Pop());
    }
    EXPECT_TRUE(q.Empty());
    EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, InitializerListCtor) {
    Queue q = {10, 20, 30, 40, 50};

    EXPECT_EQ(q.Size(), 5);
    EXPECT_EQ(q.Front(), 10);
    EXPECT_EQ(q.Back(), 50);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(q.Front(), (i + 1) * 10);
        EXPECT_TRUE(q.Pop());
    }
    EXPECT_TRUE(q.Empty());
    EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, PushAndSize) {
    Queue q;

    q.Push(10);
    EXPECT_EQ(q.Size(), 1);
    EXPECT_FALSE(q.Empty());

    q.Push(20);
    EXPECT_EQ(q.Size(), 2);

    q.Push(30);
    EXPECT_EQ(q.Size(), 3);
}

TEST(QueueTest, Pop) {
    Queue q = {1, 2, 3, 4, 5};

    EXPECT_TRUE(q.Pop());
    EXPECT_EQ(q.Size(), 4);
    EXPECT_EQ(q.Front(), 2);

    EXPECT_TRUE(q.Pop());
    EXPECT_EQ(q.Size(), 3);
    EXPECT_EQ(q.Front(), 3);

    while (!q.Empty()) {
        EXPECT_TRUE(q.Pop());
    }
    EXPECT_FALSE(q.Pop());

    EXPECT_TRUE(q.Empty());
    EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, Front) {
    Queue q = {10, 20, 30};

    EXPECT_EQ(q.Front(), 10);
    q.Front() = 100;
    EXPECT_EQ(q.Front(), 100);
    q.Pop();

    EXPECT_EQ(q.Front(), 20);
    q.Front() = 200;
    EXPECT_EQ(q.Front(), 200);
    q.Pop();

    EXPECT_EQ(q.Front(), 30);
    q.Front() = 300;
    EXPECT_EQ(q.Front(), 300);
}

TEST(QueueTest, Back) {
    Queue q = {10, 20, 30};

    EXPECT_EQ(q.Back(), 30);
    q.Back() = 300;
    EXPECT_EQ(q.Back(), 300);

    q.Push(40);
    EXPECT_EQ(q.Back(), 40);
    q.Back() = 400;
    EXPECT_EQ(q.Back(), 400);

    q.Pop();
    EXPECT_EQ(q.Back(), 400);
}

TEST(QueueTest, FrontBack) {
    Queue q;

    q.Push(1);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 1);

    q.Push(2);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 2);

    q.Push(3);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 3);

    q.Pop();
    EXPECT_EQ(q.Front(), 2);
    EXPECT_EQ(q.Back(), 3);

    q.Pop();
    EXPECT_EQ(q.Front(), 3);
    EXPECT_EQ(q.Back(), 3);
}

TEST(QueueTest, FrontOnEmptyQueue) {
    Queue q;
    EXPECT_NO_THROW(q.Front());

    const Queue& cq = q;
    EXPECT_NO_THROW(cq.Front());
}

TEST(QueueTest, BackOnEmptyQueue) {
    Queue q;
    EXPECT_NO_THROW(q.Back());

    const Queue& cq = q;
    EXPECT_NO_THROW(cq.Back());
}

TEST(QueueTest, Clear) {
    Queue q = {1, 2, 3, 4, 5};

    EXPECT_EQ(q.Size(), 5);
    EXPECT_FALSE(q.Empty());

    q.Clear();
    EXPECT_EQ(q.Size(), 0);
    EXPECT_TRUE(q.Empty());

    q.Push(100);
    EXPECT_EQ(q.Size(), 1);
    EXPECT_FALSE(q.Empty());
    EXPECT_EQ(q.Front(), 100);
    EXPECT_EQ(q.Back(), 100);
}

TEST(QueueTest, Swap) {
    Queue q1 = {1, 2, 3};
    Queue q2 = {4, 5, 6, 7};

    q1.Swap(q2);

    EXPECT_EQ(q1.Size(), 4);
    EXPECT_EQ(q1.Front(), 4);
    EXPECT_EQ(q1.Back(), 7);

    EXPECT_EQ(q2.Size(), 3);
    EXPECT_EQ(q2.Front(), 1);
    EXPECT_EQ(q2.Back(), 3);

    q1.Swap(q1);
    EXPECT_EQ(q1.Size(), 4);
    EXPECT_EQ(q1.Front(), 4);
    EXPECT_EQ(q1.Back(), 7);
}

TEST(QueueTest, Equality) {
    Queue q1 = {1, 2, 3, 4, 5};
    Queue q2 = {1, 2, 3, 4, 5};
    Queue q3 = {1, 2, 3, 4};
    Queue q4 = {5, 4, 3, 2, 1};
    Queue q5 = {2, 3, 4, 5};

    EXPECT_TRUE(q1 == q1);
    EXPECT_FALSE(q1 != q1);
    EXPECT_TRUE(q1 == q2);
    EXPECT_FALSE(q1 != q2);

    EXPECT_FALSE(q1 == q3);
    EXPECT_TRUE(q1 != q3);

    EXPECT_FALSE(q1 == q4);
    EXPECT_TRUE(q1 != q4);

    EXPECT_FALSE(q1 == q5);
    EXPECT_TRUE(q1 != q5);
    q1.Pop();
    EXPECT_TRUE(q1 == q5);
    EXPECT_FALSE(q1 != q5);
}

TEST(QueueTest, EqualityAfterOperations) {
    Queue q1;
    Queue q2;

    q1.Push(1); q1.Push(2); q1.Push(3); q1.Pop(); q1.Push(4);
    q2.Push(2); q2.Push(3); q2.Push(4);

    EXPECT_TRUE(q1 == q2);
}

TEST(QueueTest, EqualityAfterManyOperations) {
    Queue q3;
    Queue q4;

    for (int i = 0; i < 1000; ++i) {
        q3.Push(i);
        q4.Push(i);
    }

    for (int i = 0; i < 500; ++i) {
        q3.Pop();
        q4.Pop();
    }
    EXPECT_TRUE(q3 == q4);
}

TEST(QueueTest, SizeAfterManyOperations) {
    Queue q;
    const int N = 100'000;

    for (int i = 0; i < N; ++i) {
        q.Push(i);
        q.Push(i + 1);
        q.Pop();
    }

    EXPECT_EQ(q.Size(), N);
}

TEST(QueueTest, FifoOrder) {
    Queue q;
    const int N = 100'000;

    for (int i = 0; i < N; ++i) {
        q.Push(i);
    }

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.Front(), i);
        q.Pop();
    }

    EXPECT_TRUE(q.Empty());
}

TEST(QueueTest, MixedOperations) {
    Queue q;

    q.Push(1);
    q.Push(2);
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 2);

    q.Push(3);
    q.Pop();
    EXPECT_EQ(q.Front(), 2);
    EXPECT_EQ(q.Back(), 3);

    q.Push(4);
    q.Push(5);
    q.Pop();
    EXPECT_EQ(q.Front(), 3);
    EXPECT_EQ(q.Back(), 5);

    q.Pop();
    q.Pop();
    EXPECT_EQ(q.Front(), 5);
    EXPECT_EQ(q.Back(), 5);

    q.Pop();
    EXPECT_TRUE(q.Empty());
}

TEST(QueueTest, ConstQueue) {
    const Queue q = {1, 2, 3, 4, 5};
    EXPECT_EQ(q.Size(), 5);
    EXPECT_FALSE(q.Empty());
    EXPECT_EQ(q.Front(), 1);
    EXPECT_EQ(q.Back(), 5);

    const Queue q2 = {1, 2, 3, 4, 5};
    EXPECT_TRUE(q == q2);
    EXPECT_FALSE(q != q2);
}

TEST(QueueTest, ConstRefQueue) {
    Queue q = {1, 2, 3, 4, 5};
    const Queue& q_ref = q;
    EXPECT_EQ(q_ref.Size(), 5);
    EXPECT_FALSE(q_ref.Empty());
    EXPECT_EQ(q_ref.Front(), 1);
    EXPECT_EQ(q_ref.Back(), 5);
    EXPECT_TRUE(q_ref == q_ref);
    EXPECT_FALSE(q_ref != q_ref);

    q.Pop();
    EXPECT_EQ(q_ref.Size(), 4);
    EXPECT_FALSE(q_ref.Empty());
    EXPECT_EQ(q_ref.Front(), 2);
    EXPECT_EQ(q_ref.Back(), 5);
}

TEST(QueueTest, SingleElement) {
    Queue q;

    q.Push(42);
    EXPECT_EQ(q.Size(), 1);
    EXPECT_EQ(q.Front(), 42);
    EXPECT_EQ(q.Back(), 42);
    EXPECT_FALSE(q.Empty());

    q.Pop();
    EXPECT_TRUE(q.Empty());
    EXPECT_EQ(q.Size(), 0);
}

class QueuePerformanceTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    template<typename Func>
    static long long MeasureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
};

TEST_F(QueuePerformanceTest, CapacityConstructor) {
    constexpr int LARGE_SIZE = 10'000'000;
    Queue q_with_reserve(LARGE_SIZE);

    long long time_with_reserve = MeasureTime([&q_with_reserve]() {
        for (int i = 0; i < LARGE_SIZE; ++i) {
            q_with_reserve.Push(i);
        }
    });

    std::cout << "\nВремя заполнения очереди с резервированием ("
              << LARGE_SIZE << " элементов): "
              << time_with_reserve << " ms" << std::endl;

    Queue q_without_reserve;
    long long time_without_reserve = MeasureTime([&q_without_reserve]() {
        for (int i = 0; i < LARGE_SIZE; ++i) {
            q_without_reserve.Push(i);
        }
    });

    std::cout << "Время заполнения очереди без резервирования ("
              << LARGE_SIZE << " элементов): "
              << time_without_reserve << " ms" << std::endl;

    EXPECT_EQ(q_with_reserve.Size(), LARGE_SIZE);
    EXPECT_EQ(q_without_reserve.Size(), LARGE_SIZE);

    for (int i = 0; i < LARGE_SIZE; ++i) {
        EXPECT_EQ(q_with_reserve.Front(), i);
        EXPECT_TRUE(q_with_reserve.Pop());
        EXPECT_EQ(q_without_reserve.Front(), i);
        EXPECT_TRUE(q_without_reserve.Pop());
    }
    EXPECT_TRUE(q_with_reserve.Empty());
    EXPECT_TRUE(q_without_reserve.Empty());

    std::cout << "Разница: " << (time_without_reserve - time_with_reserve)
              << " ms (экономия "
              << (100.0 * (time_without_reserve - time_with_reserve) / time_without_reserve)
              << "%)" << std::endl;

    EXPECT_LT(time_with_reserve * 1.0, time_without_reserve * 0.94);
}

TEST_F(QueuePerformanceTest, CapacityCtorCompareWithVector) {
    constexpr int LARGE_SIZE = 10'000'000;

    Queue q(LARGE_SIZE);
    long long queue_push_time = MeasureTime([&q]() {
        for (int i = 0; i < LARGE_SIZE; ++i) {
            q.Push(i);
        }
    });

    std::vector<int> vec;
    vec.reserve(LARGE_SIZE);
    long long vector_push_time = MeasureTime([&vec]() {
        for (int i = 0; i < LARGE_SIZE; ++i) {
            vec.push_back(i);
        }
    });

    std::cout << "\nСравнение с вектором (" << LARGE_SIZE << " элементов):" << std::endl;
    std::cout << "Очередь на двух стеках:" << std::endl;
    std::cout << "  Push: " << queue_push_time << " ms" << std::endl;
    std::cout << "Вектор:" << std::endl;
    std::cout << "  Push:  " << vector_push_time << " ms" << std::endl;

    EXPECT_LT(queue_push_time * 1.0, vector_push_time * 1.5);
}