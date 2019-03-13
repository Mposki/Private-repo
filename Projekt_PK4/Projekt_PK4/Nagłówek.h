#pragma once
#include <iostream>
using namespace std;

class Params
{
public:
	Params();
	~Params();
	int tetno, cisnienie_skurcz, cisnienie_rozkurcz, temperatura;
	bool zwidy, majaczenie, problemy_psychiczne;
private:

};

class Pacjent : public Params
{
public:
	Pacjent();
	~Pacjent();
	string name, surname;
	double pesel;
	bool zywy;
	int dzien_urodzenia, miesiac_urodzenia, rok_urodzenia;
	int dzien_operacji, miesiac_operacji, rok_operacji;
	int dzien_smierci, miesiac_smierci, rok_smierci;
	void dodaj_pacjenta();
	bool nie_zyje();
private:

};

class Choroba
{
public:
	Choroba();
	~Choroba();
	string nazwa, nazwa_latina;
	//odnoœnik do encyklopedii chorób/ medycznej
private:

};

class Lek
{
public:
	Lek();
	~Lek();
	string nazwa, srodek_aktywny;
	int dawka; //ile razy dziennie
	int dawkowanie; //ile mg na jedn¹ dawkê

private:

};

class Terminarz
{
public:
	Terminarz();
	~Terminarz();

private:

};
class Lekarz
{
public:
	Lekarz();
	~Lekarz();
	void dodaj_lekarz();//dodaje lekarza, ¿e¿eli ten poda odnowiednie has³o aktywacyjne, lub pooda has³o swojego mentora

private:
	string username, password, imieL, nazwiskoL;

};
