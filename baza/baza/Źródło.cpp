#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;
typedef struct Produkty
{
	string nazwa_produktu;
	string cena;
	int ilosc;
	Produkty *next;
} Produkty;
typedef struct Klienci
{
	string imie_nazwisko;
	Produkty *head_produkty;
	Klienci *prev, *next;
} Klienci;
bool sprawdz_czy_liczba(string zmienna)
{
	for (int i = 0; i < zmienna.length(); ++i)
	{
		if (zmienna[i] < '0' || zmienna[i] > '9')
			return false;
		else
			return true;
	}
}
int konwertujStringNaInt(string zmienna) {
	int liczba;
	stringstream ss;
	ss << zmienna;
	ss >> liczba;
	ss.clear();
	return liczba;
}
Klienci *dodaj_klienta(Klienci*&head, Klienci *&tail, const string dane_klienta)
{
	Klienci *temp = new Klienci;
	temp->imie_nazwisko = dane_klienta;
	temp->head_produkty = NULL;
	temp->next = NULL;
	temp->prev = NULL;
	if (head == NULL)
	{
		head = tail = temp;
		return temp;
	}
	if (head->imie_nazwisko > temp->imie_nazwisko)
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
		return temp;
	}
	Klienci *temp2 = head;
	while (temp2 != NULL && (temp2->imie_nazwisko < temp->imie_nazwisko))
		temp2 = temp2->next;
	if (temp2 == NULL)
	{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
		return temp;
	}
	temp2->prev->next = temp;
	temp->prev = temp2->prev;
	temp->next = temp2;
	temp2->prev = temp;
}
Produkty *dodaj_produkt_do_klienta(Produkty *head, const string nazwa_produktu, const string cena, int ilosc = 1)
{
	if (head == NULL)
	{
		head = new Produkty;
		head->nazwa_produktu = nazwa_produktu;
		head->cena = cena;
		head->ilosc = ilosc;
		head->next = NULL;
		return head;
	}
	if (head->nazwa_produktu > nazwa_produktu)
	{
		Produkty *temp = dodaj_produkt_do_klienta(NULL, nazwa_produktu, cena);
		temp->next = head;
		return temp;
	}
	head->next = dodaj_produkt_do_klienta(head->next, nazwa_produktu, cena);
	return head;
}
void wypisz_produkty(Produkty * head)
{
	while (head != NULL)
	{
		cout << head->nazwa_produktu << " " << head->cena << " z�" << " " << head->ilosc << " sztuk" << endl;
		head = head->next;
	}
}
void zapisz_do_pliku(Klienci *head)
{
	fstream plik;
	plik.open("sklep.txt", ios::out);
	if (plik.good())
	{
		while (head != NULL)
		{
			plik << "Klient " << head->imie_nazwisko << endl;
			while (head->head_produkty != NULL)
			{
				plik << head->head_produkty->nazwa_produktu << " " << head->head_produkty->cena << " " << head->head_produkty->ilosc << endl;
				head->head_produkty = head->head_produkty->next;
			}
			head = head->next;
		}
	}
	plik.close();
}
void usun_wszystkie_struktury(Klienci *&head)
{
	Klienci *tempKlienci;
	Produkty *tempProdukty;
	while (head != NULL)
	{
		tempKlienci = head;
		while (head->head_produkty != NULL)
		{
			tempProdukty = head->head_produkty;
			delete tempProdukty;
			head->head_produkty = head->head_produkty->next;
		}
		delete tempKlienci;
		head = head->next;
	}
}
Klienci *znajdz_klienta(Klienci *head, string dane)
{
	while (head != NULL)
	{
		if (head->imie_nazwisko == dane)
			return head;
		head = head->next;
	}
	return NULL;
}
Produkty *znajdz_produkt(Produkty *head, string nazwa_produktu)
{
	while (head != NULL)
	{
		if (head->nazwa_produktu == nazwa_produktu)
			return head;
		head = head->next;
	}
	return NULL;
}
void wyswietl_pomoc()
{
	cout << "Program sluzy jako baza danych produktow i klientow. Aby program uruchomil sie poprawnie nalezy podac podczas jego" << endl;
	cout << "wywolywania od 1 do 6 argumentow (wliczaj�c wybor funkcji obslugi), ktore podane s� w nawiasach przy nazwach funkcji." << endl;
	cout << "!!!UWAGA!!!" << endl;
	cout << "Pierwszym argumentem powinien byc nr opcji!" << endl;
	cout << "Program posiada zaimplementowanych 7 funkcji obslugi:" << endl;
	cout << "************MENU GLOWNE************" << endl;
	cout << "1. Dodanie klienta [nazwa klienta]" << endl;
	cout << "2. Usuwanie klienta [nazwa klienta]" << endl;
	cout << "3. Dodanie produktu (do klienta)[nazwa klienta->nazwa produktu->cena produktu]" << endl;
	cout << "4. Edycja danych produktu [nazwa klienta->nazwa produktu->wybor edycji danej (1-cena, 2-ilosc)->stara/nowa cena->stara/nowa ilo�� produktu]" << endl;
	cout << "5. Usuwanie produktu [nazwa klienta->nazwa produktu]" << endl;
	cout << "6. Wyswietlenie wszystkich klientow i produktom im podleglym" << endl;
	cout << "7. Wyswietlenie produktow podleglych danemu klientowi[nazwa klienta]" << endl;
	cout << "W przypadku bledu podczas obslugi programu pojawi sie odpowiedni komunikat." << endl;
	cout << "Plik zewnetrzny musi znajdowac sie w folderze oraz zawierac dane w postaci:" << endl;
	cout << "Klient Imie_Nazwisko" << endl;
	cout << "Produkt 1" << endl;
	cout << "Produkt 2" << endl;
	cout << "..." << endl;
	cout << "Zycze przyjemnej obslugi!" << endl;
}
void odczyt_z_pliku(Klienci *&head, Klienci *&tail)
{
	string templine, nazwa_produktu, cena;
	int ilosc;
	fstream plik;
	plik.open("sklep.txt", ios::in);
	if (plik.good())
	{
		if (!plik.eof())
			plik >> templine;
		while (!plik.eof())
		{
			if (templine == "Klient")
			{
				plik >> templine;
				dodaj_klienta(head, tail, templine);
				Klienci *temp = znajdz_klienta(head, templine);
				if (!plik.eof())
				{
					plik >> templine;
					while (templine != "Klient" && !plik.eof())
					{
						nazwa_produktu = templine;
						plik >> cena;
						plik >> ilosc;
						temp->head_produkty = dodaj_produkt_do_klienta(temp->head_produkty, nazwa_produktu, cena, ilosc);
						plik >> templine;
					}
				}
			}
		}
	}
	else
		cout << "Brak pliku sklep.txt w folderze do odczytu!" << endl;
	plik.close();
}
void dodawanie_klienta(Klienci *&head, Klienci *&tail, string nazwa_klienta)
{
	Klienci *temp = znajdz_klienta(head, nazwa_klienta);
	if (temp == NULL)
		dodaj_klienta(head, tail, nazwa_klienta);
	else
		cout << "Klient juz istnieje" << endl;
}
void usuwanie_klienta(Klienci *&head, Klienci *&tail, string nazwa_klienta)
{
	Klienci *tempK;
	Produkty *tempP;
	tempK = znajdz_klienta(head, nazwa_klienta);
	if (tempK == NULL)
		cout << "Brak klienta w bazie!" << endl;
	else
	{
		if (tempK == head)
			head = head->next;
		else if (tempK == tail)
			tail = tail->prev;
		else
		{
			Klienci *poprzedni = tempK->prev;
			Klienci *nastepny = tempK->next;
			nastepny->prev = poprzedni;
			poprzedni->next = nastepny;
		}
		while (tempK->head_produkty != NULL)
		{
			tempP = tempK->head_produkty;
			delete tempP;
			tempK->head_produkty = tempK->head_produkty->next;
		}
		delete tempK;
	}
}
void dodawanie_produktu(Klienci *&head, Klienci *&tail, string nazwa_klienta, string nazwa_produktu, string cena)
{
	Klienci *tempK = znajdz_klienta(head, nazwa_klienta);
	if (tempK == NULL)
	{
		cout << "Klient nie istnieje! Klient o podanej nazwie zostal dodany.";
		dodaj_klienta(head, tail, nazwa_klienta);
		tempK = znajdz_klienta(head, nazwa_klienta);
	}
	Produkty *tempP = znajdz_produkt(tempK->head_produkty, nazwa_produktu);
	if (tempP == NULL)
		tempK->head_produkty = dodaj_produkt_do_klienta(tempK->head_produkty, nazwa_produktu, cena);
	else
	{
		cout << "Taki produkt juz istnieje! Ilosc produktu zosta�a zinkrementowana." << endl;
		tempP->ilosc++;
	}
}
void edycja_produktu(Klienci *&head, Klienci *&tail, string nazwa_klienta, string nazwa_produktu, string wybor, string cena, string ilosc)
{
	Klienci *tempK = znajdz_klienta(head, nazwa_klienta);
	if (tempK == NULL)
		cout << "Brak klienta w bazie!";
	else
	{
		Produkty *tempP = znajdz_produkt(tempK->head_produkty, nazwa_produktu);
		if (wybor == "1")
			tempP->cena = cena;
		else if (wybor == "2")
		{
			if (sprawdz_czy_liczba(ilosc))
				tempP->ilosc = konwertujStringNaInt(ilosc);
			else
				cout << "Dana wprowadzona jako nowa ilosc produktu jest bledna! Nie jest liczba!" << endl;
		}
		else
			cout << "Brak opcji dzialania na produkcie!" << endl;
	}
}
void usuwanie_produktu(Klienci *&head, Klienci *&tail, string nazwa_klienta, string nazwa_produktu)
{
	Klienci *tempK;
	Produkty *tempP;
	Produkty *tempPp;
	tempK = znajdz_klienta(head, nazwa_klienta);
	if (tempK == NULL)
		cout << "Brak klienta w bazie!" << endl;
	else
	{
		tempP = znajdz_produkt(tempK->head_produkty, nazwa_produktu);
		if (tempP == NULL)
			cout << "Nie znaleziono produktu" << endl;
		else
		{
			if (tempP == tempK->head_produkty)
				tempK->head_produkty = tempK->head_produkty->next;
			else
			{
				tempPp = tempK->head_produkty;
				while (tempPp->next != tempP)
					tempPp = tempPp->next;
				tempPp->next = tempP->next;
			}
			delete tempP;
		}
	}
}
void wypisz(Klienci *head, bool parametr = false, char znak = '>', int liczba = 0)
{
	while (head != NULL)
	{
		cout << head->imie_nazwisko << endl;
		wypisz_produkty(head->head_produkty);
		head = head->next;
	}
}
void wypisz_podanego_klienta(Klienci *&head, Klienci *& tail, string nazwa_klienta)
{
	Klienci * tempK;
	tempK = znajdz_klienta(head, nazwa_klienta);
	if (tempK == NULL)
		cout << "Brak klienta w bazie!" << endl;
	else
		wypisz_produkty(tempK->head_produkty);
}
int main(int argc, char *argv[])
{
	Klienci *head = NULL;
	Klienci *tail = NULL;
	string wybor;
	wybor = argv[1];
	if (argc == 2)
	{
		if (wybor == "-h")
			wyswietl_pomoc();
		if (wybor == "6")
		{
			odczyt_z_pliku(head, tail);
			wypisz(head);
		}
		else
			cout << "Prosze wybrac opcje z menu glownego" << endl;
	}
	else if (argc > 2 && argc <8 && argc != 6)
	{
		odczyt_z_pliku(head, tail);
		if (wybor == "1")
			dodawanie_klienta(head, tail, argv[2]);
		else if (wybor == "2")
			usuwanie_klienta(head, tail, argv[2]);
		else if (wybor == "3")
			dodawanie_produktu(head, tail, argv[2], argv[3], argv[4]);
		else if (wybor == "4")
			edycja_produktu(head, tail, argv[2], argv[3], argv[4], argv[5], argv[6]);
		else if (wybor == "5")
			usuwanie_produktu(head, tail, argv[2], argv[3]);
		else  if (wybor == "7")
			wypisz_podanego_klienta(head, tail, argv[2]);
		else
			cout << "Prosze wybrac opcje z menu glownego" << endl;
		zapisz_do_pliku(head);
		usun_wszystkie_struktury(head);
		cin.ignore(100);
	}
	else
		cout << "Nieodpowiednia liczba argumentow podczas wywolania programu!" << endl;
	return 0;
}