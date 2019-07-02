#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct Daty {
	int dzien;
	int miesiac;
	int rok;
	Daty *next;
	Daty *back;
};

Daty *szukaj_najstarszej(Daty *head) {
	Daty *temp = (Daty*)malloc(sizeof(Daty));
	temp = head;
	head = head->next;
	do {
		if (head->rok < temp->rok) {
			temp = head;
			head = head->next;
		}
		else if (head->rok = temp->rok) {
			if (head->miesiac < temp->miesiac) {
				temp = head;
				head = head->next;
			}
			else if (head->miesiac = temp->miesiac) {
				if (head->dzien < temp->dzien) {
					temp = head;
					head = head->next;
				}
				else {
					head = head->next;
				}
			}
			else {
				head = head->next;
			}
		}
		else {
			head = head->next;
		}
	} while (head->next != NULL);
	return temp;
}

int main(int argc, char *argv[]) {
	Daty *head = NULL;
	char data[10];
	const char *plik_wejsciowy;
	char plik_dzien[2];
	char plik_miesiac[2];
	char plik_rok[4];
	plik_wejsciowy = argv[1];
	FILE *plik;
	if ((plik = fopen(plik_wejsciowy, "w")) == NULL) {
		printf("Brak pliku wejsciowego!/n");
		exit(100);
	}
	else
	{
		while (!feof(plik))
		{
			fscanf(plik, "%s", data);
//			fgets(data, 10, plik);
			for (int i = 0; i < 10; i++) {
				if (i == 2 || i == 5) {
					i++;
				}
				else {
					for (int t = 0; t < 2; t++) {
						plik_dzien[t] == data[i];
					}
					for (int t = 0; t < 2; t++) {
						plik_miesiac[t] == data[i];
					}
					for (int t = 0; t < 4; t++) {
						plik_rok[t] == data[i];
					}
				}
+			}
			head->dzien = atoi(plik_dzien);
			head->miesiac = atoi(plik_miesiac);
			head->rok = atoi(plik_rok);
			head = head->next;
		}
	}
	fclose(plik);
	Daty *temp = (Daty*)malloc(sizeof(Daty));
	while (head->back != NULL) {
		head = head->back;
	}
	temp = szukaj_najstarszej(head);
	printf("Najstarsza data w pliku to: ", temp->dzien, "-", temp->miesiac, "-", temp->rok);
	return 0;
	system("pause");
}