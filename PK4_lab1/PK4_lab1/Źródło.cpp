#include <iostream>
#include "Nag³ówek.h"
using namespace std;
#define NUM 12
int main() {
	Class* tab[NUM];
	tab[0] = new Class(90);
	tab[1] = new Class(80);
	tab[2] = new Class(70);
	tab[3] = new Class(60);
	tab[4] = new Laboratory("Kowalski", 120);
	tab[5] = new Laboratory("Szeregowy", 110);
	tab[6] = new Laboratory("Skipper", 100);
	tab[7] = new Laboratory("Polok", 130);
	tab[8] = new PK4("Szeregowy", 220);
	tab[9] = new PK4("Kowalski", 210);
	tab[10] = new PK4("Polok", 200);
	tab[11] = new PK4("Skipper", 190);
	ShowNames(tab, NUM);
	Show(tab, NUM);
	Action(tab, NUM);
	Average(tab, NUM, "Kowalski");
	system("pause");
	return 0;
}