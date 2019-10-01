#include <iostream>
#include <string>
using namespace std;
// funkcja do sprawdzania wszystkich wyciekach pamieci dajemy przed return; -- _GtDumpMemoryLeak();
// include crt
struct Pasazer
{
	string imie, nazwisko;
	Pasazer * pNext;
};

struct Rejs {
	string portStart, portKon;
	string data;
	Pasazer * pPasazerowie;
	Rejs* pPrev, *pNex;
};

Rejs * dodajRejs(Rejs*&pH, Rejs *&pTail,
	const string & data, const string & ps, const string & pk)
{
	Rejs * nowy = new Rejs;
	nowy->data = data;
	nowy->portStart = ps;
	nowy->portKon = pk;
	nowy->pPasazerowie = NULL;
	nowy->pNex = NULL;
	nowy->pPrev = NULL;
	if (pH == NULL)
	{
		pH = pTail = nowy;
		return nowy;
	}
	if (pH->data > nowy->data)
	{
		nowy->pNex = pH;
		pH->pPrev = nowy;
		pH = nowy;
		return nowy;
	}
	Rejs * tmp = pH;
	while (tmp != NULL && (tmp->data < nowy->data))
		tmp = tmp->pNex;
	if (tmp == NULL)
	{
		pTail->pNex = nowy;
		nowy->pPrev = pTail;
		pTail = nowy;
		return nowy;
	}

	tmp->pPrev->pNex = nowy;
	nowy->pPrev = tmp->pPrev;
	nowy->pNex = tmp;
	tmp->pPrev = nowy;
}

Pasazer * dodajPasazeraDoRosja(Pasazer *pH, const string & imie, const string &nazwisko)
{
	if (pH == NULL)
	{
		pH = new Pasazer;
		pH->imie = imie;
		pH->nazwisko = nazwisko;
		pH->pNext = NULL;
		return pH;
	}
	if (pH->nazwisko > nazwisko)
	{
		Pasazer * nowy = dodajPasazeraDoRosja(NULL, imie, nazwisko);
		nowy->pNext = pH;
		return nowy;
	}

	pH->pNext = dodajPasazeraDoRosja(pH->pNext, imie, nazwisko);
	return pH;

}
Rejs * znajdz_rejs(Rejs *pH, const string & portStartowy, const string &portKoncowy, const string &data)
{
	if (pH = NULL)
	{
		return NULL;
	}
	Rejs *tmp = pH;
	while (tmp != NULL)
	{
		if ((tmp->data == data) && (tmp->portKon == portKoncowy) && (tmp->portStart == portStartowy))
		{
			return tmp;
		}
		tmp = tmp->pNex;
	}
	return NULL;

}
void wypisz(Pasazer * h)
{
	while (h != NULL)
	{
		cout << "    " << h->nazwisko << "" << h->imie << endl;
		h = h->pNext;
	}

}
void dodajPasazera(Rejs *&pH, Rejs *&pT, const string &data, const string & portStartowy, const string &portKoncowy, const string& imie,
	const string &nazwisko)
{
	Rejs *tmp = znajdz_rejs(pH, portStartowy, portKoncowy, data);
	if (tmp == NULL)
	{
		tmp = dodajRejs(pH, pT, data, portStartowy, portKoncowy);
		tmp->pPasazerowie = dodajPasazeraDoRosja(tmp->pPasazerowie, imie, nazwisko);
	}
	if (tmp != NULL)
		tmp->pPasazerowie = dodajPasazeraDoRosja(pH->pPasazerowie, imie, nazwisko);

}
Rejs *ulubiony(Rejs *&pH)
{
	Rejs *ulub = NULL;
	int licznik = 0;
	int max = 0;

	while (pH != NULL)
	{
		licznik = 0;
		Pasazer *tmp = pH->pPasazerowie;
		while (tmp != NULL)
		{

			licznik++;
			tmp = tmp->pNext;

		}

		if (licznik > max)
		{
			max = licznik;
			ulub = pH;

		}
		pH = pH->pNex;

	}
	return ulub;
}
void wypisz(Rejs * h)
{
	while (h != NULL)
	{
		cout << h->data << endl;
		wypisz(h->pPasazerowie);
		h = h->pNex;
	}

}


int main()
{
	Rejs * head = NULL;
	Rejs * tail = NULL;
	string data = "2016-05-24";
	dodajRejs(head, tail, data, data, data);
	head->pPasazerowie = dodajPasazeraDoRosja(head->pPasazerowie, "Ania", "Kowalska");
	head->pPasazerowie = dodajPasazeraDoRosja(head->pPasazerowie, "Beata", "Ania");
	data = "2016-04-24";
	dodajRejs(head, tail, data, data, data);
	head->pPasazerowie = dodajPasazeraDoRosja(head->pPasazerowie, "Adam", "Zenon");
	head->pPasazerowie = dodajPasazeraDoRosja(head->pPasazerowie, "Bartek", "Witek");

	data = "2016-08-24";
	dodajRejs(head, tail, data, data, data);

	wypisz(head);

	cin.get();
	return 0;
}