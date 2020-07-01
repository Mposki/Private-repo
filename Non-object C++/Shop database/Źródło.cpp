#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;
typedef struct klienci
{
	string ID_klienta;
	string imie;
	string nazwisko;
	klienci *next;
} klienci;
typedef struct produkty
{
	string nazwa_produktu;
	klienci *head_klienci;
	produkty *prev, *next;
} produkty;
produkty *dodaj_produkt(produkty*&head, produkty *&tail, string nazwa_nowego_produktu)
{
	produkty *tmp = new produkty;
	tmp->nazwa_produktu = nazwa_nowego_produktu;
	tmp->head_klienci = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	if (head == NULL)
	{
		head = tail = tmp;
		return tmp;
	}
	if (head->nazwa_produktu > tmp->nazwa_produktu)
	{
		tmp->next = head;
		head->prev = tmp;
		head = tmp;
		return tmp;
	}
	produkty *tmp2 = head;
	while (tmp2 != NULL && (tmp2->nazwa_produktu < tmp->nazwa_produktu))
	{
		tmp2 = tmp2->next;
	}
	if (tmp2 == NULL)
	{
		tail->next = tmp;
		tmp->prev = tail;
		tail = tmp;
		return tmp;
	}
	tmp2->prev->next = tmp;
	tmp->prev = tmp2->prev;
	tmp->next = tmp2;
	tmp2->prev = tmp;
	return tmp;
}
klienci *dodaj_klienta_do_produktu(klienci *head, string ID_klienta, string imie, string nazwisko)
{
	if (head == NULL)
	{
		head = new klienci;
		head->ID_klienta = ID_klienta;
		head->imie = imie;
		head->nazwisko = nazwisko;
		head->next = NULL;
		return head;
	}
	if (head->ID_klienta > ID_klienta)
	{
		klienci *tmp = dodaj_klienta_do_produktu(NULL, ID_klienta, imie, nazwisko);
		tmp->next = head;
		return tmp;
	}
	head->next = dodaj_klienta_do_produktu(head->next, ID_klienta, imie, nazwisko);
	return head;
}
void pokaz_klientow(klienci * head)
{
	while (head != NULL)
	{
		cout << head->ID_klienta << "." << head->imie << " " << head->nazwisko << endl;
		head = head->next;
	}
	if (head == NULL)
	{
		cout << "Blad! Brak klientow w produkcie" << endl;
	}
}
void wypisz_do_pliku(produkty *head)
{
	fstream plik;
	plik.open("dane.txt", ios::out);
	if (plik.good() == true)
	{
		while (head != NULL)
		{
			plik << head->nazwa_produktu << endl;
			while (head->head_klienci != NULL)
			{
				plik << ":" << head->head_klienci->ID_klienta << "." << head->head_klienci->imie << " " << head->head_klienci->nazwisko << ",";
				head->head_klienci = head->head_klienci->next;
			}
			head = head->next;
		}
		if (head == NULL)
		{
			cout << "Blad! Struktura produkty jest pusta!" << endl;
		}
	}
	else
	{
		cout << "Blad! Brak mozliwosci zapisania pliku!" << endl;
	}
	plik.close();
}
void usun_struktury(produkty *& head)
{
	produkty * tmpprodukty;
	klienci * tmpklienci;
	while (head != NULL)
	{
		tmpprodukty = head;
		while (head->head_klienci != NULL)
		{
			tmpklienci = head->head_klienci;
			delete tmpklienci;
			head->head_klienci = head->head_klienci->next;
		}
		delete tmpprodukty;
		head = head->next;
	}
}
produkty *znajdz_produkt(produkty *head, string nazwa_produktu)
{
	while (head != NULL)
	{
		if (head->nazwa_produktu == nazwa_produktu)
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}
klienci *znajdz_klienta(klienci *head, string ID_klienta)
{
	while (head != NULL)
	{
		if (head->ID_klienta == ID_klienta)
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}
void dodawanie_produktu(produkty *&head, produkty *&tail)
{
	string nazwa_nowego_produktu;
	produkty *tmp = znajdz_produkt(head, nazwa_nowego_produktu);
	if (tmp == NULL)
	{
		dodaj_produkt(head, tail, nazwa_nowego_produktu);
	}
	else
	{
		cout << "Produkt juz istnieje" << endl;
	}
}
void dodawanie_klienta_do_produktu(produkty *&head, produkty *&tail, string nazwa_produktu, string ID_klienta, string imie, string nazwisko)
{
	produkty * tmpP = znajdz_produkt(head, nazwa_produktu);
	if (tmpP == NULL)
	{
		cout << "Produkt nie istnieje!" << endl;
	}
	klienci * tmpK = znajdz_klienta(tmpP->head_klienci, ID_klienta);
	if (tmpK == NULL)
	{
		tmpP->head_klienci = dodaj_klienta_do_produktu(tmpP->head_klienci, ID_klienta, imie, nazwisko);
	}
	else
	{
		cout << "Klient juz istnieje!" << endl;
	}
}
void edycja_klienta(produkty *&head, produkty *&tail, string nazwa_produktu, string ID_klienta, string wybor_edycji, string nazwa)
{
	produkty *tmpP = znajdz_produkt(head, nazwa_produktu);
	if (tmpP == NULL)
	{
		cout << "Produkt nie istnieje!";
	}
	else
	{
		klienci *tmpK = znajdz_klienta(tmpP->head_klienci, ID_klienta);
		if (wybor_edycji == "1")
		{
			tmpK->ID_klienta = nazwa;
		}
		else if (wybor_edycji == "2")
		{
			tmpK->imie = nazwa;
		}
		else if (wybor_edycji == "3")
		{
			tmpK->nazwisko = nazwa;
		}
		else
		{
			cout << "Blad! Brak opcji edycji danych klienta!" << endl;
		}
	}
}
void wczytaj_struktury_z_pliku(produkty *&head, produkty *&tail)//zrobiæ!!!!!!!
{
	/*string templine, nazwa_produktu, ID_klienta, imie, nazwisko;
	fstream plik;
	plik.open("dane.txt", ios::in);
	//if (plik.good() == true)
	//{
	cout << "dzialam" << endl;
	while (getline(plik, templine))
	{
		for (int i = 0; i < templine.length(); i++)
		{
			bool dwukropek = false;
			bool kropka = false;
			bool spacja = false;
			plik >> templine;
			nazwa_produktu = templine;
			
			cout << "dzialam" << endl;
			if (templine[i] == ':')
			{
				dwukropek = true;
				plik >> templine;
				ID_klienta = templine;
				cout << "dzialam" << endl;
			}
			if (templine[i] == '.')
			{
				kropka = true;
				plik >> templine;
				imie = templine;
				cout << "dzialam" << endl;
			}
			if (templine[i] == ' ')
			{
				spacja = true;
				plik >> templine;
				nazwisko = templine;
				cout << "dzialam" << endl;
			}
			if (templine[i] == ',')
			{
				tmp->head_klienci = dodaj_klienta_do_produktu(tmp->head_klienci, ID_klienta, imie, nazwisko);
				kropka = false;
				spacja = false;
				plik >> templine;
				cout << "dzialam" << endl;
			}
		}
	}*/
	string ID_klienta = "";
	string nazwisko = "";
	string imie = "";
	string nazwa_produktu = "";
	fstream plik;
	plik.open("dane.txt", ios::in);
	if (plik.good() == false)
	{ 
		cout << "Blad! Brak pliku!" << endl;
		exit(0);
	}
	else
	{
		string templine;
		bool dwukropek = false;
		bool kropka = false;
		bool przecinek = false;
		bool spacja = false;
		nazwa_produktu = "";
		while (getline(plik, templine))
		{
			for (int i = 0; i < templine.length(); i++)
			{
				if (templine[i] == ':')
				{
					dwukropek = true;
					continue;
				}
				if (dwukropek == false)
				{
					nazwa_produktu = nazwa_produktu + templine[i];
					continue;
				}
			}
		}
		dodaj_produkt(head, tail, nazwa_produktu);
		produkty *tmp = znajdz_produkt(head, nazwa_produktu);
		while (getline(plik, templine))
		{
			for (int i = 0; i < templine.length(); i++)
			{
				if (templine[i] == '.')
				{
					kropka = true;
					continue;
				}
				if (kropka == false)
				{
					ID_klienta = ID_klienta + templine[i];
					continue;
				}
				if (templine[i] == ' ')
				{
					spacja = true;
					continue;
				}
				if (spacja == false)
				{
					imie = imie + templine[i];
					continue;
				}
				if (templine[i] == ',')
				{
					kropka = false;
					przecinek = false;
					dodaj_klienta_do_produktu(tmp->head_klienci, ID_klienta, imie, nazwisko);
					ID_klienta = "";
					imie = "";
					nazwisko = "";
					continue;
				}
				nazwisko = nazwisko + templine[i];
			}
		}
	plik.close();
	}
}
void usun_produkt(produkty *&head, produkty *&tail, string nazwa)//dodaæ blokadê, gdy s¹ klienci w liœcie produktów
{
	produkty * tmpP;
	klienci * tmpK;
	tmpP = znajdz_produkt(head, nazwa);
	if (tmpP == NULL)
	{
		cout << "Nie znaleziono produktu!" << endl;
	}
	else
	{
		if (tmpP == head)
		{
			head = head->next;
		}
		else if (tmpP == tail)
		{
			tail = tail->prev;
		}
		else
		{
			produkty *p = tmpP->prev;
			produkty *n = tmpP->next;
			n->prev = p;
			p->next = n;
		}
		while (tmpP->head_klienci != NULL)
		{
			tmpK = tmpP->head_klienci;
			delete tmpK;
			tmpP->head_klienci = tmpP->head_klienci->next;
		}
		delete tmpP;
	}
}
void usun_klienta(produkty *& head, produkty *& tail, string nazwa, string ID_klienta)
{
	produkty * tmpP;
	klienci * tmpK;
	klienci * tmpKk;
	tmpP = znajdz_produkt(head, nazwa);
	if (tmpP == NULL)
	{
		cout << "Nie znaleziono produktu!" << endl;
	}
	else
	{
		tmpK = znajdz_klienta(tmpP->head_klienci, ID_klienta);
		if (tmpK == NULL)
		{
			cout << "Nie znaleziono klienta!" << endl;
		}
		else
		{
			if (tmpK == tmpP->head_klienci)
			{
				tmpP->head_klienci = tmpP->head_klienci->next;
			}
			else
			{
				tmpKk = tmpP->head_klienci;
				while (tmpKk->next != tmpK)
				{
					tmpKk = tmpKk->next;
				}
				tmpKk->next = tmpK->next;
			}
			delete tmpK;
		}
	}
}
void wypisz_produkt(produkty *&head, produkty *&tail, string nazwa)
{
	produkty *tmpP;
	tmpP = znajdz_produkt(head, nazwa);
	if (tmpP == NULL)
	{
		cout << "Nie znaleziono produktu" << endl;
	}
	else
	{
		pokaz_klientow(tmpP->head_klienci);
	}
}
void wyswietl_pomoc()
{
	cout << "Program sluzy jako baza danych produktow i klientow. Aby program uruchomil sie poprawnie nalezy podac podczas jego"<<endl;
	cout << "wywolywania od 1 do 5 argumentow, ktore podane s¹ w nawiasach przy nazwach funkcji." << endl;
	cout << "UWAGA!" << endl;
	cout << "Pierwszym argumentem powinien byc nr opcji!" << endl;
	cout << "Na koñcu linijki musi znajdowaæ siê przecinek (',')" << endl;
	cout << "Program posiada zaimplementowanych 6 funkcji obslugi:" << endl;
	cout << "1. Dodanie produktu." << endl;
	cout << "2. Usuniecie produktu." << endl;
	cout << "3. Dodanie klienta." << endl;
	cout << "4. Edycja danych klienta" << endl;
	cout << "5. Usuniecie klienta" << endl;
	cout << "6. Wypisanie klientow z danego produktu" << endl;
	cout << "Po kazdej wykonanej operacji plik z danymi jest nadpisywany przez nowe dane." << endl;
	cout << "W przypadku bledu podczas obslugi programu pojawi sie odpowiedni komunikat." << endl;
	cout << "Plik musi zawierac dane w postaci: nazwa_produktu:ID_klienta.imie nazwisko,ID_klienta2.imie2 nazwisko2, itd." << endl;
	cout << "Zycze przyjemnej obslugi!" << endl;
}
int main(int argc, char *argv[])
{
	produkty *head = NULL;
	produkty *tail = NULL;
	string wybor;
	wybor = argv[1];
	if (wybor == "-h")
	{
		wyswietl_pomoc();
	}
	else if (wybor == "6")
	{
		wczytaj_struktury_z_pliku(head, tail);
		wypisz_produkt(head, tail, argv[2]);
	}
	else
	{
		wczytaj_struktury_z_pliku(head, tail);
		if (wybor == "1")
		{
			dodaj_produkt(head, tail, argv[2]);
		}
		else if (wybor == "2")
		{
			usun_produkt(head, tail, argv[2]);
		}
		else if (wybor == "3")
		{
			dodawanie_klienta_do_produktu(head, tail, argv[2], argv[3], argv[4], argv[5]);
		}
		else if (wybor == "4")
		{
			edycja_klienta(head, tail, argv[2], argv[3], argv[4], argv[5]);
		}
		else if (wybor == "5")
		{
			usun_klienta(head, tail, argv[2], argv[3]);
		}
		else
		{
			cout << "Brak opcji!" << endl;
		}
		usun_struktury(head);
		wypisz_do_pliku(head);
	}
	exit(0);
	return 0;
}