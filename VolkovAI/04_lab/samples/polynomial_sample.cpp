#include "polynomial.h"
#include <iostream>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMenu(const Polynomial& p) {
    std::cout << "\n=== Текущий полином: " << p << " ===\n"
        << "1 - Сложить с полиномом\n"
        << "2 - Вычесть полином\n"
        << "3 - Умножить на полином\n"
        << "4 - Вычислить в точке\n"
        << "5 - Сложить с константой\n"
        << "6 - Вычесть константу\n"
        << "7 - Умножить на константу\n"
        << "8 - Изменить полином\n"
        << "9 - Выход\n"
        << "Выберите операцию: ";
}

void handleOperations() {
    std::string input;
    std::cout << "Введите начальный полином: ";
    std::getline(std::cin, input);
    Polynomial p(input);

    while (true) {
        printMenu(p);
        int choice;
        std::cin >> choice;
        clearInput();

        switch (choice) {
        case 1: {
            std::cout << "Введите полином: ";
            std::getline(std::cin, input);
            p = p + Polynomial(input);
            break;
        }
        case 2: {
            std::cout << "Введите полином: ";
            std::getline(std::cin, input);
            p = p - Polynomial(input);
            break;
        }
        case 3: {
            std::cout << "Введите полином: ";
            std::getline(std::cin, input);
            p = p * Polynomial(input);
            break;
        }
        case 4: {
            double x, y, z;
            std::cout << "Введите x y z: ";
            std::cin >> x >> y >> z;
            clearInput();
            std::cout << "Результат: " << p(x, y, z) << "\n";
            continue;
        }
        case 5: {
            double c;
            std::cout << "Введите константу: ";
            std::cin >> c;
            clearInput();
            p = p + c;
            break;
        }
        case 6: {
            double c;
            std::cout << "Введите константу: ";
            std::cin >> c;
            clearInput();
            p = p - c;
            break;
        }
        case 7: {
            double c;
            std::cout << "Введите константу: ";
            std::cin >> c;
            clearInput();
            p = p * c;
            break;
        }
        case 8: {
            std::cout << "Введите новый полином: ";
            std::getline(std::cin, input);
            p = Polynomial(input);
            break;
        }
        case 9:
            return;
        default:
            std::cout << "Неверная операция!\n";
            continue;
        }
        std::cout << "Результат: " << p << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    handleOperations();
    std::cout << "Программа завершена.\n";
    return 0;
}