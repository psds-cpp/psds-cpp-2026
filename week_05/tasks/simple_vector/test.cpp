#include <gtest/gtest.h>

#include "simple_vector.cpp"


TEST(SimpleVectorTest, DefaultConstructor) {
    SimpleVector v;
    EXPECT_EQ(v.Size(), 0);
    EXPECT_EQ(v.Capacity(), 0);
    EXPECT_TRUE(v.Empty());
}

TEST(SimpleVectorTest, SizeConstructor) {
    SimpleVector v(5);
    EXPECT_EQ(v.Size(), 5);
    EXPECT_EQ(v.Capacity(), 5);
    EXPECT_FALSE(v.Empty());

    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(SimpleVectorTest, SizeValueConstructor) {
    SimpleVector v(3, 42);
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v.Capacity(), 3);

    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], 42);
    }
}

TEST(SimpleVectorTest, InitializerListConstructor) {
    SimpleVector v = {1, 2, 3, 4, 5};
    EXPECT_EQ(v.Size(), 5);
    EXPECT_EQ(v.Capacity(), 5);

    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], static_cast<int>(i + 1));
    }
}

TEST(SimpleVectorTest, CopyConstructor) {
    SimpleVector original = {1, 2, 3};
    SimpleVector copy(original);

    EXPECT_EQ(copy.Size(), original.Size());
    EXPECT_EQ(copy.Capacity(), original.Capacity());

    EXPECT_EQ(original, copy);

    copy[0] = 100;
    EXPECT_EQ(original[0], 1);
}

TEST(SimpleVectorTest, MoveConstructor) {
    SimpleVector original = {1, 2, 3};
    size_t original_size = original.Size();
    size_t original_capacity = original.Capacity();
    const int* original_data = original.Data();

    SimpleVector moved(std::move(original));

    EXPECT_EQ(moved.Size(), original_size);
    EXPECT_EQ(moved.Capacity(), original_capacity);
    EXPECT_EQ(moved.Data(), original_data);

    EXPECT_EQ(original.Size(), 0);
    EXPECT_EQ(original.Capacity(), 0);
    EXPECT_EQ(original.Data(), nullptr);
}


TEST(SimpleVectorTest, CopyAssignment) {
    SimpleVector v1 = {1, 2, 3};
    SimpleVector v2 = {4, 5};

    v2 = v1;

    EXPECT_EQ(v2.Size(), v1.Size());
    EXPECT_EQ(v2.Capacity(), v1.Size());

    EXPECT_EQ(v2, v1);
}

TEST(SimpleVectorTest, SelfCopyAssignment) {
    SimpleVector v1 = {1, 2, 3};
    auto cap = v1.Capacity();

    v1 = v1;

    EXPECT_EQ(v1.Capacity(), cap);
    EXPECT_EQ(v1.Size(), 3);
    EXPECT_EQ(v1[0], 1);
}
TEST(SimpleVectorTest, MoveAssignment) {
    SimpleVector v1 = {1, 2, 3};
    SimpleVector v2;

    const int* v1_data = v1.Data();
    size_t v1_size = v1.Size();
    size_t v1_capacity = v1.Capacity();

    v2 = std::move(v1);

    EXPECT_EQ(v2.Size(), v1_size);
    EXPECT_EQ(v2.Capacity(), v1_capacity);
    EXPECT_EQ(v2.Data(), v1_data);

    EXPECT_EQ(v1.Size(), 0);
    EXPECT_EQ(v1.Capacity(), 0);
    EXPECT_EQ(v1.Data(), nullptr);
}

TEST(SimpleVectorTest, PushBack) {
    SimpleVector v;

    v.PushBack(1);
    EXPECT_EQ(v.Size(), 1);
    EXPECT_EQ(v.Capacity(), 1);
    EXPECT_EQ(v[0], 1);

    v.PushBack(2);
    EXPECT_EQ(v.Size(), 2);
    EXPECT_EQ(v.Capacity(), 2);
    EXPECT_EQ(v[1], 2);

    v.PushBack(3);
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v.Capacity(), 4);
    EXPECT_EQ(v[2], 3);
}

TEST(SimpleVectorTest, EmptyPopBack) {
    SimpleVector v;
    EXPECT_NO_THROW(v.PopBack());
    EXPECT_EQ(v.Size(), 0);
    EXPECT_EQ(v.Capacity(), 0);
}

TEST(SimpleVectorTest, PopBack) {
    SimpleVector v = {1, 2, 3, 4};

    v.PopBack();
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v.Capacity(), 4);

    v.PopBack();
    EXPECT_EQ(v.Size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v.Capacity(), 4);

    v.PopBack();
    v.PopBack();
    EXPECT_EQ(v.Size(), 0);
    EXPECT_TRUE(v.Empty());
    EXPECT_EQ(v.Capacity(), 4);

    v.PopBack();
    EXPECT_EQ(v.Size(), 0);
    EXPECT_EQ(v.Capacity(), 4);
}

TEST(SimpleVectorTest, Insert) {
    SimpleVector v = {1, 3, 4};

    int* inserted = v.Insert(v.Data() + 1, 2);
    EXPECT_EQ(v.Size(), 4);
    EXPECT_EQ(*inserted, 2);
    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], static_cast<int>(i + 1));
    }

    v.Insert(v.Data(), 0);
    EXPECT_EQ(v.Size(), 5);
    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], static_cast<int>(i));
    }

    v.Insert(v.Data() + v.Size(), 5);
    EXPECT_EQ(v.Size(), 6);
    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], static_cast<int>(i));
    }

    int* result = v.Insert(v.Data() - 1, 100);
    EXPECT_EQ(v.Size(), 6);
    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v[i], static_cast<int>(i));
    }
    EXPECT_EQ(result, v.Data() + v.Size());
}

TEST(SimpleVectorTest, Erase) {
    SimpleVector v = {1, 2, 3, 4, 5};

    int* ptr = v.Erase(v.Data() + 1);
    EXPECT_EQ(v.Size(), 4);
    EXPECT_EQ(*ptr, 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 5);

    v.Erase(v.Data());
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v[0], 3);

    ptr = v.Erase(v.Data() + v.Size() - 1);
    EXPECT_EQ(v.Size(), 2);
    EXPECT_EQ(ptr, v.Data() + v.Size());
    EXPECT_EQ(v[1], 4);

    ptr = v.Erase(v.Data() + v.Size() + 1);
    EXPECT_EQ(ptr, v.Data() + v.Size());
}

TEST(SimpleVectorTest, Resize) {
    SimpleVector v = {1, 2, 3};

    v.Resize(2);
    EXPECT_EQ(v.Size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);

    v.Resize(4);
    EXPECT_EQ(v.Size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[3], 0);

    v.Resize(6, 42);
    EXPECT_EQ(v.Size(), 6);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[3], 0);
    EXPECT_EQ(v[4], 42);
    EXPECT_EQ(v[5], 42);
}

TEST(SimpleVectorTest, Reserve) {
    SimpleVector v;

    v.Reserve(10);
    EXPECT_EQ(v.Capacity(), 10);
    EXPECT_EQ(v.Size(), 0);

    SimpleVector expected = {1, 2, 3};
    v = {1, 2, 3};
    v.Reserve(5);
    EXPECT_EQ(v.Capacity(), 5);
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v, expected);

    v.Reserve(2);
    EXPECT_EQ(v.Capacity(), 5);
}

TEST(SimpleVectorTest, Clear) {
    SimpleVector v = {1, 2, 3, 4, 5};

    v.Clear();
    EXPECT_EQ(v.Size(), 0);
    EXPECT_EQ(v.Capacity(), 5);
    EXPECT_TRUE(v.Empty());
}

TEST(SimpleVectorTest, Swap) {
    SimpleVector v1 = {1, 2, 3};
    SimpleVector v2 = {4, 5};

    const int* v1_data = v1.Data();
    const int* v2_data = v2.Data();
    size_t v1_size = v1.Size();
    size_t v2_size = v2.Size();
    size_t v1_cap = v1.Capacity();
    size_t v2_cap = v2.Capacity();

    v1.Swap(v2);

    EXPECT_EQ(v1.Size(), v2_size);
    EXPECT_EQ(v1.Data(), v2_data);
    EXPECT_EQ(v1.Capacity(), v2_cap);
    EXPECT_EQ(v2.Size(), v1_size);
    EXPECT_EQ(v2.Data(), v1_data);
    EXPECT_EQ(v2.Capacity(), v1_cap);
}

TEST(SimpleVectorTest, ExternalSwap) {
    SimpleVector v1 = {1, 2, 3};
    SimpleVector v2 = {4, 5};

    swap(v1, v2);

    EXPECT_EQ(v1.Size(), 2);
    EXPECT_EQ(v2.Size(), 3);
}

TEST(SimpleVectorTest, RangeBasedFor) {
    SimpleVector v = {1, 2, 3, 4, 5};
    int sum = 0;
    for (int x : v) {
        sum += x;
    }
    EXPECT_EQ(sum, 15);

    const SimpleVector& cv = v;
    sum = 0;
    for (int x : cv) {
        sum += x;
    }
    EXPECT_EQ(sum, 15);
}

TEST(SimpleVectorTest, EqualityOperators) {
    SimpleVector v1 = {1, 2, 3};
    SimpleVector v2 = {1, 2, 3};
    SimpleVector v3 = {1, 2};
    SimpleVector v4 = {1, 2, 4};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);

    EXPECT_FALSE(v1 == v3);
    EXPECT_TRUE(v1 != v3);

    EXPECT_FALSE(v1 == v4);
    EXPECT_TRUE(v1 != v4);
}

TEST(SimpleVectorTest, AccessMethods) {
    SimpleVector v = {10, 20, 30};
    const SimpleVector& cv = v;

    EXPECT_EQ(*v.Data(), 10);
    EXPECT_EQ(*cv.Data(), 10);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(cv[1], 20);

    v[2] = 40;
    EXPECT_EQ(v[2], 40);
}

TEST(SimpleVectorTest, ComplexOperations) {
    SimpleVector v;

    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);

    v.Insert(v.Data() + 1, 99);
    v.Erase(v.Data() + 2);

    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 99);
    EXPECT_EQ(v[2], 3);

    v.Resize(5, 100);
    EXPECT_EQ(v.Size(), 5);
    EXPECT_EQ(v[3], 100);
    EXPECT_EQ(v[4], 100);

    v.Reserve(20);
    EXPECT_EQ(v.Capacity(), 20);
}

TEST(SimpleVectorTest, WorkAfterMoveCtor) {
    SimpleVector original = {1, 2, 3};
    SimpleVector moved(std::move(original));

    moved.PushBack(17);
    EXPECT_EQ(moved.Size(), 4);
    EXPECT_EQ(moved[3], 17);

    original.PushBack(17);
    EXPECT_EQ(original.Size(), 1);
    EXPECT_EQ(original[0], 17);
}

TEST(SimpleVectorTest, WorkAfterMoveAssignment) {
    SimpleVector original = {1, 2, 3};
    SimpleVector moved = {4, 5};
    moved = std::move(original);

    moved.PushBack(17);
    EXPECT_EQ(moved.Size(), 4);
    EXPECT_EQ(moved[3], 17);

    original.PushBack(17);
    EXPECT_EQ(original.Size(), 1);
    EXPECT_EQ(original[0], 17);
}