#include <gtest.h>
#include "monomial.h"

TEST(MonomialTest, ConstructorAndGetters) {
    Monomial m(123, 5.0);
    EXPECT_EQ(m.getDegree(), 123);
    EXPECT_EQ(m.getCoeff(), 5.0);
}

TEST(MonomialTest, Addition) {
    Monomial m1(123, 3.0);
    Monomial m2(123, 2.0);
    Monomial result = m1 + m2;
    EXPECT_EQ(result.getDegree(), 123);
    EXPECT_EQ(result.getCoeff(), 5.0);
}
TEST(MonomialTest, Subtraction) {
    Monomial m1(123, 5.0);
    Monomial m2(123, 2.0);
    Monomial result = m1 - m2;
    EXPECT_EQ(result.getDegree(), 123);
    EXPECT_EQ(result.getCoeff(), 3.0);
}

TEST(MonomialTest, Multiplication) {
    Monomial m1(123, 3);
    Monomial m2(123, 2);
    Monomial result = m1 * m2;
    EXPECT_EQ(result.getDegree(), 246);
    EXPECT_EQ(result.getCoeff(), 6.0);
}

TEST(MonomialTest, AddConstant) {
    Monomial m(0, 3); // m = 3
    Monomial result = m + 2.0; // 3 + 2
    EXPECT_EQ(result.getDegree(), 0);
    EXPECT_EQ(result.getCoeff(), 5.0);
}

TEST(MonomialTest, SubtractConstant) {
    Monomial m(0, 5.0); // m = 5
    Monomial result = m - 2.0; // 5 - 2
    EXPECT_EQ(result.getDegree(), 0);
    EXPECT_EQ(result.getCoeff(), 3.0);
}

TEST(MonomialTest, MultiplyByConstant) {
    Monomial m(0, 3); // m = 3
    Monomial result = m * 2.0; // 3 * 2
    EXPECT_EQ(result.getDegree(), 0);
    EXPECT_EQ(result.getCoeff(), 6.0);
}

TEST(MonomialTest, MonomialHandling) {
    Monomial m2(321, -1);
    EXPECT_EQ(m2.monomial_handling(m2), "-x^3y^2z");

    Monomial m3(0, 0);
    EXPECT_EQ(m3.monomial_handling(m3), "");
}

TEST(MonomialTest, Count) {
    Monomial m(321, 3); // 3 * x^3 * y^2 * z^1
    EXPECT_NEAR(m.count(2, 3.0, 4.0), 3.0 * std::pow(2.0, 3) * std::pow(3.0, 2) * std::pow(4.0, 1), 1e-6);
}

TEST(MonomialTest, CompareWithNumber) {
    Monomial m(0, 5);
    EXPECT_TRUE(m == 5);
    EXPECT_FALSE(m != 5);
    EXPECT_FALSE(m == 3);
}

TEST(MonomialTest, CompareMonomials) {
    Monomial m1(123, 5.0);
    Monomial m2(123, 5.0);
    Monomial m3(123, 3.0);
    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_TRUE(m1 != m3);
}

TEST(MonomialTest, AssignmentOperator) {
    Monomial m1(123, 5.0);
    Monomial m2;
    m2 = m1;
    EXPECT_EQ(m2.getDegree(), 123);
    EXPECT_EQ(m2.getCoeff(), 5.0);
}
