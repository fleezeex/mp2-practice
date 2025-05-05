#pragma once
#include "monomial.h"

class Polynomial {
private:
    std::string name;
    RingHeadList<Monomial> poly;

public:
    Polynomial();
    Polynomial(const std::string& str);
    Polynomial(const Polynomial& p);

    Polynomial operator+(const Polynomial& p) const;
    Polynomial operator-(const Polynomial& p) const;
    Polynomial operator*(const Polynomial& p) const;
    Polynomial operator+(double c) const;
    Polynomial operator-(double c) const;
    Polynomial operator*(double c) const;

    bool operator==(const Polynomial& p) const;
    bool operator!=(const Polynomial& p) const;

    double operator()(double x, double y, double z) const;


    friend std::ostream& operator<<(std::ostream& out, const Polynomial& p);
    friend std::istream& operator>>(std::istream& in, Polynomial& p);

private:
    void parseFromString(const std::string& str);
    void updateName();
    void simplify();
    Monomial parseMonomial(const std::string& token, char sign) const;
};