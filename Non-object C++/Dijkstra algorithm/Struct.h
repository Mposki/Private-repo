#pragma once
#include <iostream>
#include "Struct.cpp"
using namespace std;

struct Centrala;

struct Cele;

struct Dane;

int konwertujStringNaInt(string zmienna);

bool sprawdz_czy_liczba(string zmienna);

void help();

Centrala *dodaj_centrale(Centrala *head, Centrala *tail, string nazwa_centrali);

Centrala *znajdz_centrale(Centrala *head, string centrala);

Cele *znajdz_cel(Cele *head, string cel);

void odczyt_z_pliku(Centrala *&head, Centrala *&tail, string plik_wejsciowy);

Cele *dodaj_cel(Cele *head, const string cel, int odleglosc);

void usun_wszystkie_struktury(Centrala *&head);

Dane *Algorytm_Dijkstry(Centrala *head, string start);

void zapis_do_pliku(string plik_wyjsciowy, string start, Dane tablica, Centrala *head);

int szukaj_minimum(int n, Dane* tab);

int policz_wierzcholki(Centrala *head);

string znajdz_wierzcholek(Centrala *head, int wierzcholek);