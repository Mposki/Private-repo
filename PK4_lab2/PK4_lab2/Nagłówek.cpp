#include <iostream>
#include "Nag³ówek.h"
using namespace std;

//------awaria_samochodu
awaria_samochodu::awaria_samochodu()
{
}

awaria_samochodu::~awaria_samochodu()
{
}

void awaria_samochodu::naprawa()
{
	cout << "Numer polisy ubezpieczenia: " << this->nr_polisy << endl;
}

//--------awaria_silnika
awaria_silnika::awaria_silnika()
{
}

awaria_silnika::~awaria_silnika()
{
}

void awaria_silnika::naprawa()
{
	awaria_samochodu::naprawa();
	cout << "Numer seryjny: " << this->nr_seryjny << endl;
}

//------awaria_swiecy
awaria_swiecy::awaria_swiecy()
{
}

awaria_swiecy::~awaria_swiecy()
{
}

void awaria_swiecy::naprawa()
{
	awaria_silnika::naprawa();
	cout << "Rozmiar: " << this->rozmiar_klucza << endl;
}
