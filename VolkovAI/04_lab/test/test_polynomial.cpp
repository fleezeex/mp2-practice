#include <gtest.h>
#include "polynomial.h"

TEST(PolynomialTest, ParsingAndStringRepresentation) {
    polynomial p("3x^2 + 2y - 5z");
    EXPECT_EQ(p, polynomial("3x^2 + 2y - 5z"));

    polynomial p2("4x^2 - 2y + 3z");
    EXPECT_EQ(p2, polynomial("4x^2 - 2y + 3z"));

    polynomial p3("7x^2 - 2z");
    EXPECT_EQ(p3, polynomial("7x^2 - 2z"));
}

TEST(PolynomialTest, Addition) {
    polynomial p1("3x^2+2y-5z");
    polynomial p2("4x^2-2y+3z");
    polynomial result = p1 + p2;
    EXPECT_EQ(result, polynomial("7x^2-2z"));
}

TEST(PolynomialTest, Subtraction) {
    polynomial p1("3x^2 + 2y - 5z");
    polynomial p2("4x^2 - 2y + 3z");
    polynomial result = p1 - p2;
    EXPECT_EQ(result, polynomial("-x^2 + 4y - 8z"));
}

TEST(PolynomialTest, Multiplication) {
    polynomial p1("3x + 2y");
    polynomial p2("4x - 5z");
    polynomial result = p1 * p2;
    EXPECT_EQ(result, polynomial("12x^2 - 15xz + 8xy - 10yz"));
}

TEST(PolynomialTest, ScalarAddition) {
    polynomial p("3x^2 + 2y - 5z");
    polynomial result = p + 4;
    EXPECT_EQ(result, polynomial("3x^2 + 2y - 5z + 4"));
}

TEST(PolynomialTest, ScalarSubtraction) {
    polynomial p("3x^2 + 2y - 5z");
    polynomial result = p - 2;
    EXPECT_EQ(result, polynomial("3x^2 + 2y - 5z - 2"));
}

TEST(PolynomialTest, ScalarMultiplication) {
    polynomial p("3x^2 + 2y - 5z");
    polynomial result = p * 2;
    EXPECT_EQ(result, polynomial("6x^2 + 4y - 10z"));
}

TEST(PolynomialTest, Evaluation) {
    polynomial p("3x^2 + 2y - 5z");
    double result = p(2, 3, 1); 
    EXPECT_DOUBLE_EQ(result, 3 * 4 + 2 * 3 - 5 * 1); 
}

TEST(PolynomialTest, ComparisonOperators) {
    polynomial p1("3x^2 + 2y - 5z");
    polynomial p2("3x^2 + 2y - 5z");
    polynomial p3("4x^2 - 2y + 3z");

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(PolynomialTest, EdgeCases) {
    polynomial p1;
    polynomial p2("0");
    EXPECT_EQ(p1, p2);

    polynomial p3("x + y + z");
    polynomial p4("-x - y - z");
    polynomial result = p3 + p4;
    EXPECT_EQ(result, polynomial("0"));
}