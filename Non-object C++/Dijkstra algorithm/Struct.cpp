#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Struct.h"

typedef struct Centrala { //lista g³ówna
	string nazwa;	//nazwa miasta g³ównego
	Cele *head_cele;	//wska¿nik na listê podwieszon¹
	Centrala *next;	//wskaŸnik na nastêpny element listy g³ównej
	Centrala *prev;
}Centrala;

typedef struct Cele { //lista podwieszona
	string nazwa_celu;	//nazwa miasta do którego mierzona jest odleg³oœæ
	int odleg³osc;	//odleg³oœæ do miasta od miasta g³ównego
	Cele *next;	//wska¿nik na nastêpny element listy
}Cele;

typedef struct Dane {
	int odleglosc;
	int poprzednik;
	bool odwiedzony;
}Dane;

int konwertujStringNaInt(string zmienna)
{
	int liczba;
	stringstream ss;
	ss << zmienna;
	ss >> liczba;
	ss.clear();
	return liczba;
}

bool sprawdz_czy_liczba(string zmienna)
{
	for (int i = 0; i < zmienna.length(); ++i)
	{
		if (zmienna[i] < '0' || zmienna[i] > '9')
			return false;
		else
			return true;
	}
}

void help()
{
	cout << "Wpisz -i -o -s, a nastepnie w kolejnych krokach nazwy: \n pliku wejsciowego, pliku wyjsciowego oraz miejsca startowego." << endl;
}

Centrala * dodaj_centrale(Centrala * head, Centrala * tail, string nazwa_centrali)
{
	Centrala *temp = new Centrala;
	temp->nazwa = nazwa_centrali;
	temp->head_cele = NULL;
	temp->next = NULL;
	temp->prev = NULL;
	if (head == NULL) {
		head = tail = temp;
		return temp;
	}
	else if (head->nazwa > temp->nazwa) {
		temp->next = head;
		head->prev = temp;
		head = temp;
		return temp;
	}
	else
	{
		Centrala *temp2 = head;
		while (temp2 != NULL && (temp2->nazwa < temp->nazwa))
			temp2 = temp2->next;
		if (temp2 == NULL) {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			return temp;
		}
		temp2->prev->next = temp;
		temp->prev = temp2->prev;
		temp->next = temp2;
		temp2->prev = temp;
		delete temp;
		delete temp2;
	}
}

Centrala * znajdz_centrale(Centrala * head, string centrala)
{
	while (head != NULL)
	{
		if (head->nazwa == centrala)
			return head;
		else
			head = head->next;
	}
	if (head == NULL) {
		return NULL;
	}
}

Cele * znajdz_cel(Cele * head, string cel)
{
	while (head != NULL)
	{
		if (head->nazwa_celu == cel)
			return head;
		else
			head = head->next;
	}
}

void odczyt_z_pliku(Centrala *& head, Centrala *& tail, string plik_wejsciowy)
{
	string centrala, cel, zmienna;
	int odleglosc;
	fstream plik;
	plik.open(plik_wejsciowy + ".txt", ios::in);
	if (plik.good())
	{
		while (!plik.eof())
		{
			plik >> centrala >> cel >> zmienna;
			if (sprawdz_czy_liczba(zmienna)) {
				odleglosc = konwertujStringNaInt(zmienna);
				Centrala *temp = znajdz_centrale(head, centrala);
				if (temp == NULL) {
					dodaj_centrale(head, tail, centrala);
					Centrala *temp2 = znajdz_centrale(head, centrala);
					dodaj_cel(temp2->head_cele, cel, odleglosc);
				}
				else {
					Cele *temp_cel = znajdz_cel(temp->head_cele, cel);
					if (temp_cel == NULL)
						dodaj_cel(temp_cel->next, cel, odleglosc);
					else
						temp_cel->odleg³osc = odleglosc;
					delete temp_cel;
				}
				delete temp;
				Centrala *temp = znajdz_centrale(head, cel);
				if (temp == NULL) {
					dodaj_centrale(head, tail, cel);
					Centrala *temp2 = znajdz_centrale(head, centrala);
					dodaj_cel(temp2->head_cele, centrala, odleglosc);
				}
				else {
					Cele *temp_cel = znajdz_cel(temp->head_cele, centrala);
					if (temp_cel == NULL)
						dodaj_cel(temp_cel->next, centrala, odleglosc);
					else
						temp_cel->odleg³osc = odleglosc;
					delete temp_cel;
				}
				delete temp;
			}
			else
				cout << "Wartosc w pliku podana jako odleglosc nie jest liczba!" << endl;;
		}
	}
	else
		cout << "Brak pliku do odczytu!" << endl;
	plik.close();
}

Cele * dodaj_cel(Cele * head, const string cel, int odleglosc)
{
	if (head == NULL) {
		head = new Cele;
		head->nazwa_celu = cel;
		head->odleg³osc = odleglosc;
		head->next = NULL;
		return head;
	}
	else {
		head = head->next;
	}
}

void usun_wszystkie_struktury(Centrala *& head)
{
	Centrala *tempCentrala;
	Cele *tempCele;
	while (head != NULL)
	{
		tempCentrala = head;
		while (head->head_cele != NULL)
		{
			tempCele = head->head_cele;
			delete tempCele;
			head->head_cele = head->head_cele->next;
		}
		delete tempCentrala;
		head = head->next;
	}
}

Dane * Algorytm_Dijkstry(Centrala * head, string start)
{
	int i = policz_wierzcholki(head), nr_wezla, licz = 0;
	string *tablica_wierzcholkow = new string[i];
	for (int t = 1; t <= i; t++)
		tablica_wierzcholkow[t] = head->nazwa;
	do {
		licz++;
	} while (start != tablica_wierzcholkow[licz]);
	int **macierz = new int*[i];
	macierz[i] = new int[i];
	macierz[0][0] = 0;
	for (int d = 1; d <= i; d++) {
		macierz[0][d] = d;
		macierz[d][0] = d;
	}
	for (int s = 1; s <= i; s++) {
		for (int e = 1; e <= i; e++) {
			if ((head->head_cele->nazwa_celu == tablica_wierzcholkow[s] || head->head_cele->nazwa_celu == tablica_wierzcholkow[e]) && s != e)
				macierz[s][e] = head->head_cele->odleg³osc;
			else
				macierz[s][e] = 0;
			head->head_cele->next;
		}
		head->next;
	}
	Dane *tab = new Dane[i];
	for (int q = 0; q < i; q++) {
		tab[q].odleglosc = (q == licz) ? 0 : INT_MAX;
		tab[q].odwiedzony = false;
		tab[q].poprzednik = -1;
	}
	int min = szukaj_minimum(i, tab);
	while (min != -1) {
		tab[min].odwiedzony = true;
		for (int z = 0; z < i; z++) {
			if (macierz[min][z] > 0 && tab[min].odleglosc + macierz[min][z] < tab[z].odleglosc) {
				tab[z].odleglosc = tab[min].odleglosc + macierz[min][z];
				tab[z].poprzednik = min;
			}
		}
		min = szukaj_minimum(i, tab);
	}
	return tab;

	delete macierz, tab, tablica_wierzcholkow;
}

void zapis_do_pliku(string plik_wyjsciowy, string start, Dane tablica, Centrala * head)
{
	fstream plik;
	plik.open(plik_wyjsciowy, ios::out);
	if (plik.good()) {
		if (!tablica.odwiedzony) {
			plik << start << " " << "nieodwiedzony";
		}
		else {
			if (tablica.poprzednik == -1)
				plik << start << " " << " brak";
			else {
				string nazwa_wierczholka = znajdz_wierzcholek(head, tablica.poprzednik);
				plik << nazwa_wierczholka;
			}
			plik << " " << tablica.odleglosc << " km";
		}
		plik << endl;
	}
	plik.close();
}

int szukaj_minimum(int n, Dane * tab)
{
	int min = -1;
	int mindist = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (!tab[i].odwiedzony && tab[i].odleglosc < mindist) {
			min = i;
			mindist = tab[i].odleglosc;
		}
	}
	return min;
}

int policz_wierzcholki(Centrala * head)
{
	int i = 0;
	do {
		head = head->next;
		i++;
	} while (head == NULL);
	return i;
}

string znajdz_wierzcholek(Centrala * head, int wierzcholek)
{
	int i = policz_wierzcholki(head);
	string *tablica_wierzcholkow = new string[i];
	for (int t = 1; t <= i; t++)
		tablica_wierzcholkow[t] = head->nazwa;
	return tablica_wierzcholkow[wierzcholek];
	delete tablica_wierzcholkow;
}
