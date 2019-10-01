#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;
int konwertujCharNaInt(char znak)
{
	int liczba;
	stringstream ss;
	ss << znak;
	ss >> liczba;
	ss.clear();
	return liczba;
}
int main()
{
	char polibiusz[8][9] = { { 'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E' },
	{ 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i' },
	{ 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N' },
	{ 'n', 'O', 'o', 'P', 'p', 'R', 'r', 'S', 's' },
	{ 'T', 't', 'U', 'u', 'W', 'w', 'Y', 'y', 'Z' },
	{ 'z', '.', ',', '!', '?', '0', '1', '2', '3' },
	{ '4', '5', '6', '7', '8', '9', '(', ')', '+' },
	{ '-', '<', '>', '#', ':', ';', '/', '_', ' ' } };

	fstream plik; string odczyt; char znak, otwarcie;
	do
	{
		cout << "Witam w programie szyfrujacym." << endl;//zast¹piæ wprowadzaniem z lini poleceñ
		cout << "MENU GLOWNE" << endl;
		cout << "-------------" << endl;
		cout << "1. Kodowanie" << endl;
		cout << "2. Dekodowanie" << endl;
		cout << "3. Wyjscie z programu" << endl;
		cout << "Pomoc- nacisnij h" << endl;
		cout << "Prosze wybrac opcje z menu glownego:" << endl;
		znak = _getch();
		string nowy_plik = "";
		switch (znak)
		{
		case '1':
		{
			cout << "Prosze wprowadzic nazwe kodowanego pliku: "; cin >> odczyt;
			plik.open(odczyt + ".txt", ios::in);
			if (plik.good() == true)
			{
				cout << "Udalo sie otworzyc plik! Prosze wprowadzic nazwe pliku z zawartoscia do zakodowania: ";
				cin >> nowy_plik;
				if (nowy_plik == odczyt)
				{
					cout << "Podany plik istnieje w lokalizacji, prosze wprowadziæ inna nazwe!" << endl;
					break;
				}
				else
				{
					fstream kod;
					kod.open(nowy_plik + ".txt", ios::out);
					string templinia;
					while (getline(plik, templinia))
					{
						string zaklinia = "";
						for (int i = 0; i < templinia.length(); i++) //schemat blokowy
						{
							char aktchar = templinia[i];
							for (int j = 0; j < 8; j++)
							{
								for (int k = 0; k < 9; k++)
								{
									if (aktchar == polibiusz[j][k])
									{
										string js = to_string(j);
										string ks = to_string(k);
										zaklinia = zaklinia + js + ks;
									}
								}
							}
						}
						kod << zaklinia << endl;
					}
					cout << "Prosze sprawdzic czy zakodowany plik zostal utworzony i czy znajduje sie w nim ciag liczb." << endl;
					kod.close();
					kod.clear();
					kod.sync();
				}
			}
			else cout << "Nie udalo sie zaladowac pliku. Prosze sprawdzic czy nazwa pliku zostala wprowadzona poprawnie" << endl;
			plik.close();
			plik.clear();
		}; break;
		case '2':
		{
			cout << "Prosze wprowadzic nazwe dekodowanego pliku: "; cin >> odczyt;
			plik.open(odczyt + ".txt", ios::in);
			if (plik.good() == true)
			{
				cout << "Udalo sie otworzyc plik! Prosze wprowadzic nazwe pliku z zakodowana zawartoscia: ";
				cin >> nowy_plik;
				fstream dekod;
				dekod.open(nowy_plik + ".txt", ios::out);
				string templinia;
				while (getline(plik, templinia))
				{
					string dekodlinia = "";
					for (int i = 0; i < templinia.length(); i++)
					{
						char literka;
						int x, y;
						if (i % 2 == 0)
						{
							x = konwertujCharNaInt(templinia[i]); //jest to jdenoczesne przypisanie wartoœci i konwersja z char do int
						}
						else
						{
							y = konwertujCharNaInt(templinia[i]);
							literka = polibiusz[x][y];
							dekodlinia.push_back(literka);
						}
					}
					dekod << dekodlinia << endl;
				}
				cout << "Prosze sprawdzic czy plik odkodowany zostal utworzony i czy znajduje sie w nim tekst." << endl;
				dekod.close();
				dekod.clear();
				dekod.sync();
			}
			else cout << "Nie udalo sie zaladowac pliku. Prosze sprawdzic czy nazwa pliku zostala wprowadzona poprawnie" << endl;
			plik.close();
			plik.clear();
		}; break;
		case '3': exit(0); break;
		case 'h':
		{
			cout << "Plik musi zostac wprowadzony do folderu rozwiazania. Nazwe pliku prosze podawac bez rozszerzenia oraz nazwa pliku nie" << endl;
			cout << "moze posiadac znakow spacji. Prosze sie nie martwic duza iloscia czasu poswiecana na operacje - jest to" << endl;
			cout << "najprawdopodobniej wynikiem wielkosci kodowanego / dekodowanego pliku.Tablica Polibiusza wyglada nastepujaca: " << endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					cout << "[" << polibiusz[i][j] << "]";
				}
				cout << endl;
			}
		}; break;
		default: cout << "Prosze wybrac opcje z menu!" << endl;
		}
		cout << "Dziekuje za skorzystanie z mojego programu. Menu glowne wyswietli sie ponownie po wykonaniu operacji i wprowadzeniu" << endl;
		cout << "znaku 't' z klawiatury." << endl;
		otwarcie = _getch();
		cout << endl;
	} while (otwarcie == 't');
	return 0;
}