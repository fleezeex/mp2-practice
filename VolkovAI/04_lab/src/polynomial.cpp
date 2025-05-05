#include "polynomial.h"

Polynomial::Polynomial() : name("0") {}

Polynomial::Polynomial(const std::string& str) {
    parseFromString(str);
}

Polynomial::Polynomial(const Polynomial& p) : name(p.name), poly(p.poly) {}

Monomial Polynomial::parseMonomial(const std::string& token, char sign) const {
    double coeff = 1.0;
    int xDeg = 0, yDeg = 0, zDeg = 0;
    size_t pos = 0;

    if (pos < token.size() && (token[pos] == '+' || token[pos] == '-')) {
        sign = token[pos++]; // запоминаем знак и сдвигаем позицию
    }

    if (pos < token.size() && (isdigit(token[pos]) || token[pos] == '.')) { // числовой коэффициент
        size_t coeffEnd = token.find_first_not_of("0123456789.", pos); // находим конец числа
        if (coeffEnd == std::string::npos) coeffEnd = token.size();
        coeff = std::stod(token.substr(pos, coeffEnd - pos)); // преобразуем подстроку в число
        pos = coeffEnd;
    }

    if (sign == '-') coeff = -coeff;

    // обработка переменных и  степеней
    while (pos < token.size()) {
        if (token[pos] == 'x' || token[pos] == 'y' || token[pos] == 'z') {
            char var = token[pos++];
            int deg = 1;

            if (pos < token.size() && token[pos] == '^') {
                pos++;
                size_t degEnd = token.find_first_not_of("0123456789", pos);
                if (degEnd == std::string::npos) degEnd = token.size();
                deg = std::stoi(token.substr(pos, degEnd - pos));
                pos = degEnd;
            }

            switch (var) {
            case 'x': xDeg = deg; break;
            case 'y': yDeg = deg; break;
            case 'z': zDeg = deg; break;
            }
        }
        else {
            pos++;
        }
    }

    return Monomial(100 * xDeg + 10 * yDeg + zDeg, coeff);
}

void Polynomial::simplify() {
    if (poly.isEmpty()) {
        name = "0";
        return;
    }

    // собираем все мономы в вектор
    std::vector<Monomial> monomials;
    for (poly.reset(); !poly.isEnded(); poly.next()) {
        monomials.push_back(poly.current());
    }

    // сортируем по убыванию степени
    std::sort(monomials.begin(), monomials.end(),
        [](const Monomial& a, const Monomial& b) {
            return a.getDegree() > b.getDegree();
        });

    // объединяем одинаковые мономы
    RingHeadList<Monomial> simplified;
    for (size_t i = 0; i < monomials.size(); ) {
        Monomial current = monomials[i++];
        while (i < monomials.size() && monomials[i].getDegree() == current.getDegree()) {
            current = current + monomials[i++];
        }
        if (current.getCoeff() != 0) {
            simplified.push_back(current);
        }
    }

    poly = simplified;
    updateName();
}

void Polynomial::updateName() {
    if (poly.isEmpty()) {
        name = "0";
        return;
    }

    std::stringstream ss;
    RingHeadList<Monomial> temp = poly;
    temp.reset();

    while (!temp.isEnded()) {
        ss << temp.current().monomial_handling(temp.current());
        temp.next();
    }

    name = ss.str();
    if (!name.empty() && name[0] == '+') {
        name.erase(0, 1);
    }
}

void Polynomial::parseFromString(const std::string& str) {
    poly.clear();
    if (str.empty()) {
        name = "0";
        return;
    }

    std::string strWithoutSpaces;
    for (char ch : str) {
        if (ch != ' ') strWithoutSpaces += ch; // удаляем пробелы
    }

    size_t pos = 0;
    while (pos < strWithoutSpaces.size()) {
        size_t nextPos = strWithoutSpaces.find_first_of("+-", pos + 1);
        if (nextPos == std::string::npos) nextPos = strWithoutSpaces.size(); // парсим токен

        std::string token = strWithoutSpaces.substr(pos, nextPos - pos);
        char sign = (pos > 0 && (strWithoutSpaces[pos - 1] == '+' || strWithoutSpaces[pos - 1] == '-'))
            ? strWithoutSpaces[pos - 1] : '+'; // извлекаем токен и знак

        Monomial monomial = parseMonomial(token, sign);
        if (monomial.getCoeff() != 0) {
            poly.push_back(monomial);
        } // парсим моном
        pos = nextPos;
    }

    updateName();
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
    Polynomial result;
    RingHeadList<Monomial> tempThis = poly;
    RingHeadList<Monomial> tempP = p.poly;

    tempThis.reset();
    tempP.reset();

    while (!tempThis.isEnded() && !tempP.isEnded()) {
        Monomial m1 = tempThis.current();
        Monomial m2 = tempP.current();

        if (m1 < m2) {
            result.poly.push_back(m1);
            tempThis.next();
        }
        else if (m1 > m2) {
            result.poly.push_back(m2);
            tempP.next();
        }
        else {
            Monomial sum = m1 + m2;
            if (sum.getCoeff() != 0) result.poly.push_back(sum);
            tempThis.next();
            tempP.next();
        }
    }

    while (!tempThis.isEnded()) {
        result.poly.push_back(tempThis.current());
        tempThis.next();
    }

    while (!tempP.isEnded()) {
        result.poly.push_back(tempP.current());
        tempP.next();
    }
    result.simplify();
    result.updateName();
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
    return *this + (p * -1.0);
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
    Polynomial result;
    RingHeadList<Monomial> tempThis = poly;

    tempThis.reset();
    while (!tempThis.isEnded()) {
        Monomial m1 = tempThis.current();
        RingHeadList<Monomial> tempP = p.poly;

        tempP.reset();
        while (!tempP.isEnded()) {
            Monomial m2 = tempP.current();
            Monomial product = m1 * m2;
            if (product.getCoeff() != 0) {
                result.poly.push_back(product);
            }
            tempP.next();
        }
        tempThis.next();
    }
    result.simplify();
    result.updateName();
    return result;
}

double Polynomial::operator()(double x, double y, double z) const {
    double result = 0.0;
    RingHeadList<Monomial> temp = poly;
    temp.reset();

    while (!temp.isEnded()) {
        result += temp.current().count(x, y, z);
        temp.next();
    }

    return result;
}

Polynomial Polynomial::operator+(double c) const {
    Polynomial result(*this);
    result.poly.push_back(Monomial(0, c));
    result.simplify();
    result.updateName();
    return result;
}

Polynomial Polynomial::operator-(double c) const {
    return *this + (-c);
}

Polynomial Polynomial::operator*(double c) const {
    Polynomial result;
    RingHeadList<Monomial> temp = poly;
    temp.reset();

    while (!temp.isEnded()) {
        result.poly.push_back(temp.current() * c);
        temp.next();
    }

    result.updateName();
    return result;
}

bool Polynomial::operator==(const Polynomial& p) const {
    if (poly.size() != p.poly.size()) return false;

    RingHeadList<Monomial> tempThis = poly;
    RingHeadList<Monomial> tempP = p.poly;

    tempThis.reset();
    tempP.reset();

    while (!tempThis.isEnded() && !tempP.isEnded()) {
        if (tempThis.current() != tempP.current()) return false;
        tempThis.next();
        tempP.next();
    }

    return true;
}

bool Polynomial::operator!=(const Polynomial& p) const {
    return !(*this == p);
}

std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
    out << p.name;
    return out;
}

std::istream& operator>>(std::istream& in, Polynomial& p) {
    std::string str;
    if (std::getline(in, str)) {
        p.parseFromString(str);
    }
    return in;
}