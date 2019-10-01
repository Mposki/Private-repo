#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "Nagłówek.h"
#include <fstream>
#include <ctime>
#include <iterator>
using namespace std;

int randoom(){
	return rand() % 1000;
}
Dane randomData(){
	return Dane(rand() % 1000, cos(rand() % 10));
}

int main()
{
	srand(time(NULL));
	//----------ZADANIE 1----------
	vector<int> naturalne;
	for (int i = 0; i < 10; i++)
		naturalne.push_back(i);
	for (vector<int>::iterator i = naturalne.begin(); i != naturalne.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	vector<int>::iterator iterator = find(naturalne.begin(), naturalne.end(), 6);
	cout << "Znaleziony element to: " << *iterator << endl;
	cout << "------------------------------------------" << endl;
	vector<int>::reverse_iterator odwrocony_iterator(iterator);
	cout << "Odwrocony iterator: " << *odwrocony_iterator << endl;
	cout << "------------------------------------------" << endl;
	vector<int>::iterator base(odwrocony_iterator.base());
	cout << "Po base: " << *base << endl;
	cout << "------------------------------------------" << endl;
	//----------ZADANIE 2----------
	deque<int> dekue;
	front_insert_iterator<deque<int> > poczatek(dekue);
	back_insert_iterator<deque<int> > koniec(dekue);
	*poczatek = 1;
	*poczatek = 2;
	*koniec = 9;
	*koniec = 10;
	insert_iterator<deque<int>> wstawiajacy(dekue, dekue.begin() + 1);
	*wstawiajacy = 11;
	back_inserter(dekue) = 12;
	copy(dekue.begin(), dekue.end(), front_inserter(dekue));
	//---wyświetlanie---
	cout << "Poczatek: ";
	for (deque<int>::iterator i = dekue.begin(); i != dekue.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "Koniec: ";
	for (deque<int>::iterator i = dekue.begin(); i != dekue.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "Wstawiajacy: ";
	for (deque<int>::iterator i = dekue.begin(); i != dekue.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "Wstawiajacy na koniec: ";
	for (deque<int>::iterator i = dekue.begin(); i != dekue.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "Po skopiowaniu: ";
	for (deque<int>::iterator i = dekue.begin(); i != dekue.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	//----------ZADANIE 3----------
	vector<int> całkowite(100);
	generate(całkowite.begin(), całkowite.end(), randoom);
	cout << "Lista calkowitych: ";
	for (vector<int>::iterator i = całkowite.begin(); i != całkowite.end(); i++)
		cout << *i << " ";
	cout << endl;
	cout << "------------------------------------------" << endl;
	//---
	vector<float>odwrotne(100);
	copy(całkowite.begin(), całkowite.end(), odwrotne.begin());
	for_each(odwrotne.begin(), odwrotne.end(), [&](float &wartosc) {wartosc = 1 / wartosc; });
	cout << "Lista odwrotnych: ";
	for_each(odwrotne.begin(), odwrotne.end(), [&](float &wartosc) {cout << wartosc << " "; });
	cout << endl;
	cout << "------------------------------------------" << endl;
	//---
	vector<Dane> lista_klas(100);
	generate(lista_klas.begin(), lista_klas.end(), randomData);
	//---
	cout << "Lista klas: " << endl;
	for_each(lista_klas.begin(), lista_klas.end(), [&](Dane &wartosc) {cout << wartosc << " "; });
	cout << "------------------------------------------" << endl;
	cout << "Posortowane po int: " << endl;
	sort(lista_klas.begin(), lista_klas.end(), [](const Dane &dana1, const Dane &dana2)->bool {return dana1.integer < dana2.integer; });
	for_each(lista_klas.begin(), lista_klas.end(), [&](Dane &wartosc) {cout << wartosc << " "; });
	cout << "------------------------------------------" << endl;
	//---
	cout << "Posortowane po double: " << endl;
	vector<Dane>listaKlasDouble(100);
	copy(lista_klas.begin(), lista_klas.end(), listaKlasDouble.begin());
	sort(listaKlasDouble.begin(), listaKlasDouble.end(), [](const Dane &dana1, const Dane &dana2)->bool {return dana1.zmienno < dana2.zmienno; });
	for_each(listaKlasDouble.begin(), listaKlasDouble.end(), [&](Dane &wartosc) {cout << wartosc << " "; });
	cout << "------------------------------------------" << endl;
	//---
	system("pause");
	return 0;
}