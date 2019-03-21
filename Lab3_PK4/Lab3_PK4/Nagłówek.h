#pragma once
#include <iostream>
using namespace std;

//-------FUNKCJE ZAD1------

template <typename Type_m>
Type_m mnoz(Type_m a, Type_m b) {
	return a * b;
}
template <typename Type_d>
Type_d dziel(Type_d a, Type_d b) {
	return a / b;
}
template <typename Type_max>
Type_max max(Type_max a, Type_max b) {
	if (a > b)
		return a;
	else
		return b;
}

//------KLASY------

template <typename type1, typename type2>
class pacjent
{
public:
	pacjent(string nazwa, string lekarz, string autor, type1 temperatura, type2 EKG);
	type1 temperatura;
	type2 EKG;
private:
	string imie;
	string nazwisko;
	string lekarz;
	string getTemperatura(temperatura) { return temperatura };
	string getTemperatura(EKG) { return EKG };
};

template <typename type3, typename type_T, typename type_E>
class wskaünik_pacjent
{
public:
	wskaünik_pacjent(string imie, string nazwisko, string lekarz, type_T temperatura, type_E EKG) :osoba(imie, nazwisko, lekarz, temperatura, EKG) {
		next = NULL;
	}
	wskaünik_pacjent *next;
	//pobieranie pacjenta
private:
	type3 osoba;
};

template<typename type4, typename type_T, typename type_E>
class lista_pacjentow
{
public:
	wskaünik_pacjent<type4, type_T, type_E> *head;
	lista_pacjentow();
	void add(string imie, string nazwisko, string lekarz, type_T temperatura, type_E EKG);
	void show();
};

//------FUNKCJE SK£ADOWE

template<typename type1, typename type2>
inline pacjent<type1, type2>::pacjent(string imie, string nazwisko, string lekarz, type1 temperatura, type2 EKG)
{
	this->imie = imie;
	this->nazwisko = nazwisko;
	this->lekarz = lekarz;
	this->temperatura = temperatura;
	this->EKG = EKG;
}

template<typename type4, typename type_T, typename type_E>
inline lista_pacjentow<type4, type_T, type_E>::lista_pacjentow()
{
	head = NULL;
}

template<typename type4, typename type_T, typename type_E>
inline void lista_pacjentow<type4, type_T, type_E>::add(string imie, string nazwisko, string lekarz, type_T temperatura, type_E EKG)
{
	wskaünik_pacjent<type4, type_T, type_E> *temp = new wskaünik_pacjent<type4, type_T, type_E>(imie, nazwisko, lekarz, temperatura, EKG);
	if (head == NULL) {
		temp->next = NULL;
		head = temp;
	}
	else {
		while (head->next != NULL)
			head = head->next;
		temp->next = NULL;
		head->next = temp;
	}
}