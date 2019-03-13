#include <time.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Klasy.h"
#include "Funkcje.h"
using namespace std;

void deaktywuj(vector <Biurko>& tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa> &tab_szafa, vector <Lampa> &tab_lampa, vector <Lozko> &tab_lozko, vector <Kwiat>& tab_kwiat) {
	//przechodzi po kontenerze zmieniaj¹c obiekt aktywny na nieaktywny (bool active = false)
	for (auto i = 0; i < tab_kwiat.size(); i++)
		tab_kwiat[i].ustaw_aktywny(false);
	for (auto i = 0; i < tab_fotel.size(); i++)
		tab_fotel[i].ustaw_aktywny(false);
	for (auto i = 0; i < tab_lozko.size(); i++)
		tab_lozko[i].ustaw_aktywny(false);
	for (auto i = 0; i < tab_lampa.size(); i++)
		tab_lampa[i].ustaw_aktywny(false);
	for (auto i = 0; i < tab_szafa.size(); i++)
		tab_szafa[i].ustaw_aktywny(false);
	for (auto i = 0; i < tab_biurko.size(); i++)
		tab_biurko[i].ustaw_aktywny(false);
	for (auto i = 0; i < tab_krzeslo.size(); i++)
		tab_krzeslo[i].ustaw_aktywny(false);
}

Element* szukaj_aktywnego_elementu(vector <Biurko> &tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa>& tab_szafa, vector <Lampa>& tab_lampa, vector <Lozko>& tab_lozko, vector <Kwiat>& tab_kwiat) {
	//przechodzi po kontenerze sprawdzaj¹c czy któryœ z obiektów jest aktywny (bool active == true), jeœli tak, to go zwraca
	for (auto i = 0; i < tab_kwiat.size(); i++) {
		if (tab_kwiat[i].aktywny())
			return &tab_kwiat[i];
	}
	for (auto i = 0; i < tab_fotel.size(); i++) {
		if (tab_fotel[i].aktywny())
			return &tab_fotel[i];
	}
	for (auto i = 0; i < tab_lozko.size(); i++) {
		if (tab_lozko[i].aktywny())
			return &tab_lozko[i];
	}
	for (auto i = 0; i < tab_lampa.size(); i++) {
		if (tab_lampa[i].aktywny())
			return &tab_lampa[i];
	}
	for (auto i = 0; i < tab_szafa.size(); i++) {
		if (tab_szafa[i].aktywny())
			return &tab_szafa[i];
	}
	for (auto i = 0; i < tab_biurko.size(); i++) {
		if (tab_biurko[i].aktywny())
			return &tab_biurko[i];
	}
	for (auto i = 0; i < tab_krzeslo.size(); i++) {
		if (tab_krzeslo[i].aktywny())
			return &tab_krzeslo[i];
	}
	return NULL;
}

void myszka(vector <Biurko> &tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa>& tab_szafa, vector <Lampa>& tab_lampa, vector <Lozko>& tab_lozko, vector <Kwiat>& tab_kwiat, bool& sprawdzanie, int x, int y) {
	for (auto i = 0; i < tab_kwiat.size() && sprawdzanie; i++) { //porzechodzi przez ka¿dy element kontenera
		if (tab_kwiat[i].pobierz_pozycjaX() < x && x<tab_kwiat[i].pobierz_pozycjaX() + tab_kwiat[i].pobierz_rozmiarX() && y>tab_kwiat[i].pobierz_pozycjaY() && y < tab_kwiat[i].pobierz_pozycjaY() + tab_kwiat[i].pobierz_rozmiarY()) {//je¿eli kursor znalaz³ siê miêdzy wielkoœciami wyznaczaj¹cymi obiekt (pozycja, rozmiarX i rozmiarY)
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_kwiat[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_biurko.size() && sprawdzanie; i++) {
		if (tab_biurko[i].pobierz_pozycjaX() < x && x<tab_biurko[i].pobierz_pozycjaX() + tab_biurko[i].pobierz_rozmiarX() && y>tab_biurko[i].pobierz_pozycjaY() && y < tab_biurko[i].pobierz_pozycjaY() + tab_biurko[i].pobierz_rozmiarY()) {
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_biurko[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_szafa.size() && sprawdzanie; i++) {
		if (tab_szafa[i].pobierz_pozycjaX() < x && x<tab_szafa[i].pobierz_pozycjaX() + tab_szafa[i].pobierz_rozmiarX() && y>tab_szafa[i].pobierz_pozycjaY() && y < tab_szafa[i].pobierz_pozycjaY() + tab_szafa[i].pobierz_rozmiarY()) {
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_szafa[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_fotel.size() && sprawdzanie; i++) {
		if (tab_fotel[i].pobierz_pozycjaX() < x && x<tab_fotel[i].pobierz_pozycjaX() + tab_fotel[i].pobierz_rozmiarX() && y>tab_fotel[i].pobierz_pozycjaY() && y < tab_fotel[i].pobierz_pozycjaY() + tab_fotel[i].pobierz_rozmiarY()) {
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_fotel[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_krzeslo.size() && sprawdzanie; i++) {
		if (tab_krzeslo[i].pobierz_pozycjaX() < x && x<tab_krzeslo[i].pobierz_pozycjaX() + tab_krzeslo[i].pobierz_rozmiarX() && y>tab_krzeslo[i].pobierz_pozycjaY() && y < tab_krzeslo[i].pobierz_pozycjaY() + tab_krzeslo[i].pobierz_rozmiarY()) {
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_krzeslo[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_lampa.size() && sprawdzanie; i++) {
		if (tab_lampa[i].pobierz_pozycjaX() < x && x<tab_lampa[i].pobierz_pozycjaX() + tab_lampa[i].pobierz_rozmiarX() && y>tab_lampa[i].pobierz_pozycjaY() && y < tab_lampa[i].pobierz_pozycjaY() + tab_lampa[i].pobierz_rozmiarY()) {
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_lampa[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_lozko.size() && sprawdzanie; i++) {
		if (tab_lozko[i].pobierz_pozycjaX() < x && x<tab_lozko[i].pobierz_pozycjaX() + tab_lozko[i].pobierz_rozmiarX() && y>tab_lozko[i].pobierz_pozycjaY() && y < tab_lozko[i].pobierz_pozycjaY() + tab_lozko[i].pobierz_rozmiarY()) {
			deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			tab_lozko[i].ustaw_aktywny(true);
			sprawdzanie = false;
			break;
		}
	}
}

void usun_element(vector<Biurko>& tab_biurko, vector<Fotel>& tab_fotel, vector<Krzeslo>& tab_krzeslo, vector<Szafa>& tab_szafa, vector<Lampa>& tab_lampa, vector<Lozko>& tab_lozko, vector<Kwiat>& tab_kwiat) {
	//usuwa obiekt, który jest aktywny z kontenera
	for (int i = 0; i < tab_kwiat.size(); i++) {
		if (tab_kwiat[i].aktywny())
			tab_kwiat.erase(tab_kwiat.begin() + i);
	}
	for (int i = 0; i < tab_biurko.size(); i++) {
		if (tab_biurko[i].aktywny())
			tab_biurko.erase(tab_biurko.begin() + i);
	}
	for (int i = 0; i < tab_szafa.size(); i++) {
		if (tab_szafa[i].aktywny())
			tab_szafa.erase(tab_szafa.begin() + i);
	}
	for (int i = 0; i < tab_fotel.size(); i++) {
		if (tab_fotel[i].aktywny())
			tab_fotel.erase(tab_fotel.begin() + i);
	}
	for (int i = 0; i < tab_krzeslo.size(); i++) {
		if (tab_krzeslo[i].aktywny())
			tab_krzeslo.erase(tab_krzeslo.begin() + i);
	}
	for (int i = 0; i < tab_lampa.size(); i++) {
		if (tab_lampa[i].aktywny())
			tab_lampa.erase(tab_lampa.begin() + i);
	}
	for (int i = 0; i < tab_lozko.size(); i++) {
		if (tab_lozko[i].aktywny())
			tab_lozko.erase(tab_lozko.begin() + i);
	}
}