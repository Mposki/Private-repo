#include <iostream>
using namespace std;
const int stos_max = 256;
int funkcja(char wyrazenie)
{
	switch (wyrazenie)
	{
	case '+': return 1;
	case '*': return 2;
	}
	return 0;
}
int main()
{
	char stos[stos_max];
	int wskaznik = 0;
	cout << "Prosze wprowadzic wyrazenie do tranlsacji, jednoczesnie pamietajac o znaku '=' na koncu wyrazenia: " << endl;
	char wyrazenie;
	while (true)
	{
		cin >> wyrazenie;
		if (wyrazenie == '=')
		{
			while (wskaznik) cout << stos[--wskaznik] << ' ';
			break;
		}
		switch (wyrazenie)
		{
		case ' ':break;
		case '(':stos[wskaznik++] = '(';
			break;
		case')':while (stos[wskaznik - 1] != '(')
			cout << stos[--wskaznik] << ' ';
			wskaznik--;
			break;
		case '+':;
		case '*': while (wskaznik)
		{
			if ((funkcja(wyrazenie) == 2) || (funkcja(wyrazenie) > funkcja(stos[wskaznik - 1]))) break;
			cout << stos[--wskaznik] << ' ';
		}
				  stos[wskaznik++] = wyrazenie;
				  break;
		default: cout << wyrazenie << ' ';
			     break;
		}
	}
	cout << endl;
	system("PAUSE");
	return 0;
}