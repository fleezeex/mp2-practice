#include <Windows.h>
#include "TVector.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int temp;
	cout << "Пожалуйста, выберите необходимый пункт: \n1. Действия с двумя векторами; \n2. Действие с вектором и числом; \n3. Найти норму вектора.\n";
	cin >> temp;
	if (temp == 1) {
		TVector v1, v2;
		cin >> v1 >> v2;
		cout << "Сложение векторов: " << v1 + v2 << endl;
		cout << "Вычитание векторов: " << v1 - v2 << endl;
		cout << "Скалярное произведение: " << v1 * v2 << endl;
	}
	if (temp == 2) {
		TVector v1;
		double c;
		cin >> v1;
		cout << "Пожалуйста, введите число: ";
		cin >> c;
		cout << "Сложение вектора и числа: " << v1 + c << endl;
		cout << "Вычитание вектора и числа: " << v1 - c << endl;
		cout << "Произведение вектора и числа: " << v1 * c << endl;
	}
	if (temp == 3) {
		TVector v1;
		cin >> v1;
		cout << "Норма вектора: " << v1.norma() << endl;
	}
}