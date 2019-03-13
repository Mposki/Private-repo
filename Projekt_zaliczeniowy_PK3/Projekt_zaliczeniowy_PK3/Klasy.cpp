#include "Klasy.h"
#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <math.h>  
using namespace sf;
using namespace std;

void Element::zmieñ_pozycjê_obiekt(int x, int y)
{
	this->pozycjaX =  pozycjaX + x;
	this->pozycjaY = pozycjaY + y;
	int calosc = kat_pochylenia;
	calosc = calosc % 360;
	//poruszanie, je¿eli zmieniony k¹t pochylenia
	if (calosc == 90 || calosc == -270) { //je¿eli k¹t pochylenia wynosi . i . to wykonaj
		if (pozycjaX < 49) 
			pozycjaX = 402 + 49 - rozmiarY;
		else if (pozycjaX > 402 + 49 - rozmiarY)
			pozycjaX = 50;
		if (pozycjaY < 49 + rozmiarX)
			pozycjaY = 352 + 49;
		else if (pozycjaY > 352 + 49)
			pozycjaY = 50 + rozmiarX;
	}
	else if (calosc == 180 || calosc == -180) {
		if (pozycjaX < 49 + rozmiarX) 
			pozycjaX = 402 + 49;
		else if (pozycjaX > 402 + 49) 
			pozycjaX = 49 + rozmiarX;
		if (pozycjaY < 49 + rozmiarY)
			pozycjaY = 352 + 49;
		else if (pozycjaY > 352 + 49) 
			pozycjaY = 49 + rozmiarY;
	}
	else if (calosc == 270 || calosc == -90) {
		if (pozycjaX < 49 + rozmiarY) 
			pozycjaX = 401 + 49;
		else if (pozycjaX > 402 + 49) 
			pozycjaX = 50 + rozmiarY;
		if (pozycjaY < 49)
			pozycjaY = 352 + 49 - rozmiarX;
		else if (pozycjaY > 352 + 49 - rozmiarX) 
			pozycjaY = 49;
	}
	else {
		if (pozycjaX < 49)
			pozycjaX = 402 + 49 - rozmiarX;
		else if (pozycjaX > 402 + 49 - rozmiarX)
			pozycjaX = 49;
		if (pozycjaY < 49)
			pozycjaY = 352 + 49 - rozmiarY;
		else if (pozycjaY > 352 + 49 - rozmiarY)
			pozycjaY = 49;
	}
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
int Element::pobierz_pozycjaX()
{
	return this->pozycjaX;
}
int Element::pobierz_pozycjaY()
{
	return this->pozycjaX;
}
bool Element::aktywny()
{
	return this->active;
}
void Element::ustaw_pozycjêX(int x)
{
	this->pozycjaX = x;
}
void Element::ustaw_pozycjêY(int y)
{
	this->pozycjaY = y;
}
void Element::ustaw_aktywny(bool tak)
{
	this->active = tak;
}
Sprite Element::pobierz_obiekt()
{
	return this->obiekt;
}
void Element::pochyl_lewo()
{
	this->obiekt.rotate(-90);
	this->kat_pochylenia += 90;

	int calosc = kat_pochylenia;
	calosc = calosc % 360;


	int x1 = floor(rozmiarY*sin(kat_pochylenia * 3.14159265 / 180));
	int x2 = floor(rozmiarX*cos(kat_pochylenia * 3.14159265 / 180));
	int y1 = floor(rozmiarY*cos(kat_pochylenia * 3.14159265 / 180));
	int y2 = floor(rozmiarX*sin(kat_pochylenia * 3.14159265 / 180));

	if (x1 < 0 && x2 > 0) { //je¿eli aktualny k¹t mieœci siê miêdzy (-90, 0) i (270, 360)
		if (pozycjaX + x1 < 50) 
			pozycjaX = 50 - x1;
		else if (pozycjaX > 402 + 48 - x2) 
			pozycjaX = 402 + 48 - x2;
	}
	else {
		if (pozycjaX + x1 + x2 < 50) 
			pozycjaX = 50 - x1 - x2;
		else if (pozycjaX > 402 + 48) 
			pozycjaX = 402 + 48;
	}

	if (y1 < 0 && y2 < 0) { //je¿eli aktualny k¹t mieœci siê miêdzy (-180, -90) i (180, 270)
		if (pozycjaY + y1 < 50) 
			pozycjaY = 50 - y1;
		else if (pozycjaY > 352 + 48 + y2) 
			pozycjaY = 352 + 48 + y2;
	}
	else {
		if (pozycjaY < 50) 
			pozycjaY = 50;
		else if (pozycjaY > 352 + 48 + y2 - y1)
			pozycjaY = 352 + 48 + y2 - y1;
	}
	obiekt.setPosition(this->pozycjaY, this->pozycjaY);
}
void Element::pochyl_prawo()
{
	this->obiekt.rotate(90);
	this->kat_pochylenia -= 90;

	int x1 = floor(rozmiarY*sin(kat_pochylenia* 3.14159265 / 180));
	int x2 = floor(rozmiarX*cos(kat_pochylenia* 3.14159265 / 180));
	int y1 = floor(rozmiarY*cos(kat_pochylenia* 3.14159265 / 180));
	int y2 = floor(rozmiarX*sin(kat_pochylenia* 3.14159265 / 180));

	if (x1 > 0 && x2 < 0) { //jeœli aktualny k¹t wynosi (-360, -270) lub (90, 180)
		if (pozycjaX + x2 < 50)
			pozycjaX = 50 - x2;
		else if (pozycjaX > 402 + 48 - x1)
			pozycjaX = 402 + 48 - x1;
	}
	else {
		if (pozycjaX + x1 + x2 < 50) 
			pozycjaX = 50 - x1 - x2;
		else if (pozycjaX > 402 + 48) 
			pozycjaX = 402 + 48;
	}

	if (y1 < 0 && y2 < 0) { //jeœli aktualny k¹t wynosi (-180, -90) lub (180, 270)
		if (pozycjaY + y1 < 50) 
			pozycjaY = 50 - y1;
		else if (pozycjaY > 352 + 48 + y2) 
			pozycjaY = 352 + 48 + y2;
	}
	else if (y1 < 0 && y2 > 0) { //jeœli aktualny k¹t wynosi (-360, -270) lub (90, 180)
		if (pozycjaY < 50 + y2 - y1) 
			pozycjaY = 50 + y2 - y1;
		else if (pozycjaY > 352 + 48) 
			pozycjaY = 352 + 48;
	}
	else {
		if (pozycjaY < 50) 
			pozycjaY = 50;
		else if (pozycjaY > 352 + 48 + y2 - y1)
			pozycjaY = 352 + 48 + y2 - y1;
	}
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
int Mebel::pobierz_rozmiarX()
{
	return this->rozmiarX;
}
int Mebel::pobierz_rozmiarY()
{
	return this->rozmiarY;
}
Texture Mebel::pobierz_teksture()
{
	return this->x;
}
int Uzyteczne::pobierz_rozmiarX()
{
	return this->rozmiarX;
}
int Uzyteczne::pobierz_rozmiarY()
{
	return this->rozmiarY;
}
Texture Uzyteczne::pobierz_teksture()
{
	return this->x;
}
Krzeslo::Krzeslo()
{
	x.loadFromFile("grafika/krzeslo.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 48;
	this->rozmiarY = 42;
	this->pozycjaX = 200;
	this->pozycjaY = 198;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
Fotel::Fotel()
{
	x.loadFromFile("grafika/fotel.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 49;
	this->rozmiarY = 48;
	this->pozycjaX = 200;
	this->pozycjaY = 202;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}

Biurko::Biurko()
{
	x.loadFromFile("grafika/biurko.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 117;
	this->rozmiarY = 60;
	this->pozycjaX = 200;
	this->pozycjaY = 201;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
Lozko::Lozko()
{
	x.loadFromFile("grafika/lozko.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 119;
	this->rozmiarY = 61;
	this->pozycjaX = 198;
	this->pozycjaY = 200;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
Szafa::Szafa()
{
	x.loadFromFile("grafika/szafa.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 118;
	this->rozmiarY = 60;
	this->pozycjaX = 199;
	this->pozycjaY = 200;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
Kwiat::Kwiat()
{
	x.loadFromFile("grafika/kwiat.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 48;
	this->rozmiarY = 48;
	this->pozycjaX = 201;
	this->pozycjaY = 201;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}
Lampa::Lampa()
{
	x.loadFromFile("grafika/lampa.png");
	obiekt.setTexture(this->x);
	kat_pochylenia = 0;
	this->rozmiarX = 40;
	this->rozmiarY = 40;
	this->pozycjaX = 201;
	this->pozycjaY = 200;
	active = false;
	obiekt.setPosition(this->pozycjaX, this->pozycjaY);
}