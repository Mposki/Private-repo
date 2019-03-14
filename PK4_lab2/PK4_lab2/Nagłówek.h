#pragma once
#include <iostream>
using namespace std;

class awaria_samochodu
{
private:
	int nr_polisy;
public:
	awaria_samochodu();
	virtual ~awaria_samochodu();
	void naprawa();
	awaria_samochodu(int nr_polisy) : nr_polisy(nr_polisy) {};
};

class awaria_silnika : public awaria_samochodu
{
private:
	int nr_seryjny;
public:
	awaria_silnika();
	virtual ~awaria_silnika();
	void naprawa();
	awaria_silnika(int nr_polisy, int nr_seryjny) : nr_seryjny(nr_seryjny), awaria_samochodu(nr_polisy) {};
};

class awaria_swiecy : public awaria_silnika
{
private:
	int rozmiar_klucza;
public:
	awaria_swiecy();
	virtual ~awaria_swiecy();
	void naprawa();
	awaria_swiecy(int nr_polisy, int nr_seryjny, int rozmiar_klucza) : rozmiar_klucza(rozmiar_klucza), awaria_silnika(nr_polisy, nr_seryjny) {};
};

