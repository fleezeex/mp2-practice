#include <iostream>
#include <string>
#include "polynomial.h"

void printMenu() {
    std::cout << "Введите операцию:\n";
    std::cout << "1 - Сложение полиномов\n";
    std::cout << "2 - Вычитание полиномов\n";
    std::cout << "3 - Умножение полиномов\n";
    std::cout << "4 - Подставить значения в полином\n";
    std::cout << "5 - Добавить константу к полиному\n";
    std::cout << "6 - Выход\n";
}

void handleOperation(polynomial& p1) {
    int operation;
    std::string input;

    printMenu();
    std::cin >> operation;

    while (operation != 6) {
        if (operation == 1) {
            std::cout << "Введите второй полином для сложения: ";
            std::cin.ignore(); // чтобы пропустить символ новой строки после ввода числа
            std::getline(std::cin, input);
            polynomial p2(input);
            polynomial result = p1 + p2;
            std::cout << "Результат: " << result << "\n";
        }
        else if (operation == 2) {
            std::cout << "Введите второй полином для вычитания: ";
            std::cin.ignore(); // чтобы пропустить символ новой строки после ввода числа
            std::getline(std::cin, input);
            polynomial p2(input);
            polynomial result = p1 - p2;
            std::cout << "Результат: " << result << "\n";
        }
        else if (operation == 3) {
            std::cout << "Введите второй полином для умножения: ";
            std::cin.ignore(); // чтобы пропустить символ новой строки после ввода числа
            std::getline(std::cin, input);
            polynomial p2(input);
            polynomial result = p1 * p2;
            std::cout << "Результат: " << result << "\n";
        }
        else if (operation == 4) {
            double x, y, z;
            std::cout << "Введите значение для x, y, z: ";
            std::cin >> x >> y >> z;
            double result = p1(x, y, z);
            std::cout << "Результат: " << result << "\n";
        }
        else if (operation == 5) {
            double constant;
            std::cout << "Введите константу для добавления: ";
            std::cin >> constant;
            polynomial result = p1 + constant;
            std::cout << "Результат: " << result << "\n";
        }
        else {
            std::cout << "Неверная операция. Попробуйте снова.\n";
        }

        printMenu();
        std::cin >> operation;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string input;
    std::cout << "Введите первый полином: ";
    //std::cin.ignore(); // чтобы пропустить символ новой строки после ввода числа
    std::getline(std::cin, input);
    polynomial p1(input);

    handleOperation(p1);

    return 0;
}
