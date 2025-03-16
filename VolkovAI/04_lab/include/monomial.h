#pragma once
#include <sstream>
#include "ring_head_list.h"

class Monomial {
protected:
    int degree;
    double coeff;

public:
    Monomial() {
        degree = -1;
        coeff = 0;
    }

    Monomial(int deg, double coef) {
        coeff = coef;
        degree = deg;
    }

    Monomial(const Monomial& m) {
        coeff = m.coeff;
        degree = m.degree;
    }

    int getDegree() const {
        return degree;
    }

    double getCoeff() const {
        return coeff;
    }

    Monomial operator+ (const Monomial& m) const {
        if (degree == m.degree) {
            return Monomial(degree, coeff + m.coeff);
        }
        else {
            throw "Selected monomial has a different degree.";
        }
    }

    Monomial operator- (const Monomial& m) const {
        if (degree == m.degree) {
            return Monomial(degree, coeff - m.coeff);
        }
        else {
            throw "Selected monomial has a different degree.";
        }
    }

    Monomial operator*(const Monomial& m) const {
        if (coeff == 0 || m.coeff == 0) {
            return Monomial(0, 0);
        }
        return Monomial(degree + m.degree, coeff * m.coeff);
    }

    Monomial operator+ (double val) const {
        if (degree == 0) {
            return Monomial(degree, coeff + val);
        }
        else {
            throw "Selected monomial has a not-zero degree.";
        }
    }

    Monomial operator- (double val) const {
        if (degree == 0) {
            return Monomial(degree, coeff - val);
        }
        else {
            throw "Selected monomial has a not-zero degree.";
        }
    }

    Monomial operator*(double val) const {
        return Monomial(degree, coeff * val);
    }

    std::string monomial_handling(const Monomial& m) const {
        if (m.getCoeff() == 0) {
            return "";
        }

        std::string answ;
        double coeff = m.getCoeff();

        if (coeff > 0) {
            answ += "+";
        }
        else {
            answ += "-";
        }
        if (std::abs(coeff) != 1) {
            if (coeff == static_cast<int>(coeff)) {
                answ += std::to_string(static_cast<int>(std::abs(coeff)));
            }
            else {
                answ += std::to_string(std::abs(coeff));
            }
        }

        int xDegree = m.getDegree() / 100;
        int yDegree = (m.getDegree() / 10) % 10;
        int zDegree = m.getDegree() % 10;

        if (xDegree > 0) {
            answ += "x";
            if (xDegree > 1) {
                answ += "^" + std::to_string(xDegree);
            }
        }

        if (yDegree > 0) {
            answ += "y";
            if (yDegree > 1) {
                answ += "^" + std::to_string(yDegree);
            }
        }

        if (zDegree > 0) {
            answ += "z";
            if (zDegree > 1) {
                answ += "^" + std::to_string(zDegree);
            }
        }

        return answ;
    }

    double count(double x, double y, double z) const {
        double result = coeff;
        int xDegree = degree / 100;
        int yDegree = (degree / 10) % 10;
        int zDegree = degree % 10;

        if (xDegree > 0) result *= std::pow(x, xDegree);
        if (yDegree > 0) result *= std::pow(y, yDegree);
        if (zDegree > 0) result *= std::pow(z, zDegree);

        return result;
    }

    Monomial& operator=(const Monomial& m) {
        if (this != &m) {
            coeff = m.coeff;
            degree = m.degree;
        }
        return *this;
    }

    bool operator==(double c) const { return std::abs(coeff - c) <= 1e-6; }
    bool operator!=(double c) const { return !(*this == c); }

    bool operator==(const Monomial& m) const { return coeff == m.coeff && degree == m.degree; }
    bool operator!=(const Monomial& m) const { return !(*this == m); }
    bool operator>(const Monomial& m) const { return degree > m.degree; }
    bool operator>=(const Monomial& m) const { return degree >= m.degree; }
    bool operator<(const Monomial& m) const { return degree < m.degree; }
    bool operator<=(const Monomial& m) const { return degree <= m.degree; }
};