#include <gtest/gtest.h>

#include <cmath>
#include <numbers>

#include "phasor.cpp"

namespace {
    using std::numbers::pi;
    constexpr double EPS = 1e-6;
}


TEST(PhasorTest, SizeCheck) {
    EXPECT_EQ(sizeof(Phasor), 2 * sizeof(double));
}

TEST(PhasorTest, DefaultCtor) {
    Phasor p;
    EXPECT_DOUBLE_EQ(p.Magnitude(), 0.0);
    EXPECT_DOUBLE_EQ(p.Phase(), 0.0);
    EXPECT_DOUBLE_EQ(p.Real(), 0.0);
    EXPECT_DOUBLE_EQ(p.Imag(), 0.0);
}

TEST(PhasorTest, PolarCtor) {
    {
        Phasor p(10.0, pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 4, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 45., EPS);
        EXPECT_NEAR(p.Real(), 5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), 5.0 * std::sqrt(2), EPS);
    }
    {
        Phasor p(10.0, -pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), -pi / 4, EPS);
        EXPECT_NEAR(p.PhaseDeg(), -45., EPS);
        EXPECT_NEAR(p.Real(), 5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), -5.0 * std::sqrt(2), EPS);
    }
    {
        Phasor p(10.0, 3 * pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), 3 * pi / 4, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 135., EPS);
        EXPECT_NEAR(p.Real(), -5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), 5.0 * std::sqrt(2), EPS);
    }
    {
        Phasor p(10.0, -3 * pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), -3 * pi / 4, EPS);
        EXPECT_NEAR(p.PhaseDeg(), -135., EPS);
        EXPECT_NEAR(p.Real(), -5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), -5.0 * std::sqrt(2), EPS);
    }
}

TEST(PhasorTest, NegativeMagnitude) {
    {
        Phasor p(-10.0, pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 4 - pi, EPS);
        EXPECT_NEAR(p.PhaseDeg(), -135., EPS);
        EXPECT_NEAR(p.Real(), -5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), -5.0 * std::sqrt(2), EPS);
    }
    {
        Phasor p(-10.0, -pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), - pi / 4 + pi, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 135., EPS);
        EXPECT_NEAR(p.Real(), -5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), 5.0 * std::sqrt(2), EPS);
    }
    {
        Phasor p(-10.0, 3 * pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), - pi / 4, EPS);
        EXPECT_NEAR(p.PhaseDeg(), -45., EPS);
        EXPECT_NEAR(p.Real(), 5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), -5.0 * std::sqrt(2), EPS);
    }
    {
        Phasor p(-10.0, -3 * pi / 4);
        EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 4, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 45., EPS);
        EXPECT_NEAR(p.Real(), 5.0 * std::sqrt(2), EPS);
        EXPECT_NEAR(p.Imag(), 5.0 * std::sqrt(2), EPS);
    }
}

TEST(PhasorTest, ExpTagConstructor) {
    {
        Phasor p(5.0, pi / 3, ExpTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 3, EPS);
    }
    {
        Phasor p(-5.0, pi / 3, ExpTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.Phase(), - 2 * pi / 3, EPS);
    }
    {
        Phasor p(5.0, 2 * pi / 3, ExpTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.Phase(), 2 * pi / 3, EPS);
    }
    {
        Phasor p(5.0, 7 * pi / 3, ExpTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 3, EPS);
    }
}

TEST(PhasorTest, DegTagConstructor) {
    {
        Phasor p(5.0, 60.0, DegTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 60.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 3, EPS);
    }
    {
        Phasor p(5.0, -60.0, DegTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.PhaseDeg(), -60.0, EPS);
        EXPECT_NEAR(p.Phase(), -pi / 3, EPS);
    }
    {
        Phasor p(-5.0, -60.0, DegTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 120.0, EPS);
        EXPECT_NEAR(p.Phase(), 2 * pi / 3, EPS);
    }
    {
        Phasor p(5.0, -360.0, DegTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.PhaseDeg(), 0.0, EPS);
        EXPECT_NEAR(p.Phase(), 0.0, EPS);
    }
}

TEST(PhasorTest, AlgTagConstructor) {
    {
        Phasor p(3.0, 4.0, AlgTag{});
        EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
        EXPECT_NEAR(p.Phase(), std::atan2(4.0, 3.0), EPS);
        EXPECT_DOUBLE_EQ(p.Real(), 3.0);
        EXPECT_DOUBLE_EQ(p.Imag(), 4.0);
    }
    {
        Phasor p(std::sqrt(2), std::sqrt(2), AlgTag{});
        EXPECT_NEAR(p.Magnitude(), 2.0, EPS);
        EXPECT_NEAR(p.Phase(), pi / 4, EPS);
        EXPECT_DOUBLE_EQ(p.Real(), std::sqrt(2));
        EXPECT_DOUBLE_EQ(p.Imag(), std::sqrt(2));
    }
    {
        Phasor p(-std::sqrt(2), -std::sqrt(2), AlgTag{});
        EXPECT_NEAR(p.Magnitude(), 2.0, EPS);
        EXPECT_NEAR(p.Phase(), -3 * pi / 4, EPS);
        EXPECT_DOUBLE_EQ(p.Real(), -std::sqrt(2));
        EXPECT_DOUBLE_EQ(p.Imag(), -std::sqrt(2));
    }
    {
        Phasor p(std::sqrt(2), -std::sqrt(2), AlgTag{});
        EXPECT_NEAR(p.Magnitude(), 2.0, EPS);
        EXPECT_NEAR(p.Phase(), -pi / 4, EPS);
        EXPECT_DOUBLE_EQ(p.Real(), std::sqrt(2));
        EXPECT_DOUBLE_EQ(p.Imag(), -std::sqrt(2));
    }
    {
        Phasor p(-std::sqrt(2), std::sqrt(2), AlgTag{});
        EXPECT_NEAR(p.Magnitude(), 2.0, EPS);
        EXPECT_NEAR(p.Phase(), 3 * pi / 4, EPS);
        EXPECT_DOUBLE_EQ(p.Real(), -std::sqrt(2));
        EXPECT_DOUBLE_EQ(p.Imag(), std::sqrt(2));
    }
}

TEST(PhasorTest, PhaseNormalization) {
    Phasor p1(1.0, 3 * pi / 2);
    EXPECT_NEAR(p1.Phase(), -pi / 2, EPS);
    EXPECT_NEAR(p1.PhaseDeg(), -90., EPS);

    Phasor p2(1.0, -3 * pi / 2);
    EXPECT_NEAR(p2.Phase(), pi / 2, EPS);
    EXPECT_NEAR(p2.PhaseDeg(), 90., EPS);

    Phasor p3(1.0, 2 * pi + pi / 4);
    EXPECT_NEAR(p3.Phase(), pi / 4, EPS);
    EXPECT_NEAR(p3.PhaseDeg(), 45., EPS);
}

TEST(PhasorTest, Synonyms) {
    Phasor p(3.0, 4.0,AlgTag{});
    EXPECT_DOUBLE_EQ(p.Magnitude(), p.Abs());
    EXPECT_DOUBLE_EQ(p.Phase(), p.Angle());
    EXPECT_DOUBLE_EQ(p.PhaseDeg(), p.AngleDeg());
}

TEST(PhasorTest, SetPolar) {
    Phasor p;
    p.SetPolar(10.0, pi / 6);

    EXPECT_NEAR(p.Magnitude(), 10.0, EPS);
    EXPECT_NEAR(p.Phase(), pi / 6, EPS);
    EXPECT_NEAR(p.Real(), 10.0 * std::sqrt(3) / 2, EPS);
    EXPECT_NEAR(p.Imag(), 5.0, EPS);
}

TEST(PhasorTest, SetCartesian) {
    Phasor p;
    p.SetCartesian(1.0, sqrt(3.0));

    EXPECT_NEAR(p.Magnitude(), 2.0, EPS);
    EXPECT_NEAR(p.Phase(), pi / 3, EPS);
    EXPECT_DOUBLE_EQ(p.Real(), 1.0);
    EXPECT_DOUBLE_EQ(p.Imag(), std::sqrt(3.0));
}

TEST(MathPhasorTest, UnaryMinus) {
    Phasor p(3.0, 4.0, AlgTag{});
    Phasor p2 = -p;

    EXPECT_DOUBLE_EQ(p2.Real(), -3.0);
    EXPECT_DOUBLE_EQ(p2.Imag(), -4.0);
    EXPECT_NEAR(p2.Magnitude(), p.Magnitude(), EPS);
    EXPECT_NEAR(p2.Phase(), p.Phase() - pi, EPS);
}

TEST(MathPhasorTest, Addition) {
    Phasor p1(1.0, 2.0, AlgTag{});
    Phasor p2(3.0, 4.0, AlgTag{});
    Phasor res = p1 + p2;

    Phasor expected(4.0, 6.0, AlgTag{});
    EXPECT_EQ(res, expected);
}

TEST(MathPhasorTest, Subtraction) {
    Phasor p1(5.0, 6.0, AlgTag{});
    Phasor p2(2.0, -3.0, AlgTag{});
    Phasor res = p1 - p2;

    Phasor expected(3.0, 9.0, AlgTag{});
    EXPECT_EQ(res, expected);
}

TEST(MathPhasorTest, Multiplication) {
    Phasor p1(1.0, 2.0, AlgTag{});
    Phasor p2(3.0, 4.0, AlgTag{});
    Phasor res = p1 * p2;

    EXPECT_NEAR(res.Real(), -5.0, EPS);
    EXPECT_NEAR(res.Imag(), 10.0, EPS);

    Phasor p3(2.0, 60.0, DegTag{});
    Phasor p4(3.0, 30.0, DegTag{});
    res = p3 * p4;

    EXPECT_NEAR(res.Magnitude(), 6.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), 90.0, EPS);
}

TEST(MathPhasorTest, Division) {
    Phasor p1(3.0, 4.0, AlgTag{});
    Phasor p2(1.0, 1.0, AlgTag{});
    Phasor res = p1 / p2;

    EXPECT_NEAR(res.Real(), 3.5, EPS);
    EXPECT_NEAR(res.Imag(), 0.5, EPS);

    Phasor p3(6.0, 90.0, DegTag{});
    Phasor p4(3.0, 30.0, DegTag{});
    res = p3 / p4;

    EXPECT_NEAR(res.Magnitude(), 2.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), 60.0, EPS);
}

TEST(MathPhasorTest, CompoundAssignment) {
    Phasor p1(2.0, 3.0, AlgTag{});
    Phasor p2(1.0, 1.0, AlgTag{});

    p1 += p2;
    EXPECT_DOUBLE_EQ(p1.Real(), 3.0);
    EXPECT_DOUBLE_EQ(p1.Imag(), 4.0);

    p1 -= p2;
    EXPECT_DOUBLE_EQ(p1.Real(), 2.0);
    EXPECT_DOUBLE_EQ(p1.Imag(), 3.0);

    p1 *= Phasor(2.0, 0.0, DegTag{});
    EXPECT_NEAR(p1.Magnitude(), 2.0 * sqrt(13.0), EPS);
    EXPECT_DOUBLE_EQ(p1.Phase(), atan2(3.0, 2.0));

    p1 /= Phasor(2.0, 0.0, DegTag{});
    EXPECT_NEAR(p1.Magnitude(), std::sqrt(13.0), EPS);
    EXPECT_DOUBLE_EQ(p1.Phase(), std::atan2(3.0, 2.0));
}

TEST(MathPhasorTest, ScalarAddition) {
    Phasor p(1.0, 2.0, AlgTag{});
    Phasor res = p + 3.0;
    EXPECT_DOUBLE_EQ(res.Real(), 4.0);
    EXPECT_DOUBLE_EQ(res.Imag(), 2.0);

    res = -3.0 + p;
    EXPECT_DOUBLE_EQ(res.Real(), -2.0);
    EXPECT_DOUBLE_EQ(res.Imag(), 2.0);
}

TEST(MathPhasorTest, ScalarSubtraction) {
    Phasor p(5.0, 2.0, AlgTag{});
    Phasor res = p - 7.0;
    EXPECT_DOUBLE_EQ(res.Real(), -2.0);
    EXPECT_DOUBLE_EQ(res.Imag(), 2.0);

    res = 3.0 - p;
    EXPECT_DOUBLE_EQ(res.Real(), -2.0);
    EXPECT_DOUBLE_EQ(res.Imag(), -2.0);
}

TEST(MathPhasorTest, ScalarMultiplication) {
    Phasor p(2.0, 60.0, DegTag{});

    Phasor res = p * 3.0;
    EXPECT_NEAR(res.Magnitude(), 6.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), 60.0, EPS);

    res = -2.0 * p;
    EXPECT_NEAR(res.Magnitude(), 4.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), 60.0 - 180.0, EPS);

    res = 3.0 * p;
    EXPECT_NEAR(res.Magnitude(), 6.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), 60.0, EPS);
}

TEST(MathPhasorTest, ScalarDivision) {
    Phasor p(6.0, 60.0, DegTag{});

    Phasor res = p / 2.0;
    EXPECT_NEAR(res.Magnitude(), 3.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), 60.0, EPS);

    res = 12.0 / p;
    EXPECT_NEAR(res.Magnitude(), 2.0, EPS);
    EXPECT_NEAR(res.PhaseDeg(), -60.0, EPS);
}

TEST(PhasorTest, Conjugate) {
    Phasor p(3.0, 4.0,AlgTag{});
    Phasor conj = p.Conj();

    EXPECT_DOUBLE_EQ(conj.Real(), p.Real());
    EXPECT_DOUBLE_EQ(conj.Imag(), -p.Imag());
    EXPECT_DOUBLE_EQ(conj.Magnitude(), p.Magnitude());
    EXPECT_DOUBLE_EQ(conj.Phase(), -p.Phase());

    Phasor res = p * conj;
    EXPECT_NEAR(res.Imag(), 0.0, EPS);
    EXPECT_NEAR(res.Real(), p.Magnitude() * p.Magnitude(), EPS);
}

TEST(PhasorTest, Inverse) {
    Phasor p(4.0, 60.0, DegTag{});
    Phasor inv = p.Inv();

    EXPECT_NEAR(inv.Magnitude(), 0.25, EPS);
    EXPECT_NEAR(inv.PhaseDeg(), -60.0, EPS);

    Phasor res = p * inv;
    EXPECT_NEAR(res.Magnitude(), 1.0, EPS);
    EXPECT_NEAR(res.Phase(), 0.0, EPS);
}

TEST(PhasorTest, Equality) {
    Phasor p1(1.0, 2.0, AlgTag{});
    Phasor p2(1.0, 2.0, AlgTag{});
    Phasor p3(1.0, 2.000000001, AlgTag{});

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);

    Phasor p4(1.0, 45.0, DegTag{});
    Phasor p5(std::cos(pi / 4), std::sin(pi / 4), AlgTag{});
    EXPECT_TRUE(p4 == p5);
}

TEST(PhasorTest, FactoryFunctions) {
    Phasor p1 = MakePhasorCartesian(3.0, 4.0);
    EXPECT_DOUBLE_EQ(p1.Real(), 3.0);
    EXPECT_DOUBLE_EQ(p1.Imag(), 4.0);

    Phasor p2 = MakePhasorPolar(5.0, pi / 3);
    EXPECT_NEAR(p2.Magnitude(), 5.0, EPS);
    EXPECT_NEAR(p2.Phase(), pi / 3, EPS);

    Phasor p3 = MakePhasorPolarDeg(5.0, 60.0);
    EXPECT_NEAR(p3.Magnitude(), 5.0, EPS);
    EXPECT_NEAR(p3.PhaseDeg(), 60.0, EPS);
}

TEST(PhasorTest, OutputOperator) {
    Phasor p(5.0, 45.0, DegTag{});
    std::stringstream ss;
    ss << p;

    std::string output = ss.str();

    EXPECT_TRUE(output.find("5.000") != std::string::npos);
    EXPECT_TRUE(output.find("45.000") != std::string::npos);
    EXPECT_TRUE(output.find("*e(j*") != std::string::npos);
    EXPECT_TRUE(output.find(") [") != std::string::npos);
    EXPECT_TRUE(output.find(" + j*") != std::string::npos);
    EXPECT_TRUE(output.find("]") != std::string::npos);
}

TEST(MathPhasorTest, ComplexCalculations) {
    Phasor z1(3.0, 30.0, DegTag{});
    Phasor z2(4.0, 60.0, DegTag{});
    Phasor z3(2.0, -45.0, DegTag{});

    Phasor result = (z1 + z2) * z3 / 2.0;

    EXPECT_NEAR(result.Magnitude(), 6.7664, 0.0001);
    EXPECT_NEAR(result.PhaseDeg(), 2.1921, 0.0001);
    EXPECT_NEAR(result.Magnitude(), 6.7664, 0.0001);
    EXPECT_NEAR(result.Real(), 6.7615, 0.0001);
    EXPECT_NEAR(result.Imag(), 0.2588, 0.0001);
}

TEST(MathPhasorTest, CommutativeProperty) {
    Phasor p1(2.0, 3.0, AlgTag{});
    Phasor p2(4.0, 5.0,AlgTag{});

    EXPECT_TRUE(p1 + p2 == p2 + p1);
    EXPECT_TRUE(p1 * p2 == p2 * p1);
}

TEST(MathPhasorTest, AssociativeProperty) {
    Phasor p1(1.0, 2.0, AlgTag{});
    Phasor p2(3.0, 4.0, AlgTag{});
    Phasor p3(5.0, 6.0, AlgTag{});

    Phasor left = (p1 + p2) + p3;
    Phasor right = p1 + (p2 + p3);
    EXPECT_TRUE(left == right);

    left = (p1 * p2) * p3;
    right = p1 * (p2 * p3);
    EXPECT_TRUE(left == right);
}

TEST(MathPhasorTest, DistributiveProperty) {
    Phasor p1(1.0, 2.0, AlgTag{});
    Phasor p2(3.0, 4.0, AlgTag{});
    Phasor p3(5.0, 6.0, AlgTag{});

    Phasor left = p1 * (p2 + p3);
    Phasor right = p1 * p2 + p1 * p3;
    EXPECT_TRUE(left == right);
}

TEST(PhasorTest, SpecialAngles) {
    Phasor p1(1.0, 0.0, DegTag{});
    EXPECT_NEAR(p1.Real(), 1.0, EPS);
    EXPECT_NEAR(p1.Imag(), 0.0, EPS);

    Phasor p2(1.0, 90.0, DegTag{});
    EXPECT_NEAR(p2.Real(), 0.0, EPS);
    EXPECT_NEAR(p2.Imag(), 1.0, EPS);

    Phasor p3(1.0, 180.0, DegTag{});
    EXPECT_NEAR(p3.Real(), -1.0, EPS);
    EXPECT_NEAR(p3.Imag(), 0.0, EPS);
    EXPECT_NEAR(p3.PhaseDeg(), 180.0, EPS);

    p3 = Phasor(1.0, -180.0, DegTag{});
    EXPECT_NEAR(p3.Real(), -1.0, EPS);
    EXPECT_NEAR(p3.Imag(), 0.0, EPS);
    EXPECT_NEAR(p3.PhaseDeg(), 180.0, EPS);

    Phasor p4(1.0, -90.0, DegTag{});
    EXPECT_NEAR(p4.Real(), 0.0, EPS);
    EXPECT_NEAR(p4.Imag(), -1.0, EPS);
}

TEST(ConstPhasorTest, ConstPhasorMethods) {
    const Phasor p(5.0, 60.0, DegTag{});

    EXPECT_NEAR(p.Magnitude(), 5.0, EPS);
    EXPECT_NEAR(p.Phase(), pi / 3, EPS);
    EXPECT_NEAR(p.PhaseDeg(), 60.0, EPS);
    EXPECT_NEAR(p.Real(), 2.5, EPS);
    EXPECT_NEAR(p.Imag(), 5.0 * std::sqrt(3) / 2, EPS);

    EXPECT_NEAR(p.Abs(), 5.0, EPS);
    EXPECT_NEAR(p.Angle(), p.Phase(), EPS);
    EXPECT_NEAR(p.AngleDeg(), 60.0, EPS);
}

TEST(ConstPhasorTest, ConstPhasorComparison) {
    const Phasor p1(3.0, 45.0, DegTag{});
    const Phasor p2(3.0, 45.0, DegTag{});
    const Phasor p3(4.0, 45.0, DegTag{});

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(ConstPhasorTest, ConstPhasorUnaryOperators) {
    const Phasor p(3.0, 30.0, DegTag{});

    Phasor p2 = -p;
    EXPECT_NEAR(p2.Magnitude(), p.Magnitude(), EPS);
    EXPECT_NEAR(p2.Phase(), p.Phase() - pi, EPS);
}

TEST(ConstPhasorTest, ConstPhasorBinaryOperators) {
    const Phasor p1(2.0, 30.0, DegTag{});
    const Phasor p2(3.0, 60.0, DegTag{});

    Phasor res = p1 + p2;
    EXPECT_NEAR(res.Magnitude(), 4.8366, 0.0001);
    EXPECT_NEAR(res.Phase(), 0.8389, 0.0001);
    EXPECT_NEAR(res.PhaseDeg(), 48.0675, 0.0001);
    EXPECT_NEAR(res.Real(), 3.2321, 0.0001);
    EXPECT_NEAR(res.Imag(), 3.5981, 0.0001);

    res = p1 - p2;
    EXPECT_NEAR(res.Magnitude(), 1.6148, 0.0001);
    EXPECT_NEAR(res.Phase(), -1.4266, 0.0001);
    EXPECT_NEAR(res.PhaseDeg(), -81.7380, 0.0001);
    EXPECT_NEAR(res.Real(), 0.2321, 0.0001);
    EXPECT_NEAR(res.Imag(), -1.5981, 0.0001);

    res = p1 * p2;
    EXPECT_NEAR(res.Magnitude(), 6.0, 0.0001);
    EXPECT_NEAR(res.Phase(), 1.5708, 0.0001);
    EXPECT_NEAR(res.PhaseDeg(), 90.0000, 0.0001);
    EXPECT_NEAR(res.Real(), 0.0000, 0.0001);
    EXPECT_NEAR(res.Imag(), 6.0000, 0.0001);

    res = p1 / p2;
    EXPECT_NEAR(res.Magnitude(), 0.6667, 0.0001);
    EXPECT_NEAR(res.Phase(), -0.5236, 0.0001);
    EXPECT_NEAR(res.PhaseDeg(), -30.0000, 0.0001);
    EXPECT_NEAR(res.Real(), 0.5774, 0.0001);
    EXPECT_NEAR(res.Imag(), -0.3333, 0.0001);

    Phasor p3 = p1 + 2.0;
    Phasor p4 = 2.0 + p1;
    Phasor p5 = p1 * 2.0;
    Phasor p6 = 2.0 * p1;

    EXPECT_TRUE(p3 == p4);
    EXPECT_TRUE(p5 == p6);
}

TEST(ConstPhasorTest, ConstPhasorSpecialMethods) {
    const Phasor p(4.0, 45.0, DegTag{});

    Phasor conj = p.Conj();
    EXPECT_NEAR(conj.Real(), p.Real(), EPS);
    EXPECT_NEAR(conj.Imag(), -p.Imag(), EPS);

    Phasor inv = p.Inv();
    EXPECT_NEAR(inv.Magnitude(), 1.0/p.Magnitude(), EPS);
    EXPECT_NEAR(inv.Phase(), -p.Phase(), EPS);
}

TEST(ConstPhasorTest, ConstPhasorInExpression) {
    const Phasor a(3.0, 0.0, DegTag{});
    const Phasor b(4.0, 90.0, DegTag{});

    Phasor result = (a * a.Conj() + b * b.Conj()) / 2.0;

    EXPECT_NEAR(result.Magnitude(), 12.5, EPS);
    EXPECT_NEAR(result.Phase(), 0.0, EPS);
}

TEST(ConstPhasorTest, ConstPhasorVectorOperations) {
    const Phasor phasors[] = {
        Phasor(1.0, 0.0, DegTag{}),
        Phasor(1.0, 90.0, DegTag{}),
        Phasor(1.0, 180.0, DegTag{}),
        Phasor(1.0, 270.0, DegTag{})
    };
    Phasor sum;
    for (const auto& p : phasors) {
        sum += p;
    }
    EXPECT_NEAR(sum.Magnitude(), 0.0, EPS);
}

TEST(ConstPhasorTest, ConstPhasorOutput) {
    const Phasor p(2.5, 30.0, DegTag{});
    std::stringstream ss;

    ss << p;

    std::string output = ss.str();
    EXPECT_TRUE(output.find("2.500") != std::string::npos);
    EXPECT_TRUE(output.find("30.000") != std::string::npos);
}

TEST(ConstPhasorTest, ConstPhasorAssignmentFromConst) {
    const Phasor source(10.0, 45.0, DegTag{});
    Phasor target;

    target = source;

    EXPECT_TRUE(target == source);
    EXPECT_NEAR(target.Magnitude(), 10.0, EPS);
    EXPECT_NEAR(target.PhaseDeg(), 45.0, EPS);
}

TEST(ConstPhasorTest, MixedConstAndNonConst) {
    const Phasor cp(3.0, 60.0, DegTag{});
    Phasor ncp(4.0, 30.0, DegTag{});

    Phasor sum1 = cp + ncp;
    Phasor sum2 = ncp + cp;

    EXPECT_TRUE(sum1 == sum2);

    Phasor prod1 = cp * ncp;
    Phasor prod2 = ncp * cp;

    EXPECT_TRUE(prod1 == prod2);

    ncp += cp;
    ncp -= cp;
    ncp *= cp;
    ncp /= cp;

    EXPECT_NEAR(ncp.Magnitude(), 4.0, EPS);
    EXPECT_NEAR(ncp.PhaseDeg(), 30.0, EPS);
}

TEST(ConstPhasorTest, ConstPhasorChainOperations) {
    const Phasor a(2.0, 0.0, DegTag{});
    const Phasor b(3.0, 90.0, DegTag{});
    const Phasor c(4.0, 180.0, DegTag{});

    Phasor result = a.Conj() * b + c / a - b.Inv();
    EXPECT_TRUE(result.Magnitude() >= 0.0);

    result = (a + b) * c.Conj() / 2.0;
    EXPECT_TRUE(result.Magnitude() >= 0.0);
}
