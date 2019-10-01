#pragma once
#ifndef DANE_H_
#define DANE_H_
#include <string>
#include <iostream>
#include <ostream>
using namespace std;
class Dane
{
public:
	int integer;
	double zmienno;
	int const getInt() { return this->integer; };
	double const getZmienno() { return this->zmienno; }
	Dane();
	Dane(int liczba, double ulamek) :integer(liczba), zmienno(ulamek) {};
	friend	ostream& operator <<(ostream& out, Dane& data);
};

#endif 