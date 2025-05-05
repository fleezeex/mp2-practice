#pragma once
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "ring_head_list.h"

class Monomial {
protected:
    int degree;
    double coeff;

public:
    Monomial();
    Monomial(int deg, double coef);
    Monomial(const Monomial& m);

    int getDegree() const;
    double getCoeff() const;

    Monomial operator+(const Monomial& m) const;
    Monomial operator-(const Monomial& m) const;
    Monomial operator*(const Monomial& m) const;
    Monomial operator+(double val) const;
    Monomial operator-(double val) const;
    Monomial operator*(double val) const;

    std::string monomial_handling(const Monomial& m) const;
    double count(double x, double y, double z) const;

    Monomial& operator=(const Monomial& m);

    bool operator==(double c) const;
    bool operator!=(double c) const;
    bool operator==(const Monomial& m) const;
    bool operator!=(const Monomial& m) const;
    bool operator>(const Monomial& m) const;
    bool operator>=(const Monomial& m) const;
    bool operator<(const Monomial& m) const;
    bool operator<=(const Monomial& m) const;
};