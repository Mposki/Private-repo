#include "Nag³ówek.h"

Dane::Dane()
{
	this->zmienno = 0.0;
	this->integer = 0;
}

ostream& operator <<(ostream& out, Dane &data)
{
	out << "int: " << data.getInt() << " double: " << data.getZmienno() << endl;
	return out;
}