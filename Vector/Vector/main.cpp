#include <Windows.h>
#include "TVector.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int temp;
	cout << "����������, �������� ����������� �����: \n1. �������� � ����� ���������; \n2. �������� � �������� � ������; \n3. ����� ����� �������.\n";
	cin >> temp;
	if (temp == 1) {
		TVector v1, v2;
		cin >> v1 >> v2;
		cout << "�������� ��������: " << v1 + v2 << endl;
		cout << "��������� ��������: " << v1 - v2 << endl;
		cout << "��������� ������������: " << v1 * v2 << endl;
	}
	if (temp == 2) {
		TVector v1;
		double c;
		cin >> v1;
		cout << "����������, ������� �����: ";
		cin >> c;
		cout << "�������� ������� � �����: " << v1 + c << endl;
		cout << "��������� ������� � �����: " << v1 - c << endl;
		cout << "������������ ������� � �����: " << v1 * c << endl;
	}
	if (temp == 3) {
		TVector v1;
		cin >> v1;
		cout << "����� �������: " << v1.norma() << endl;
	}
}