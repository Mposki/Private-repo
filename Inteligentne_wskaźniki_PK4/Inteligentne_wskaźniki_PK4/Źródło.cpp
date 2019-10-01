#include <crtdbg.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include "Pointer.h"
using namespace std;

//----------ZADANIE 1
unique_ptr<int[]> wypelnij(unique_ptr<int[]> ptr, int size)
{
	for (int i = 0; i < size; i++)
		ptr[i] = i + 1;
	return ptr;
}

void wypisz(int* ptr, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << ptr[i] << " ";
}

int main(int argc, char** argv)
{
	//----------ZADANIE 1
	auto a = make_unique<int[]>(20);
	a = wypelnij(move(a), 20);
	wypisz(a.get(), 20);
	cout << endl;

	//----------ZADANIE 2
	vector<unique_ptr<int>> v{};
	v.push_back(make_unique<int>(100));
	v.push_back(make_unique<int>(200));
	unique_ptr<int> tmp1(new int(300));
	v.push_back(move(tmp1));
	auto tmp2 = make_unique<int>(400);
	v.push_back(move(tmp2));
	v.push_back(unique_ptr<int>(new int(500)));
	for (auto i = v.begin(); i != v.end(); i++)
		cout << *(*i) << endl;

	//----------ZADANIE 3
	deque<shared_ptr<Zawodnik>> z{};
	z.push_back(make_shared<Zawodnik>("Maciek Bomba", 40));
	z.push_front(make_shared<Zawodnik>("Mateusz Strzecha", 35));
	z.push_front(make_shared<Zawodnik>("Artur Moczymord", 32));
	z.push_back(shared_ptr<Zawodnik>(new Zawodnik("Kord³an Mi³y", 33)));
	z.push_back(shared_ptr<Zawodnik>(new Zawodnik("Hulk Utwardzony", 31)));
	for (auto it = z.begin(); it != z.end(); it++)
		(*it)->wypisz();

	//----------ZADANIE 5
	Zawody rzut_mlotem{};
	rzut_mlotem.dodaj_wynik(z[0], 60.0);
	rzut_mlotem.dodaj_wynik(z[0], 50.3);
	rzut_mlotem.dodaj_wynik(z[0], 64.7);
	rzut_mlotem.dodaj_wynik(z[1], 80.1);
	rzut_mlotem.dodaj_wynik(z[1], 82.2);
	rzut_mlotem.dodaj_wynik(z[1], 66.6);
	rzut_mlotem.dodaj_wynik(z[2], 40.9);
	rzut_mlotem.dodaj_wynik(z[2], 78.8);
	rzut_mlotem.dodaj_wynik(z[2], 80.0);
	rzut_mlotem.dodaj_wynik(z[3], 13.1);
	rzut_mlotem.dodaj_wynik(z[3], 53.8);
	rzut_mlotem.dodaj_wynik(z[3], 30.2);
	rzut_mlotem.dodaj_wynik(z[4], 99.3);
	rzut_mlotem.dodaj_wynik(z[4], 102.6);
	rzut_mlotem.dodaj_wynik(z[4], 106.4);
	auto weak_najlepszy = rzut_mlotem.najlepszy_zawodnik();
	auto shared_najlepszy = weak_najlepszy.lock();
	cout << "Najlepszy wynik osiagnal: " << shared_najlepszy->nazwa << " lat: " << shared_najlepszy->wiek << " wynik: " << rzut_mlotem.najlepszy_wynik() << "\n";

	//----------ZADANIE 6
	for (int i = 0; i < 2000; i++)
		rzut_mlotem.dodaj_wynik(z[0], i); // No dlaczego ??
										  // Stack Overflow
	system("pause");
	return 0;
}