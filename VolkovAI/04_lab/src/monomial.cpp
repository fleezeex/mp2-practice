#include "monomial.h"

Monomial::Monomial() {
    degree = -1;
    coeff = 0;
}

Monomial::Monomial(int deg, double coef) {
    coeff = coef;
    degree = deg;
}

Monomial::Monomial(const Monomial& m) {
    coeff = m.coeff;
    degree = m.degree;
}

int Monomial::getDegree() const {
    return degree;
}

double Monomial::getCoeff() const {
    return coeff;
}

Monomial Monomial::operator+(const Monomial& m) const {
    if (degree == m.degree) {
        return Monomial(degree, coeff + m.coeff);
    }
    else {
        throw "Selected monomial has a different degree.";
    }
}

Monomial Monomial::operator-(const Monomial& m) const {
    if (degree == m.degree) {
        return Monomial(degree, coeff - m.coeff);
    }
    else {
        throw "Selected monomial has a different degree.";
    }
}

Monomial Monomial::operator*(const Monomial& m) const {
    if (coeff == 0 || m.coeff == 0) {
        return Monomial(0, 0);
    }
    return Monomial(degree + m.degree, coeff * m.coeff);
}

Monomial Monomial::operator+(double val) const {
    if (degree == 0) {
        return Monomial(degree, coeff + val);
    }
    else {
        throw "Selected monomial has a not-zero degree.";
    }
}

Monomial Monomial::operator-(double val) const {
    if (degree == 0) {
        return Monomial(degree, coeff - val);
    }
    else {
        throw "Selected monomial has a not-zero degree.";
    }
}

Monomial Monomial::operator*(double val) const {
    return Monomial(degree, coeff * val);
}

std::string Monomial::monomial_handling(const Monomial& m) const {
    if (m.getCoeff() == 0) return "";

    std::stringstream ss;
    double coeff = m.getCoeff();
    int degree = m.getDegree();

    // знак
    if (coeff > 0) ss << "+";
    else ss << "-";

    // коэффициент (не выводим для 1/-1, если это не константа)
    if (std::abs(coeff) != 1 || degree == 0) {
        ss << std::abs(coeff);
    }
    if (degree != 0) {
        int xDeg = degree / 100;
        int yDeg = (degree / 10) % 10;
        int zDeg = degree % 10;
        if (xDeg == 1) ss << "x";
        else if (xDeg > 0) ss << "x^" << xDeg;
        if (yDeg == 1) ss << "y";
        else if (yDeg > 0) ss << "y^" << yDeg;
        if (zDeg == 1) ss << "z";
        else if (zDeg > 0) ss << "z^" << zDeg;
    }
    else {
        // для константы (degree = 0) выводим только коэффициент, если он не ±1
        if (std::abs(coeff) == 1) {
            ss.str("");  // сброс буфера
            ss << (coeff > 0 ? "+" : "-") << "1";
        }
    }

    return ss.str();
}

double Monomial::count(double x, double y, double z) const {
    double result = coeff;
    int xDegree = degree / 100;
    int yDegree = (degree / 10) % 10;
    int zDegree = degree % 10;

    if (xDegree > 0) result *= std::pow(x, xDegree);
    if (yDegree > 0) result *= std::pow(y, yDegree);
    if (zDegree > 0) result *= std::pow(z, zDegree);

    return result;
}

Monomial& Monomial::operator=(const Monomial& m) {
    if (this != &m) {
        coeff = m.coeff;
        degree = m.degree;
    }
    return *this;
}

bool Monomial::operator==(double c) const { return std::abs(coeff - c) <= 1e-6; }
bool Monomial::operator!=(double c) const { return !(*this == c); }

bool Monomial::operator==(const Monomial& m) const { return coeff == m.coeff && degree == m.degree; }
bool Monomial::operator!=(const Monomial& m) const { return !(*this == m); }
bool Monomial::operator>(const Monomial& m) const { return degree > m.degree; }
bool Monomial::operator>=(const Monomial& m) const { return degree >= m.degree; }
bool Monomial::operator<(const Monomial& m) const { return degree < m.degree; }
bool Monomial::operator<=(const Monomial& m) const { return degree <= m.degree; }