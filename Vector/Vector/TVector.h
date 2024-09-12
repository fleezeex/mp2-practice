#pragma once
#include <iostream>
using namespace std;

class TVector {
private:
	int n;
	double* x;
public:
	TVector(int size);
	TVector(const TVector&);
	~TVector();

	double norma() const;

	TVector operator = (const TVector&);

	TVector operator + (const TVector&);
	TVector operator - (const TVector&);
	double operator * (const TVector&);
	
	TVector operator + (const double);
	TVector operator - (const double);
	TVector operator * (const double);

	double& operator [] (const int index) { return x[index]; };
	const double& operator [] (const int index) const { return x[index]; };

	friend std::istream& operator >> (istream&, TVector&);
	friend std::ostream& operator << (ostream&, TVector&);
};

