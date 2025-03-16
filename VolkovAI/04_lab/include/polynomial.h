#pragma once
#include <iostream>
#include <stdexcept> // для std::invalid_argument
#include "ring_head_list.h"
#include "monomial.h"

class polynomial {
private:
    std::string name;
    RingHeadList<Monomial> pol;

public:
    polynomial() = default;
    polynomial(const std::string& str) { parseFromString(str); }
    polynomial(const polynomial& p) : name(p.name), pol(p.pol) {}

    void parseFromString(const std::string& str) {
        pol.clear();
        name.clear();
        if (str.empty()) {
            return;
        }
        std::string strWithoutSpaces;
        for (char ch : str) {
            if (ch != ' ') {
                strWithoutSpaces += ch;
            }
        }
        size_t pos = 0;
        while (pos < strWithoutSpaces.size()) {
            size_t nextPos = strWithoutSpaces.find_first_of("+-", pos + 1);
            nextPos = (nextPos > strWithoutSpaces.size()) ? strWithoutSpaces.size() : nextPos;
            std::string token = strWithoutSpaces.substr(pos, nextPos - pos); // получает подстроку
            char sign = (pos > 0 && (strWithoutSpaces[pos - 1] == '+' || strWithoutSpaces[pos - 1] == '-'))
                ? strWithoutSpaces[pos - 1]
                : '+';
            Monomial monomial = parseMonomial(token, sign);
            if (monomial.getCoeff() != 0) {
                pol.push_back(monomial);
            }
            pos = nextPos;
        }
        updateName();
    }

    Monomial parseMonomial(const std::string& token, char sign) {
        double coeff = 1.0;
        int xDegree = 0, yDegree = 0, zDegree = 0;
        size_t pos = 0;

        if (pos < token.size() && (token[pos] == '+' || token[pos] == '-')) {
            sign = token[pos];
            pos++;
        }

        if (pos < token.size() && (isdigit(token[pos]) || token[pos] == '.')) {
            size_t coeffEnd = token.find_first_not_of("0123456789.", pos);
            if (coeffEnd == std::string::npos) {
                coeffEnd = token.size();
            }
            try {
                coeff = std::stod(token.substr(pos, coeffEnd - pos));
            }
            catch (const std::invalid_argument& e) {
                throw "Invalid coefficient in monomial";
            }
            pos = coeffEnd;
        }

        if (sign == '-') {
            coeff = -coeff;
        }

        while (pos < token.size()) {
            if (token[pos] == 'x' || token[pos] == 'y' || token[pos] == 'z') {
                char var = token[pos];
                pos++;

                if (pos < token.size() && token[pos] == '^') {
                    pos++;
                    size_t degreeEnd = token.find_first_not_of("0123456789", pos);
                    if (degreeEnd == std::string::npos) {
                        degreeEnd = token.size();
                    }
                    try {
                        int degree = std::stoi(token.substr(pos, degreeEnd - pos));
                        pos = degreeEnd;

                        if (var == 'x') {
                            xDegree = degree;
                        }
                        else if (var == 'y') {
                            yDegree = degree;
                        }
                        else if (var == 'z') {
                            zDegree = degree;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        throw "Invalid degree in monomial";
                    }
                }
                else {
                    if (var == 'x') {
                        xDegree = 1;
                    }
                    else if (var == 'y') {
                        yDegree = 1;
                    }
                    else if (var == 'z') {
                        zDegree = 1;
                    }
                }
            }
            else {
                pos++;
            }
        }

        int degree = 100 * xDegree + 10 * yDegree + zDegree;
        return Monomial(degree, coeff);
    }

    void updateName() {
        name.clear();
        if (pol.get_pHead() == nullptr) {
            return;
        }

        TNode<Monomial>* node = pol.get_pHead()->pNext;

        while (node != pol.get_pHead()) {
            std::string monomialStr = node->value.monomial_handling(node->value);
            name += monomialStr;
            node = node->pNext;
        }

        if (!name.empty() && name[0] == '+') {
            name.erase(0, 1);
        }
    }

    polynomial operator+(const polynomial& p) const {
        polynomial result;

        if (pol.get_pHead() == nullptr || p.pol.get_pHead() == nullptr) {
            return result;
        }

        TNode<Monomial>* iter1 = pol.get_pHead()->pNext;
        TNode<Monomial>* iter2 = p.pol.get_pHead()->pNext;

        while (iter1 != pol.get_pHead() && iter2 != p.pol.get_pHead()) {
            if (iter1->value < iter2->value) {
                result.pol.push_back(iter1->value);
                iter1 = iter1->pNext;
            }
            else if (iter1->value > iter2->value) {
                result.pol.push_back(iter2->value);
                iter2 = iter2->pNext;
            }
            else {
                Monomial sum = iter1->value + iter2->value;
                if (sum.getCoeff() != 0) {
                    result.pol.push_back(sum);
                }
                iter1 = iter1->pNext;
                iter2 = iter2->pNext;
            }
        }

        while (iter1 != pol.get_pHead()) {
            result.pol.push_back(iter1->value);
            iter1 = iter1->pNext;
        }

        while (iter2 != p.pol.get_pHead()) {
            result.pol.push_back(iter2->value);
            iter2 = iter2->pNext;
        }

        result.updateName();
        return result;
    }

    polynomial operator-(const polynomial& p) const {
        return *this + (p * -1.0);
    }

    polynomial operator*(const polynomial& p) const {
        polynomial result;
        auto iter1 = this->pol.get_pHead()->pNext;

        while (iter1 != this->pol.get_pHead()) {
            auto iter2 = p.pol.get_pHead()->pNext;

            while (iter2 != p.pol.get_pHead()) {
                Monomial product = iter1->value * iter2->value;

                if (product.getCoeff() != 0) {
                    TNode<Monomial>* found = result.pol.get_pHead()->pNext;
                    while (found != result.pol.get_pHead() && found->value.getDegree() != product.getDegree()) {
                        found = found->pNext;
                    }

                    if (found != result.pol.get_pHead()) {
                        found->value = Monomial(product.getDegree(), found->value.getCoeff() + product.getCoeff());
                    }
                    else {
                        result.pol.push_back(product);
                    }
                }

                iter2 = iter2->pNext;
            }

            iter1 = iter1->pNext;
        }

        result.updateName();
        return result;
    }

    double operator()(double x, double y, double z) const {
        double result = 0.0;
        TNode<Monomial>* temp = pol.get_pHead()->pNext;

        while (temp != pol.get_pHead()) {
            result += temp->value.count(x, y, z);
            temp = temp->pNext;
        }

        return result;
    }

    polynomial operator+(double c) const {
        polynomial result(*this);
        TNode<Monomial>* iter = result.pol.get_pHead()->pNext;
        bool foundZeroDegree = false;

        while (iter != result.pol.get_pHead()) {
            if (iter->value.getDegree() == 0) {
                iter->value = iter->value + c;
                foundZeroDegree = true;
                break;
            }
            iter = iter->pNext;
        }

        if (!foundZeroDegree) {
            result.pol.push_back(Monomial(0, c));
        }

        result.updateName();
        return result;
    }

    polynomial operator-(double c) const {
        return *this + (-c);
    }

    polynomial operator*(double c) const {
        polynomial result;
        TNode<Monomial>* iter = pol.get_pHead()->pNext;
        while (iter != pol.get_pHead()) {
            result.pol.push_back(iter->value * c);
            iter = iter->pNext;
        }
        result.updateName();
        return result;
    }

    bool operator==(const polynomial& p) const {
        if (pol.get_pHead() == nullptr || p.pol.get_pHead() == nullptr) {
            return false;
        }
        TNode<Monomial>* iter1 = pol.get_pHead()->pNext;
        TNode<Monomial>* iter2 = p.pol.get_pHead()->pNext;
        while (iter1 != pol.get_pHead() && iter2 != p.pol.get_pHead()) {
            if (iter1->value != iter2->value) return false;
            iter1 = iter1->pNext;
            iter2 = iter2->pNext;
        }
        return iter1 == pol.get_pHead() && iter2 == p.pol.get_pHead();
    }

    bool operator!=(const polynomial& p) const {
        return !(*this == p);
    }

    friend std::ostream& operator<<(std::ostream& out, const polynomial& p) {
        out << p.name;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, polynomial& p) {
        std::string strpolinomial;
        if (std::getline(in, strpolinomial)) {
            p = polynomial(strpolinomial);
        }
        return in;
    }
};