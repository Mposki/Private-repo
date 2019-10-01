#pragma once
#include <crtdbg.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <deque>
using namespace std;

//----------ZADANIE 3
class Zawodnik {
public:
	string nazwa;
	int wiek;
	Zawodnik(string nazwa_, int wiek_) :nazwa(nazwa_), wiek(wiek_) {}
	void wypisz(){
		cout << nazwa << " " << wiek << "\n";
	}
};

//----------ZADANIE 4
class Zawody {
	class zawodnicy_node {
	public:
		weak_ptr<Zawodnik> zawodnik;
		double wynik;
		unique_ptr<zawodnicy_node> nast;
		zawodnicy_node(weak_ptr<Zawodnik> zaw_, double score_ = 0.0) :zawodnik(zaw_), wynik(score_), nast(nullptr) {};
	};
public:
	std::unique_ptr<zawodnicy_node> poczatek;

	Zawody() : poczatek(nullptr) {}

	~Zawody()
	{
		for (std::unique_ptr<zawodnicy_node> aktualna = move(poczatek);
			aktualna;
			aktualna = move(aktualna->nast));
	}

	void dodaj_wynik(weak_ptr<Zawodnik> zawodnik_, double wynik_){
		auto stary_pocz = move(poczatek);
		poczatek = unique_ptr<zawodnicy_node>(new zawodnicy_node(zawodnik_, wynik_));
		poczatek->nast = move(stary_pocz);
	}

	weak_ptr<Zawodnik> najlepszy_zawodnik() {
		auto najlepszy = poczatek.get();
		auto tmp = poczatek.get();
		while (tmp) {
			if (tmp->wynik >= najlepszy->wynik)
				najlepszy = tmp;
			tmp = tmp->nast.get();
		}
		return najlepszy->zawodnik;
	}
	double najlepszy_wynik()
	{
		auto najlepszy = poczatek.get();
		auto tmp = poczatek.get();
		while (tmp) {
			if (tmp->wynik >= najlepszy->wynik)
				najlepszy = tmp;
			tmp = tmp->nast.get();
		}
		return najlepszy->wynik;
	}
};