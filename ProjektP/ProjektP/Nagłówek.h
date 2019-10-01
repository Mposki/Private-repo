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


class element
{
protected:
	float angle;
	int positionX, positionY;
	bool active;
	int rozmiarX, rozmiarY;

public:
	Sprite duszek;
	void change_duszek_position(int x, int y);
	int get_positionX();
	int get_positionY();
	bool get_active();
	void set_positionX(int x);
	void set_positionY(int Y);
	void set_active(bool tak);
	Sprite get_sprite();
	void rotate_left();
	void rotate_right();
};

//////////////////ELEMNTY//////////////////////////

class meble :public element
{
protected:
	Texture x;
public:
	int get_rozmiarX();
	int get_rozmiarY();
	Texture get_tekstura();
};

class ozdoby : public element
{
protected:
	Texture x;
public:
	int get_rozmiarX();
	int get_rozmiarY();
	Texture get_tekstura();
};

/////////////////////MEBLE//////////////////////////

class krzeslo_z_oparciem :public meble
{
public:
	krzeslo_z_oparciem();
};

class krzeslo_z_lokietnikami : public meble
{
public:
	krzeslo_z_lokietnikami();
};


class stolik : public meble
{
public:
	stolik();
};

class lozko :public meble
{
public:
	lozko();
};

class szafa : public meble
{
public:
	szafa();
};

/////////////////////OZDOBY//////////////////////////

class paprotka : public ozdoby
{
public:
	paprotka();
};

class lampa : public ozdoby
{
public:
	lampa();
};

class taboret : public ozdoby
{
public:
	taboret();
};