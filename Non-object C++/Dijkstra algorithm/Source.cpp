#include <iostream>
#include "Struct.h"
using namespace std;

int main(int argc, char *argv[])
{
	Centrala *head = NULL;
	Centrala *tail = NULL;
	string wybor_pliku_wejsciowego, wybor_pliku_wyjsciowego, miasto_start;
	string plik_wejsciowy, plik_wyjsciowy, start;
	wybor_pliku_wejsciowego = argv[1];
	wybor_pliku_wyjsciowego = argv[2];
	start = argv[3];
	if (argc == 4) {
		if (wybor_pliku_wejsciowego == "-i")
		{
			cout << "Prosze wpisaæ nazwe pliku wejsciowego bez rozszerzenia:";
			cin >> plik_wejsciowy;
			if (wybor_pliku_wyjsciowego == "-o") {
				cout << "Prosze wpisaæ nazwe pliku wyjsciowego bez rozszerzenia:";
				cin >> plik_wyjsciowy;
				if (miasto_start == "-s") {
					cout << "Prosze wpisaæ miasto centrali:";
					cin >> start;
					odczyt_z_pliku(head, tail, plik_wejsciowy);
					Dane *tablica = Algorytm_Dijkstry(head, start);
					int i = policz_wierzcholki(head);
					zapis_do_pliku(plik_wyjsciowy, start, tablica[i], head);
					usun_wszystkie_struktury(head);
				}
				else
					cout << "Blad przelacznika!" << help << endl;
			}
			else
				cout << "Blad przelacznika!" << help << endl;
		}
		else
			cout << "Blad przelacznika!" << help << endl;
	}
	else
		cout << "Nieodpowiednia liczba argumentow podczas wywolania programu!" << help << endl;
	return 0;
}