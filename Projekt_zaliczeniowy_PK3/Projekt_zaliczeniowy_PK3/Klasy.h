#pragma once
#include <iostream>
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace sf;
using namespace std;

class Element
{
protected:
	float kat_pochylenia;
	bool active;
	int pozycjaX, pozycjaY;
	int rozmiarX, rozmiarY;

public:
	Sprite obiekt;
	void zmie�_pozycj�_obiekt(int x, int y);
	int pobierz_pozycjaX();
	int pobierz_pozycjaY();
	bool aktywny();
	void ustaw_pozycj�X(int x);
	void ustaw_pozycj�Y(int Y);
	void ustaw_aktywny(bool tak);
	Sprite pobierz_obiekt();
	void pochyl_lewo();
	void pochyl_prawo();
};

/*-------Klasy dziedzicz�ce po Element-------*/

class Mebel :public Element
{
protected:
	Texture x;
public:
	int pobierz_rozmiarX();
	int pobierz_rozmiarY();
	Texture pobierz_teksture();
};

class Uzyteczne : public Element
{
protected:
	Texture x;
public:
	int pobierz_rozmiarX();
	int pobierz_rozmiarY();
	Texture pobierz_teksture();
};

/*-------Klasy dziedzicz�ce po Mebel-------*/

class Krzeslo :public Mebel
{
public:
	Krzeslo();
};

class Fotel : public Mebel
{
public:
	Fotel();
};

class Biurko : public Mebel
{
public:
	Biurko();
};

class Lozko :public Mebel
{
public:
	Lozko();
};

class Szafa : public Mebel
{
public:
	Szafa();
};

/*------Klasy dziedzicz�ce po Uzyteczne-------*/

class Kwiat : public Uzyteczne
{
public:
	Kwiat();
};

class Lampa : public Uzyteczne
{
public:
	Lampa();
};