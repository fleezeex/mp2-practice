#include <gtest.h>
#include "Polynomial.h"

TEST(PolynomialTest, ParsingAndStringRepresentation) {
    Polynomial p("3x^2 + 2y - 5z");
    EXPECT_EQ(p, Polynomial("3x^2 + 2y - 5z"));

    Polynomial p2("4x^2 - 2y + 3z");
    EXPECT_EQ(p2, Polynomial("4x^2 - 2y + 3z"));

    Polynomial p3("7x^2 - 2z");
    EXPECT_EQ(p3, Polynomial("7x^2 - 2z"));
}

TEST(PolynomialTest, Addition) {
    Polynomial p1("3x^2+2y-5z");
    Polynomial p2("4x^2-2y+3z");
    Polynomial result = p1 + p2;
    EXPECT_EQ(result, Polynomial("7x^2-2z"));
}

TEST(PolynomialTest, Subtraction) {
    Polynomial p1("3x^2 + 2y - 5z");
    Polynomial p2("4x^2 - 2y + 3z");
    Polynomial result = p1 - p2;
    EXPECT_EQ(result, Polynomial("-x^2 + 4y - 8z"));
}

TEST(PolynomialTest, Multiplication) {
    Polynomial p1("3x + 2y");
    Polynomial p2("4x - 5z");
    Polynomial result = p1 * p2;
    EXPECT_EQ(result, Polynomial("12x^2 + 8xy - 15xz  - 10yz"));
}

TEST(PolynomialTest, ScalarAddition) {
    Polynomial p("3x^2 + 2y - 5z");
    Polynomial result = p + 4;
    EXPECT_EQ(result, Polynomial("3x^2 + 2y - 5z + 4"));
}

TEST(PolynomialTest, ScalarSubtraction) {
    Polynomial p("3x^2 + 2y - 5z");
    Polynomial result = p - 2;
    EXPECT_EQ(result, Polynomial("3x^2 + 2y - 5z - 2"));
}

TEST(PolynomialTest, ScalarMultiplication) {
    Polynomial p("3x^2 + 2y - 5z");
    Polynomial result = p * 2;
    EXPECT_EQ(result, Polynomial("6x^2 + 4y - 10z"));
}

TEST(PolynomialTest, Evaluation) {
    Polynomial p("3x^2 + 2y - 5z");
    double result = p(2, 3, 1); 
    EXPECT_DOUBLE_EQ(result, 3 * 4 + 2 * 3 - 5 * 1); 
}

TEST(PolynomialTest, ComparisonOperators) {
    Polynomial p1("3x^2 + 2y - 5z");
    Polynomial p2("3x^2 + 2y - 5z");
    Polynomial p3("4x^2 - 2y + 3z");

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}