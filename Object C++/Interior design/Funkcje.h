#pragma once
#include "Klasy.h"
using namespace std;

void deaktywuj(vector <Biurko>& tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa> &tab_szafa, vector <Lampa> &tab_lampa, vector <Lozko> &tab_lozko, vector <Kwiat>& tab_kwiat);

Element* szukaj_aktywnego_elementu(vector <Biurko> &tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa>& tab_szafa, vector <Lampa>& tab_lampa, vector <Lozko>& tab_lozko, vector <Kwiat>& tab_kwiat);

void myszka(vector <Biurko> &tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa>& tab_szafa, vector <Lampa>& tab_lampa, vector <Lozko>& tab_lozko, vector <Kwiat>& tab_kwiat, bool& sprawdzanie, int x, int y);

void usun_element(vector <Biurko> &tab_biurko, vector <Fotel>& tab_fotel, vector <Krzeslo>& tab_krzeslo, vector <Szafa>& tab_szafa, vector <Lampa>& tab_lampa, vector <Lozko>& tab_lozko, vector <Kwiat>& tab_kwiat);
