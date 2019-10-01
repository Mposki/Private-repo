#include <stdio.h>
#include <string.h>
#include <ctype.h>>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
//typedef enum { TRUE = 1, FALSE = 0 } bool;
#define ROZMIAR_SLOWNIKA 16384
#define ROZMIAR_BUFORA 14
#define ROZMIAR 1000
typedef struct dane
{
	char *ciag_znakow;
	int indeks_polozenia;
	char *indeks_kompresji;
	dane *lewo;
	dane *prawo;
	dane *rodzic;
}dane;
dane *tmp;
//dodaje wezel do drzewa o korzeniu drzewo
int sprawdz(dane* tmp, char *bufor)
{
	int dlugosc1 = strlen(tmp->ciag_znakow);
	int dlugosc2 = strlen(bufor);
	if (dlugosc1 = dlugosc2)
		return 1;
	else
		return 0;
}
dane *szukaj_ciagu(dane *drzewo, char *bufor)
{
	int dlugosc1 = strlen(drzewo->ciag_znakow);
	int dlugosc2 = strlen(bufor);
	//jezeli wezel ma szukana wartosc to odnalezlismy go
	if (strcmp(drzewo->ciag_znakow, bufor) == 0) return drzewo;
	//jezeli szukana wartosc jest mniejsza to szukamy w lewym poddrzewie o ile istnieje
	else if (drzewo->lewo != NULL && dlugosc2 < dlugosc1) return szukaj(drzewo->lewo, bufor);
	//jezeli szukana wartosc jest wieksza to szukamy w prawym poddrzewie o ile istnieje     
	else if (drzewo->prawo != NULL && dlugosc2 > dlugosc1) return szukaj(drzewo->prawo, bufor);
	return NULL;
}
int dodaj_do_drzewa(dane *drzewo, char *bufor, int indeks, char *indeks_kompresji)
{
	do
	{
		//jezeli drzewo jest puste to dodaj korzen
		seek(tmp->ciag_znakow, 0, SEEK_END);
		if (tmp == NULL)
		{
			tmp = (dane*)malloc(sizeof *tmp);
			tmp->ciag_znakow, bufor;
			tmp->indeks_polozenia, indeks;
			tmp->indeks_kompresji, indeks_kompresji;
			tmp->lewo = NULL;
			tmp->prawo = NULL;
			tmp->rodzic = NULL;
		}
		//jezeli zadana wartosc jest mniejsza od korzenia idz do lewego poddrzewa
		else if (sprawdz(tmp, bufor) == 1)
		{
			//jezeli lewe poddrzewo istnieje wywolaj dla niego ta funkcje rekurencyjnie
			if (drzewo->lewo != NULL)
			{
				dodawanie(drzewo->lewo, bufor, indeks, indeks_kompresji);
			}
			//jezeli lewe poddrzewo nie istnieje dodaj nowy wezel o zadanej wartosci
			else
			{
				dane *nowe = (dane*)malloc(sizeof *tmp);
				nowe->ciag_znakow, bufor;
				nowe->indeks_polozenia, indeks;
				nowe->indeks_kompresji, indeks_kompresji;
				nowe->lewo = NULL;
				nowe->prawo = NULL;
				nowe->rodzic = drzewo;
				drzewo->lewo = nowe;
			}
		}
		//jezeli zadana wartosc jest wieksza lub rowna korzeniowi idz do prawego poddrzewa   
		else
		{
			//jezeli prawe poddrzewo istnieje wywolaj dla niego ta funkcje rekurencyjnie      
			if (drzewo->lewo != NULL)
			{
				dodawanie(drzewo->lewo, bufor, indeks, indeks_kompresji);
			}
			//jezeli prawe poddrzewo nie istnieje dodaj nowy wezel o zadanej wartosci     
			else
			{
				dane *nowe = (dane*)malloc(sizeof *tmp);
				nowe->ciag_znakow, bufor;
				nowe->indeks_polozenia, indeks;
				nowe->indeks_kompresji, indeks_kompresji;
				nowe->lewo = NULL;
				nowe->prawo = NULL;
				nowe->rodzic = drzewo;
				drzewo->lewo = nowe;
			}
		}
		return 0;
	} while (tmp->indeks_polozenia < ROZMIAR_SLOWNIKA);
}
void usun_drzewo(dane *head)
{

}
void kompresja(dane *drzewo, char *plik_wejsciowy)
{
	FILE *plik_kompresowany = fopen(plik_wejsciowy, "r");
	FILE *skompresowany_plik = fopen("kompresja.txt", "w");
	if (plik_kompresowany = NULL)
		printf("Blad pliku do kompresji!");
	else
	{
		char *przechowaj_wiersz = calloc(ROZMIAR, sizeof(char));
		fgets(przechowaj_wiersz, ROZMIAR, plik_kompresowany);
		while (przechowaj_wiersz != NULL)
		{
			int i;
			char *znak;
			char *bufor1 = calloc(ROZMIAR_BUFORA, sizeof(char));//bez znaku
			char *bufor2 = calloc(ROZMIAR_BUFORA, sizeof(char));//do dodania znaku
			char *indeks_kompresji = calloc(ROZMIAR_BUFORA + 2, sizeof(char));
			for (i = 0; i < ROZMIAR; i++)
			{
				znak = calloc(1, sizeof(char));
				znak = przechowaj_wiersz[i];
				strcpy(bufor2, bufor1);
				strcat(bufor2, znak);
				szukaj_ciagu(tmp, bufor1);
				int indeks = tmp->indeks_polozenia;
				strcat(indeks_kompresji, indeks);
				strcat(indeks_kompresji, znak);
				strcat(indeks_kompresji, ";");
				if (szukaj_ciagu(tmp, bufor2) != NULL || i == ROZMIAR_BUFORA - 1)
				{
					fwrite(indeks_kompresji, 1, ROZMIAR_BUFORA + 2, skompresowany_plik);/*zapisz do pliku*/
					if (szukaj_ciagu(tmp, bufor2) != NULL)
						dodaj_do_drzewa(tmp, bufor2, indeks + 1, indeks_kompresji);
					free(bufor1);
					free(bufor2);
				}
				free(znak);
			}
		}
		free(przechowaj_wiersz);
	}
}
void help()
{
	printf("Witam w programie kompresuj¹cym zawartoœæ plików tekstowych! \n Program dzia³a w oparciu o algorytm LZ78 i obsluguje pliki w formacie .txt. \n Uruchamiajac plik trzeba wprowadziæ 1 argument:\n");
	printf("- plik z zawartoscia do kompresji/dekompresji;");
	printf("Wyj¹tkiem jest uruchamianie pomocy, wtedy podajemy -h jako argument! \n");
	printf("Obsluga bledow: \n");
	printf("Blad liczby argumentow wywolania funkcji- niewlasciwa liczba argumentow potrzebna do uruchomienia programu; wlasciwa liczba to 4 argumenty");
	printf("Blad pliku do kompresji- plik jest pusty lub nieistnieje");
}
int main(int argc, char* argv[])
{
	if (argc != 2)
		printf("Blad liczby argumentow wywolania funkcji!");
	else
		if (strcmp(argv[1], "-h") == 0)
			help();
		else
		{
			char *bufor = calloc(1, sizeof(char));
			int indeks = 0;
			char *indeks_kompresji = calloc(2, sizeof(char));
			strcat(bufor, NULL);
			strcat(indeks_kompresji, "00");
			tmp = NULL;
			char *plik_wejsciowy = malloc(20);
			plik_wejsciowy = strdup(argv[1]);
			dodaj_do_drzewa(tmp, *bufor, indeks, *indeks_kompresji);
			kompresja(tmp, plik_wejsciowy);
			usun_drzewo(tmp);
		}
	system("PAUSE");
	_CrtDumpMemoryLeaks();
	return 0;
}