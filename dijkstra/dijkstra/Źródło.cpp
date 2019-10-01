#include <iostream>

using namespace std;

struct dane {
	int dystans;
	int poprzednik;
	bool odwiedzony;
};

int szukajMinimum(int n, dane* tab) {
	int min = -1;
	int mindist = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (!tab[i].odwiedzony && tab[i].dystans < mindist) {
			min = i;
			mindist = tab[i].dystans;
		}
	}
	return min;
}

dane* Dijkstra(int** macierz, int n, int start) {
	dane* tab = new dane[n];
	for (int i = 0; i < n; i++) {
		tab[i].dystans = (i == start) ? 0 : INT_MAX;
		tab[i].odwiedzony = false;
		tab[i].poprzednik = -1;
	}
	int u = szukajMinimum(n, tab);
	while (u != -1) {
		tab[u].odwiedzony = true;
		for (int i = 0; i < n; i++) {
			if (macierz[u][i] > 0 && tab[u].dystans + macierz[u][i] < tab[i].dystans) {
				tab[i].dystans = tab[u].dystans + macierz[u][i];
				tab[i].poprzednik = u;
			}
		}
		u = szukajMinimum(n, tab);
	}
	return tab;
}

void wypiszdane(int i, dane d) {
	cout << i << "\t";
	if (!d.odwiedzony) {
		cout << "nieodwiedzony";
	}
	else {
		if (d.poprzednik == -1)
			cout << "brak";
		else cout << d.poprzednik;
		cout << "\t" << d.dystans;
	}
	cout << endl;
}

int main() {
	int n, s;
	cout << "Ile wierzcholkow ma graf?\n n = ";
	cin >> n;
	cout << "Podaj wierzcholek poczatkowy\n s = ";
	cin >> s;
	cout << "Podaj macierz:" << endl;
	int** macierz = new int*[n];
	for (int i = 0; i < n; i++) {
		macierz[i] = new int[n];
		for (int j = 0; j < n; j++)
			cin >> macierz[i][j];
	}
	dane* tab = Dijkstra(macierz, n, s);
	cout << "Wezel\tPoprz.\tDystans" << endl;
	for (int i = 0; i < n; i++)
		wypiszdane(i, tab[i]);
	system("pause");
	return 0;
}