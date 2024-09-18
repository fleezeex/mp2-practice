#include "TVector.h"
#include "math.h"

TVector::TVector() {
	this->n = 0;
	this->x = nullptr;
}

TVector::TVector(int size) {
	this->n = size;
	this->x = new double[n];
}

TVector::TVector(const TVector& Temp) {
	this->n = Temp.n;
	for (int i = 0; i < this->n; i++) {
		this[i] = Temp[i];
	}
}

TVector::~TVector() {
	delete[] this->x;
}

TVector TVector::operator = (const TVector& Temp) {
	if (this->n != Temp.n) {
		this->x = nullptr;
		this->x = new double[n];
	}
	for (int i = 0; i < this->n; i++) {
		this->x[i] = Temp[i];
	}
	return *this;
}

TVector TVector::operator + (const TVector& Temp) {
	if (this->n != Temp.n) {
		throw("Wrong size of vectors.");
	}
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res[i] = Temp[i] + this->x[i];
	}
	return res;
}

TVector TVector::operator - (const TVector& Temp) {
	if (this->n != Temp.n) {
		throw("Wrong size of vectors.");
	}
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res[i] = Temp[i] - this->x[i];
	}
	return res;
}

double TVector::operator * (const TVector& Temp) {
	double scalar = 0;
	if (this->n != Temp.n) {
		throw("Wrong size of vectors.");
	}
	for (int i = 0; i < this->n; i++) {
		scalar = scalar + (Temp[i] * this->x[i]);
	}
	return scalar;
}

TVector TVector::operator + (double Temp) {
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res[i] = this->x[i] + Temp;
	}
	return res;
}

TVector TVector::operator - (double Temp) {
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res[i] = this->x[i] - Temp;
	}
	return res;
}

TVector TVector::operator * (double Temp) {
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res[i] = this->x[i] * Temp;
	}
	return res;
}

double TVector::norma() const {
	double res = 0;
	for (int i = 0; i < this->n; i++) {
		res = res + (this->x[i]) * (this->x[i]);
	}
	return sqrt(res);
}

std::istream& operator >> (istream& in, TVector& Temp) {
	int n;
	std::cout << "Пожалуйста, введите размерность вектора: ";
	in >> n;
	std::cout << "Пожалуйста, введите координаты данного вектора: \n";
	if (Temp.x != nullptr) {
		delete[] Temp.x;
	}
	Temp.n = n;
	Temp.x = new double[Temp.n];
	for (int i = 0; i < n; i++) {
		in >> Temp[i];
	}
	return in;
}

std::ostream& operator << (ostream& out, const TVector& Temp) {
	for (int i = 0; i < Temp.n; i++)
	{
		out << Temp[i] << " ";
	}
	return out;
}