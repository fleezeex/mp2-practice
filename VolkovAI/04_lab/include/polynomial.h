#pragma once
#include <iostream>
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
                // проверяем есть ли уже такой моном в списке
                TNode<Monomial>* node = pol.get_pHead()->pNext;
                bool found = false;
                while (node != pol.get_pHead()) {
                    if (node->value.getDegree() == monomial.getDegree()) {
                        node->value = node->value + monomial;
                        found = true;
                        break;
                    }
                    node = node->pNext;
                }
                if (!found) {
                    pol.push_back(monomial); // не нашли - добавляем новый моном
                }
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
        if (pol.isEmpty()) {
            return;
        }

        pol.reset();
        while (!pol.isEnded()) {
            Monomial currentMonomial = pol.current();
            std::string monomialStr = currentMonomial.monomial_handling(currentMonomial);
            name += monomialStr;
            pol.next();
        }

        if (!name.empty() && name[0] == '+') {
            name.erase(0, 1);
        }
    }

    polynomial operator+(const polynomial& p) const {
        polynomial result;

        if (pol.isEmpty() || p.pol.isEmpty()) {
            return result;
        }

        pol.reset();
        p.pol.reset();

        while (!pol.isEnded() && !p.pol.isEnded()) {
            Monomial monomial1 = pol.current();
            Monomial monomial2 = p.pol.current();

            if (monomial1 < monomial2) {
                result.pol.push_back(monomial1);
                pol.next();
            }
            else if (monomial1 > monomial2) {
                result.pol.push_back(monomial2);
                p.pol.next();
            }
            else {
                Monomial sum = monomial1 + monomial2;
                if (sum.getCoeff() != 0) {
                    result.pol.push_back(sum);
                }
                pol.next();
                p.pol.next();
            }
        }

        while (!pol.isEnded()) {
            result.pol.push_back(pol.current());
            pol.next();
        }

        while (!p.pol.isEnded()) {
            result.pol.push_back(p.pol.current());
            p.pol.next();
        }

        result.updateName();
        return result;
    }

    polynomial operator-(const polynomial& p) const {
        return *this + (p * -1.0);
    }

    polynomial operator*(const polynomial& p) const {
        polynomial result;

        this->pol.reset();
        while (!this->pol.isEnded()) {
            Monomial monomial1 = this->pol.current();
            p.pol.reset();
            while (!p.pol.isEnded()) {
                Monomial monomial2 = p.pol.current();
                Monomial product = monomial1 * monomial2;

                if (product.getCoeff() != 0) {
                    bool found = false;
                    result.pol.reset();
                    while (!result.pol.isEnded()) {
                        Monomial& current = result.pol.current();
                        if (current.getDegree() == product.getDegree()) {
                            current = current + product;
                            found = true;
                            break;
                        }
                        result.pol.next();
                    }
                    if (!found) {
                        result.pol.push_back(product);
                    }
                }
                p.pol.next();
            }
            this->pol.next();
        }

        result.updateName();
        return result;
    }

    double operator()(double x, double y, double z) const {
        double result = 0.0;
        pol.reset();
        while (!pol.isEnded()) {
            result += pol.current().count(x, y, z);
            pol.next();
        }
        return result;
    }

    polynomial operator+(double c) const {
        polynomial result(*this);
        bool foundZeroDegree = false;

        result.pol.reset();
        while (!result.pol.isEnded()) {
            if (result.pol.current().getDegree() == 0) {
                Monomial newMonomial = result.pol.current() + c;
                result.pol.current() = newMonomial;
                foundZeroDegree = true;
                break;
            }
            result.pol.next();
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
        pol.reset();
        while (!pol.isEnded()) {
            result.pol.push_back(pol.current() * c);
            pol.next();
        }
        result.updateName();
        return result;
    }

    bool operator==(const polynomial& p) const {
        if (pol.isEmpty() || p.pol.isEmpty()) {
            return false;
        }

        pol.reset();
        p.pol.reset();

        while (!pol.isEnded() && !p.pol.isEnded()) {
            if (pol.current() != p.pol.current()) {
                return false;
            }
            pol.next();
            p.pol.next();
        }

        return pol.isEnded() && p.pol.isEnded();
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