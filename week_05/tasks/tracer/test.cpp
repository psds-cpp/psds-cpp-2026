#include <gtest/gtest.h>

#include <vector>

#include "tracer.cpp"


class TracerTest : public ::testing::Test {
protected:
    void SetUp() override {
        Tracer::ResetStats();
    }
};

TEST_F(TracerTest, DefaultConstructor) {
    {
        Tracer obj;
        EXPECT_EQ(obj.Id(), 1);
        EXPECT_EQ(obj.Name(), "obj_1");
        EXPECT_NE(obj.Data(), nullptr);

        EXPECT_EQ(Tracer::count, 1);
        EXPECT_EQ(Tracer::default_ctor, 1);
        EXPECT_EQ(Tracer::alive, 1);
    }

    EXPECT_EQ(Tracer::count, 1);
    EXPECT_EQ(Tracer::default_ctor, 1);
    EXPECT_EQ(Tracer::str_ctor, 0);
    EXPECT_EQ(Tracer::copy_ctor, 0);
    EXPECT_EQ(Tracer::move_ctor, 0);
    EXPECT_EQ(Tracer::dtor, 1);
    EXPECT_EQ(Tracer::alive, 0);
}

TEST_F(TracerTest, StringConstructor) {
    {
        Tracer obj("Hello");
        EXPECT_EQ(obj.Id(), 1);
        EXPECT_EQ(obj.Name(), "Hello_1");

        EXPECT_EQ(Tracer::count, 1);
        EXPECT_EQ(Tracer::str_ctor, 1);
        EXPECT_EQ(Tracer::alive, 1);
    }

    EXPECT_EQ(Tracer::count, 1);
    EXPECT_EQ(Tracer::default_ctor, 0);
    EXPECT_EQ(Tracer::str_ctor, 1);
    EXPECT_EQ(Tracer::dtor, 1);
    EXPECT_EQ(Tracer::alive, 0);
}

TEST_F(TracerTest, CopyConstructor) {
    Tracer original("Original");
    int original_id = original.Id();
    const char* original_ptr = original.Data();
    std::string original_name = original.Name();

    Tracer copy = original;

    EXPECT_NE(original_id, copy.Id());
    EXPECT_EQ(copy.Id(), 2);
    EXPECT_EQ(copy.Name(), original_name);

    EXPECT_NE(original_ptr, copy.Data());

    EXPECT_EQ(Tracer::default_ctor, 0);
    EXPECT_EQ(Tracer::str_ctor, 1);
    EXPECT_EQ(Tracer::copy_ctor, 1);
    EXPECT_EQ(Tracer::copy_assign, 0);
    EXPECT_EQ(Tracer::alive, 2);
}

TEST_F(TracerTest, MoveConstructor) {
    Tracer original("OriginalWithLongString");
    int original_id = original.Id();
    const char* original_ptr = original.Data();
    std::string original_name = original.Name();

    Tracer moved = std::move(original);

    EXPECT_NE(original_id, moved.Id());
    EXPECT_EQ(moved.Id(), 2);

    EXPECT_EQ(moved.Name(), original_name);
    EXPECT_TRUE(original.Name().empty());
    EXPECT_EQ(moved.Data(), original_ptr);

    EXPECT_EQ(Tracer::str_ctor, 1);
    EXPECT_EQ(Tracer::move_ctor, 1);
    EXPECT_EQ(Tracer::alive, 2);
}

TEST_F(TracerTest, CopyAssignment) {
    Tracer a("Apple");
    Tracer b("BananaBombaOuououou");

    int a_id = a.Id();
    int b_id = b.Id();
    const char* a_ptr_before = a.Data();
    const char* b_ptr = b.Data();

    a = b;

    EXPECT_EQ(a.Id(), a_id);
    EXPECT_EQ(b.Id(), b_id);
    EXPECT_EQ(a.Name(), b.Name());
    EXPECT_NE(a.Data(), b_ptr);
    EXPECT_NE(a.Data(), a_ptr_before);

    EXPECT_EQ(Tracer::default_ctor, 0);
    EXPECT_EQ(Tracer::copy_assign, 1);
    EXPECT_EQ(Tracer::dtor, 0);
}

TEST_F(TracerTest, MoveAssignment) {
    Tracer a("Apple");
    Tracer b("BananaBombaFlySoGreat");

    int a_id = a.Id();
    int b_id = b.Id();
    const char* b_ptr_before = b.Data();
    std::string b_name = b.Name();

    a = std::move(b);

    EXPECT_EQ(a.Id(), a_id);
    EXPECT_EQ(b.Id(), b_id);

    EXPECT_EQ(a.Name(), b_name);
    EXPECT_TRUE(b.Name().empty());
    EXPECT_EQ(a.Data(), b_ptr_before);

    EXPECT_EQ(Tracer::move_assign, 1);
    EXPECT_EQ(Tracer::default_ctor, 0);
    EXPECT_EQ(Tracer::copy_ctor, 0);
    EXPECT_EQ(Tracer::copy_assign, 0);
    EXPECT_EQ(Tracer::dtor, 0);
}

TEST_F(TracerTest, SelfAssignmentCopy) {
    Tracer obj("Test");
    std::string original_name = obj.Name();
    const char* original_ptr = obj.Data();
    int original_id = obj.Id();

    obj = obj;

    EXPECT_EQ(obj.Id(), original_id);
    EXPECT_EQ(obj.Name(), original_name);
    EXPECT_EQ(obj.Data(), original_ptr);

    EXPECT_EQ(Tracer::copy_assign, 0);
    EXPECT_EQ(Tracer::dtor, 0);
}

TEST_F(TracerTest, SelfAssignmentMove) {
    Tracer obj("Test");
    std::string original_name = obj.Name();
    const char* original_ptr = obj.Data();
    int original_id = obj.Id();

    obj = static_cast<Tracer&&>(obj);

    EXPECT_EQ(obj.Id(), original_id);
    EXPECT_EQ(obj.Data(), original_ptr);

    EXPECT_EQ(Tracer::move_assign, 0);
    EXPECT_EQ(Tracer::dtor, 0);
}

TEST_F(TracerTest, VectorPushBackCopy) {
    std::vector<Tracer> vec;
    vec.reserve(3);

    Tracer obj("Item");
    const char* obj_ptr = obj.Data();

    vec.push_back(obj);

    EXPECT_EQ(vec[0].Name(), obj.Name());
    EXPECT_NE(vec[0].Data(), obj_ptr);

    EXPECT_EQ(Tracer::copy_ctor, 1);
    EXPECT_EQ(Tracer::alive, 2);
}

TEST_F(TracerTest, VectorPushBackMove) {
    std::vector<Tracer> vec;
    vec.reserve(3);

    Tracer obj("LongNameToAvoidSSO");
    const char* obj_ptr = obj.Data();
    std::string obj_name = obj.Name();

    vec.push_back(std::move(obj));

    EXPECT_EQ(vec[0].Data(), obj_ptr);
    EXPECT_EQ(vec[0].Name(), obj_name);
    EXPECT_TRUE(obj.Name().empty());

    EXPECT_EQ(Tracer::move_ctor, 1);
    EXPECT_EQ(Tracer::alive, 2);
}

TEST_F(TracerTest, VectorEmplaceBack) {
    std::vector<Tracer> vec;
    vec.reserve(3);

    vec.emplace_back("Hello");

    EXPECT_EQ(Tracer::str_ctor, 1);
    EXPECT_EQ(Tracer::copy_ctor, 0);
    EXPECT_EQ(Tracer::move_ctor, 0);
    EXPECT_EQ(Tracer::alive, 1);
}

TEST_F(TracerTest, VectorReallocation) {
    std::vector<Tracer> vec;

    vec.emplace_back("First");   // 1 ctor
    vec.emplace_back("Second");  // 1 ctor + realloc (1 move)
    vec.emplace_back("Third");   // 1 ctor + realloc (2 move)

    EXPECT_EQ(Tracer::str_ctor, 3);
    EXPECT_EQ(Tracer::copy_ctor, 0);
    EXPECT_EQ(Tracer::move_ctor, 3);  // 1 + 2 move when realloc
    EXPECT_EQ(Tracer::alive, 3);
}

TEST_F(TracerTest, VectorWithReserve) {
    std::vector<Tracer> vec;
    vec.reserve(5);

    vec.emplace_back("First");
    vec.emplace_back("Second");
    vec.emplace_back("Third");
    vec.emplace_back("Fourth");
    vec.emplace_back("Fifth");

    EXPECT_EQ(Tracer::str_ctor, 5);
    EXPECT_EQ(Tracer::move_ctor, 0);
    EXPECT_EQ(Tracer::alive, 5);
}

Tracer CreateTracer() {
    return Tracer("Hello");  // RVO
}

TEST_F(TracerTest, ReturnValueOptimization) {
    Tracer obj = CreateTracer();

    EXPECT_EQ(Tracer::str_ctor, 1);
    EXPECT_EQ(Tracer::copy_ctor, 0);
    EXPECT_EQ(Tracer::move_ctor, 0);
}

TEST_F(TracerTest, MultipleObjectsConsistency) {
    {
        Tracer a("A");
        Tracer b = a;         // copy ctor
        Tracer c = std::move(a); // move ctor

        std::vector<Tracer> vec;
        vec.reserve(2);
        vec.push_back(b);
        vec.push_back(std::move(c));

        a = b;                    // copy assignment
        b = std::move(vec[0]);    // move assignment
    }

    int total_created = Tracer::default_ctor + Tracer::str_ctor + Tracer::copy_ctor +
        Tracer::move_ctor;

    EXPECT_EQ(total_created, Tracer::dtor);
    EXPECT_EQ(Tracer::alive, 0);
    EXPECT_EQ(Tracer::count, total_created);
}

TEST_F(TracerTest, DataMethodReturnsValidPointer) {
    Tracer obj("Test");
    const char* ptr = obj.Data();

    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 'T');
    EXPECT_EQ(ptr[1], 'e');
    EXPECT_EQ(ptr[2], 's');
    EXPECT_EQ(ptr[3], 't');

    Tracer copy = obj;
    EXPECT_NE(obj.Data(), copy.Data());
    EXPECT_STREQ(obj.Data(), copy.Data());
}

TEST_F(TracerTest, ResetStatsWorks) {
    Tracer a("A");
    Tracer b = a;

    EXPECT_GT(Tracer::count, 0);
    EXPECT_GT(Tracer::alive, 0);

    Tracer::ResetStats();

    EXPECT_EQ(Tracer::count, 0);
    EXPECT_EQ(Tracer::default_ctor, 0);
    EXPECT_EQ(Tracer::str_ctor, 0);
    EXPECT_EQ(Tracer::copy_ctor, 0);
    EXPECT_EQ(Tracer::move_ctor, 0);
    EXPECT_EQ(Tracer::copy_assign, 0);
    EXPECT_EQ(Tracer::move_assign, 0);
    EXPECT_EQ(Tracer::dtor, 0);
    EXPECT_EQ(Tracer::alive, 0);

    EXPECT_FALSE(a.Name().empty());
    EXPECT_FALSE(b.Name().empty());
}

TEST_F(TracerTest, ChainedAssignments) {
    Tracer a("A");
    Tracer b("B");
    Tracer c("C");

    a = b = c;

    EXPECT_NE(a.Name().find("C_"), std::string::npos);
    EXPECT_NE(b.Name().find("C_"), std::string::npos);
    EXPECT_NE(c.Name().find("C_"), std::string::npos);

    EXPECT_EQ(a.Id(), 1);
    EXPECT_EQ(b.Id(), 2);
    EXPECT_EQ(c.Id(), 3);

    EXPECT_EQ(Tracer::copy_assign, 2);
}

TEST_F(TracerTest, TemporaryObjectInExpression) {
    Tracer a("Start");
    a = Tracer("Temp");

    EXPECT_EQ(Tracer::str_ctor, 2);
    EXPECT_EQ(Tracer::move_assign, 1);
}

TEST_F(TracerTest, StdSwapUsesMoveOperations) {
    Tracer a("ThisNameRequireLongStringToAvoidSSO");
    Tracer b("LongStringToAvoidSSO");
    std::string name_a = a.Name();
    std::string name_b = b.Name();

    const char* a_ptr_before = a.Data();
    const char* b_ptr_before = b.Data();
    int a_id = a.Id();
    int b_id = b.Id();

    std::swap(a, b);

    EXPECT_EQ(a.Name(), name_b);
    EXPECT_EQ(b.Name(), name_a);

    EXPECT_EQ(a.Id(), a_id);
    EXPECT_EQ(b.Id(), b_id);

    EXPECT_EQ(a.Data(), b_ptr_before);
    EXPECT_EQ(b.Data(), a_ptr_before);

    // std::swap uses move construction and move assignment
    EXPECT_EQ(Tracer::move_ctor + Tracer::move_assign, 3);
}
