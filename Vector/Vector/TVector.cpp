#include "TVector.h"
#include "math.h"

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
	delete [] this->x;
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
		res = this->x[i] + Temp;
	}
	return res;
}

TVector TVector::operator - (double Temp) {
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res = this->x[i] - Temp;
	}
	return res;
}

TVector TVector::operator * (double Temp) {
	TVector res(this->n);
	for (int i = 0; i < this->n; i++) {
		res = this->x[i] * Temp;
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

friend std::istream& operator >> (istream&, TVector&);
friend std::ostream& operator << (ostream&, TVector&);