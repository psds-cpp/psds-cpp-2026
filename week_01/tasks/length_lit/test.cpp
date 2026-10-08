#include <gtest/gtest.h>

#include "length_lit.cpp"

namespace {
    constexpr double EPSILON = 1e-6;
} // namespace

TEST(LengthLiteralsTest, FeetToMeters) {
    EXPECT_NEAR(0.3048, 1.0_ft_to_m, EPSILON);
    EXPECT_NEAR(0.0, 0.0_ft_to_m, EPSILON);
    EXPECT_NEAR(3.048, 10.0_ft_to_m, EPSILON);
}

TEST(LengthLiteralsTest, FeetToCentimeters) {
    EXPECT_NEAR(30.48, 1.0_ft_to_cm, EPSILON);
    EXPECT_NEAR(0.0, 0.0_ft_to_cm, EPSILON);
    EXPECT_NEAR(304.8, 10.0_ft_to_cm, EPSILON);
}

TEST(LengthLiteralsTest, FeetToInches) {
    EXPECT_NEAR(12.0, 1.0_ft_to_in, EPSILON);
    EXPECT_NEAR(0.0, 0.0_ft_to_in, EPSILON);
    EXPECT_NEAR(60.0, 5.0_ft_to_in, EPSILON);
}

TEST(LengthLiteralsTest, InchesToMeters) {
    EXPECT_NEAR(0.0254, 1.0_in_to_m, EPSILON);
    EXPECT_NEAR(0.0, 0.0_in_to_m, EPSILON);
    EXPECT_NEAR(0.254, 10.0_in_to_m, EPSILON);
}

TEST(LengthLiteralsTest, InchesToCentimeters) {
    EXPECT_NEAR(2.54, 1.0_in_to_cm, EPSILON);
    EXPECT_NEAR(0.0, 0.0_in_to_cm, EPSILON);
    EXPECT_NEAR(25.4, 10.0_in_to_cm, EPSILON);
}

TEST(LengthLiteralsTest, InchesToFeet) {
    EXPECT_NEAR(1.0, 12.0_in_to_ft, EPSILON); 
    EXPECT_NEAR(0.0, 0.0_in_to_ft, EPSILON);
    EXPECT_NEAR(0.5, 6.0_in_to_ft, EPSILON);
}

// Тесты для преобразования из метров
TEST(LengthLiteralsTest, MetersToFeet) {
    EXPECT_NEAR(3.280839895, 1.0_m_to_ft, EPSILON);
    EXPECT_NEAR(0.0, 0.0_m_to_ft, EPSILON);
    EXPECT_NEAR(32.80839895, 10.0_m_to_ft, EPSILON);
}

TEST(LengthLiteralsTest, MetersToInches) {
    EXPECT_NEAR(39.37007874, 1.0_m_to_in, EPSILON);
    EXPECT_NEAR(0.0, 0.0_m_to_in, EPSILON);
    EXPECT_NEAR(393.7007874, 10.0_m_to_in, EPSILON);
}

TEST(LengthLiteralsTest, MetersToCentimeters) {
    EXPECT_NEAR(100.0, 1.0_m_to_cm, EPSILON);
    EXPECT_NEAR(0.0, 0.0_m_to_cm, EPSILON);
    EXPECT_NEAR(250.0, 2.5_m_to_cm, EPSILON); 
}

TEST(LengthLiteralsTest, CentimetersToMeters) {
    EXPECT_NEAR(0.01, 1.0_cm_to_m, EPSILON);
    EXPECT_NEAR(0.0, 0.0_cm_to_m, EPSILON);
    EXPECT_NEAR(1.0, 100.0_cm_to_m, EPSILON);
}

TEST(LengthLiteralsTest, CentimetersToFeet) {
    EXPECT_NEAR(0.0328084, 1.0_cm_to_ft, EPSILON);
    EXPECT_NEAR(0.0, 0.0_cm_to_ft, EPSILON);
    EXPECT_NEAR(3.28084, 100.0_cm_to_ft, EPSILON);
}

TEST(LengthLiteralsTest, CentimetersToInches) {
    EXPECT_NEAR(0.3937007874, 1.0_cm_to_in, EPSILON);
    EXPECT_NEAR(0.0, 0.0_cm_to_in, EPSILON);
    EXPECT_NEAR(39.37007874, 100.0_cm_to_in, EPSILON);
}

TEST(LengthLiteralsTest, RealExamples) {

    EXPECT_NEAR(1.8288, 6.0_ft_to_m, EPSILON);
    EXPECT_NEAR(182.88, 6.0_ft_to_cm, EPSILON);
    EXPECT_NEAR(72.0, 6.0_ft_to_in, EPSILON);  

    EXPECT_NEAR(175.26, 5.0_ft_to_cm + 9.0_in_to_cm, EPSILON);

    EXPECT_NEAR(139.7, 55.0_in_to_cm, EPSILON);
    EXPECT_NEAR(1.397, 55.0_in_to_m, EPSILON);

    EXPECT_NEAR(0.21, 21.0_cm_to_m, EPSILON);
    EXPECT_NEAR(8.2677165354, 21.0_cm_to_in, EPSILON);
}

TEST(LengthLiteralsTest, NegativeValues) {
    EXPECT_NEAR(-0.3048, -1.0_ft_to_m, EPSILON);
    EXPECT_NEAR(-30.48, -1.0_ft_to_cm, EPSILON);
    EXPECT_NEAR(-12.0, -1.0_ft_to_in, EPSILON);
    EXPECT_NEAR(-100.0, -1.0_m_to_cm, EPSILON);
}
