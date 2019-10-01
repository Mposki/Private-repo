#include "Nag³ówek.h"
#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <math.h>  

using namespace sf;

Sprite element::get_sprite()
{
	return this->duszek;
}

int element::get_positionX()
{
	return this->positionX;
}
int element::get_positionY()
{
	return this->positionY;
}
bool element::get_active()
{
	return this->active;
}
void element::set_positionX(int x)
{
	this->positionX = x;
}
void element::set_positionY(int y)
{
	this->positionX = y;
}
void element::set_active(bool tak)
{
	this->active = tak;
}
int ozdoby::get_rozmiarX()
{
	return this->rozmiarX;
}
int ozdoby::get_rozmiarY()
{
	return this->rozmiarY;
}
Texture ozdoby::get_tekstura()
{
	return this->x;
}
Texture meble::get_tekstura()
{
	return this->x;
}
int meble::get_rozmiarX()
{
	return this->rozmiarX;
}
int meble::get_rozmiarY()
{
	return this->rozmiarY;
}
paprotka::paprotka()
{
	angle = 0;
	this->x.loadFromFile("grafika/doniczka.png");
	this->rozmiarX = 48;
	this->rozmiarY = 48;
	this->positionX = 201;
	this->positionY = 201;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
krzeslo_z_lokietnikami::krzeslo_z_lokietnikami()
{
	angle = 0;
	x.loadFromFile("grafika/krzeslozlokciami.png");
	this->rozmiarX = 49;
	this->rozmiarY = 48;
	this->positionX = 200;
	this->positionY = 202;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
szafa::szafa()
{
	angle = 0;
	x.loadFromFile("grafika/szafa.png");
	this->rozmiarX = 118;
	this->rozmiarY = 60;
	this->positionX = 199;
	this->positionY = 200;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
lozko::lozko()
{
	angle = 0;
	x.loadFromFile("grafika/lozko.png");
	this->rozmiarX = 119;
	this->rozmiarY = 61;
	this->positionX = 198;
	this->positionY = 200;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
lampa::lampa()
{
	angle = 0;
	x.loadFromFile("grafika/lampa.png");
	this->rozmiarX = 40;
	this->rozmiarY = 40;
	this->positionX = 201;
	this->positionY = 200;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
stolik::stolik()
{
	angle = 0;
	x.loadFromFile("grafika/stol.png");
	this->rozmiarX = 117;
	this->rozmiarY = 60;
	this->positionX = 200;
	this->positionY = 201;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
taboret::taboret()
{
	angle = 0;
	x.loadFromFile("grafika/taboret.png");
	this->rozmiarX = 39;
	this->rozmiarY = 42;
	this->positionX = 200;
	this->positionY = 199;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
krzeslo_z_oparciem::krzeslo_z_oparciem()
{
	angle = 0;
	x.loadFromFile("grafika/krzeslozoparciem.png");
	this->rozmiarX = 48;
	this->rozmiarY = 42;
	this->positionX = 200;
	this->positionY = 198;
	duszek.setTexture(this->x);
	duszek.setPosition(this->positionX, this->positionY);
	active = false;
}
void element::change_duszek_position(int x, int y)
{
	this->positionX = positionX + x;
	this->positionY = positionY + y;


	int x1 = floor(rozmiarY*sin(angle* 3.14159265 / 180));
	int x2 = floor(rozmiarX*cos(angle* 3.14159265 / 180));
	int y1 = floor(rozmiarY*cos(angle* 3.14159265 / 180));
	int y2 = floor(rozmiarX*sin(angle* 3.14159265 / 180));

	int calosc = floor(angle);
	calosc = calosc % 360;

	cout << angle << endl;
	cout << calosc << endl;



	if (calosc == 90 || calosc == -270)
	{
		if (positionX < 49) positionX = 402 + 49 - rozmiarY;
		else if (positionX > 402 + 49 - rozmiarY) positionX = 50;
		if (positionY < 49 + rozmiarX)positionY = 352 + 49;
		else if (positionY > 352 + 49) positionY = 50 + rozmiarX;
	}
	else 	if (calosc == 180 || calosc == -180)
	{
		if (positionX < 49 + rozmiarX) positionX = 402 + 49;
		else if (positionX > 402 + 49) positionX = 49 + rozmiarX;
		if (positionY < 49 + rozmiarY)positionY = 352 + 49;
		else if (positionY > 352 + 49) positionY = 49 + rozmiarY;
	}
	else 	if (calosc == 270 || calosc == -90)
	{
		if (positionX < 49 + rozmiarY) positionX = 401 + 49;
		else if (positionX > 402 + 49) positionX = 50 + rozmiarY;
		if (positionY < 49)positionY = 352 + 49 - rozmiarX;
		else if (positionY > 352 + 49 - rozmiarX) positionY = 49;
	}
	else if (calosc == 0)
	{
		if (positionX < 49) positionX = 402 + 49 - rozmiarX;
		else if (positionX > 402 + 49 - rozmiarX) positionX = 49;
		if (positionY < 49)positionY = 352 + 49 - rozmiarY;
		else if (positionY > 352 + 49 - rozmiarY) positionY = 49;
	}
	else {
		if (x1 < 0 && x2 > 0)
		{
			if (positionX + x1 < 50) positionX = 402 + 48 - x2;
			else if (positionX > 402 + 48 - x2) positionX = 50 - x1;
		}
		else if (x1 > 0 && x2 < 0)
		{
			if (positionX + x2 < 50) positionX = 402 + 48 - x1;
			else if (positionX > 402 + 48 - x1) positionX = 50 - x2;
		}
		else if (x1 > 0 && x2 > 0)			// + +
		{
			if (positionX < 50) positionX = 402 + 48 - x2 - x1;
			else if (positionX > 402 + 48 - x2 - x1) positionX = 50;
		}
		else								// - -
		{
			if (positionX + x1 + x2 < 50) positionX = 402 + 48;
			else if (positionX > 402 + 48) positionX = 50 - x1 - x2;
		}

		if (y1 > 0 && y2 > 0)
		{
			if (positionY - y2 < 50)positionY = 352 + 48 - y1;
			else if (positionY > 352 + 48 - y1) positionY = 50 + y2;
		}
		else if (y1 < 0 && y2 < 0)
		{
			if (positionY + y1 < 50)positionY = 352 + 48 + y2;
			else if (positionY > 352 + 48 + y2) positionY = 50 - y1;
		}
		else if (y1 < 0 && y2 > 0)			// - +
		{
			if (positionY < 50 + y2 - y1)positionY = 352 + 48;
			else if (positionY > 352 + 48) positionY = 50 + y2 - y1;
		}
		else					            // + -
		{
			if (positionY < 50)positionY = 352 + 48 + y2 - y1;
			else if (positionY > 352 + 48 + y2 - y1) positionY = 50;
		}
	}


	duszek.setPosition(this->positionX, this->positionY);
}
void element::rotate_left()
{
	this->duszek.rotate(-15);
	this->angle += 15;


	int x1 = floor(rozmiarY*sin(angle* 3.14159265 / 180));
	int x2 = floor(rozmiarX*cos(angle* 3.14159265 / 180));
	int y1 = floor(rozmiarY*cos(angle* 3.14159265 / 180));
	int y2 = floor(rozmiarX*sin(angle* 3.14159265 / 180));

	if (x1 < 0 && x2 > 0)
	{
		if (positionX + x1 < 50)  positionX = 50 - x1;
		else if (positionX > 402 + 48 - x2) positionX = 402 + 48 - x2;
	}
	else if (x1 > 0 && x2 < 0)
	{
		if (positionX + x2 < 50) positionX = 50 - x2;
		else if (positionX > 402 + 48 - x1) positionX = 402 + 48 - x1;
	}
	else if (x1 > 0 && x2 > 0)			// + +
	{
		if (positionX < 50)positionX = 50;
		else if (positionX > 402 + 48 - x2 - x1) positionX = 402 + 48 - x2 - x1;
	}
	else								// - -
	{
		if (positionX + x1 + x2 < 50) positionX = 50 - x1 - x2;
		else if (positionX > 402 + 48) positionX = 402 + 48;
	}

	if (y1 > 0 && y2 > 0)
	{
		if (positionY - y2 < 50)positionY = 50 + y2;
		else if (positionY > 352 + 48 - y1)  positionY = 352 + 48 - y1;
	}
	else if (y1 < 0 && y2 < 0)
	{
		if (positionY + y1 < 50) positionY = 50 - y1;
		else if (positionY > 352 + 48 + y2) positionY = 352 + 48 + y2;
	}
	else if (y1 < 0 && y2 > 0)			// - +
	{
		if (positionY < 50 + y2 - y1) positionY = 50 + y2 - y1;
		else if (positionY > 352 + 48) positionY = 352 + 48;
	}
	else					            // + -
	{
		if (positionY < 50) positionY = 50;
		else if (positionY > 352 + 48 + y2 - y1)positionY = 352 + 48 + y2 - y1;
	}



	duszek.setPosition(this->positionX, this->positionY);

}
void element::rotate_right()
{
	this->duszek.rotate(15);
	this->angle -= 15;

	int x1 = floor(rozmiarY*sin(angle* 3.14159265 / 180));
	int x2 = floor(rozmiarX*cos(angle* 3.14159265 / 180));
	int y1 = floor(rozmiarY*cos(angle* 3.14159265 / 180));
	int y2 = floor(rozmiarX*sin(angle* 3.14159265 / 180));

	if (x1 < 0 && x2 > 0)
	{
		if (positionX + x1 < 50)  positionX = 50 - x1;
		else if (positionX > 402 + 48 - x2) positionX = 402 + 48 - x2;
	}
	else if (x1 > 0 && x2 < 0)
	{
		if (positionX + x2 < 50) positionX = 50 - x2;
		else if (positionX > 402 + 48 - x1) positionX = 402 + 48 - x1;
	}
	else if (x1 > 0 && x2 > 0)			// + +
	{
		if (positionX < 50)positionX = 50;
		else if (positionX > 402 + 48 - x2 - x1) positionX = 402 + 48 - x2 - x1;
	}
	else								// - -
	{
		if (positionX + x1 + x2 < 50) positionX = 50 - x1 - x2;
		else if (positionX > 402 + 48) positionX = 402 + 48;
	}

	if (y1 > 0 && y2 > 0)
	{
		if (positionY - y2 < 50)positionY = 50 + y2;
		else if (positionY > 352 + 48 - y1)  positionY = 352 + 48 - y1;
	}
	else if (y1 < 0 && y2 < 0)
	{
		if (positionY + y1 < 50) positionY = 50 - y1;
		else if (positionY > 352 + 48 + y2) positionY = 352 + 48 + y2;
	}
	else if (y1 < 0 && y2 > 0)			// - +
	{
		if (positionY < 50 + y2 - y1) positionY = 50 + y2 - y1;
		else if (positionY > 352 + 48) positionY = 352 + 48;
	}
	else					            // + -
	{
		if (positionY < 50) positionY = 50;
		else if (positionY > 352 + 48 + y2 - y1)positionY = 352 + 48 + y2 - y1;
	}



	duszek.setPosition(this->positionX, this->positionY);

}