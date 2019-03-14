#include "Nag≥Ûwek.h"
#include <iostream>
#include <exception>
using namespace std;

int main() {
	awaria_samochodu* tab[10];
	tab[0] = new awaria_samochodu(123);
	tab[1] = new awaria_samochodu(456);
	tab[2] = new awaria_samochodu(789);
	tab[3] = new awaria_silnika(123, 111);
	tab[4] = new awaria_silnika(456, 222);
	tab[5] = new awaria_silnika(789, 333);
	tab[6] = new awaria_swiecy(123, 111, 777);
	tab[7] = new awaria_swiecy(456, 222, 888);
	tab[8] = new awaria_swiecy(789, 333, 999);
	tab[9] = NULL;

	for (int i = 0; i < 10; i++) {
		try {
			if (typeid(*tab[i]).name() == typeid(awaria_samochodu).name()) {
				throw  tab[i];
			}
			if (typeid(*tab[i]).name() == typeid(awaria_silnika).name()) {
				throw  (dynamic_cast<awaria_silnika*>(tab[i]));
			}
			if (typeid(*tab[i]).name() == typeid(awaria_swiecy).name()) {
				throw  (dynamic_cast<awaria_swiecy*>(tab[i]));
			}
		}
		catch (awaria_samochodu e) { //jak jest przekazywane jako wskaünik, to nie dzia≥a, a jak teraz, to nie ≥apie pierwszego elementu
			cout << "Wyjatek Awaria samochodu" << endl;
			e.naprawa();
		}
		catch (awaria_swiecy *e) {
			cout << "Wyjatek Awaria swiecy" << endl;
			e->naprawa();
		}
		catch (awaria_silnika *e) {
			cout << "Wyjatek Awaria silnika" << endl;
			e->naprawa();
		}
		catch (...) {
			cout << "Wyjatek!" << endl;
		}
	}
	try {
		throw awaria_swiecy(9000, 150, 55);
	}
	catch (awaria_swiecy &e) {
		cout << "Obsluga awari swiecy" << endl;
		try {
			throw;
		}
		catch (awaria_silnika &e) {
			cout << "Obsluga awari silnika" << endl;
			try {
				throw;
			}
			catch (awaria_samochodu &e) {
				cout << "Obsluga awari samochodu" << endl;
			}
			catch (awaria_silnika &e) {
				cout << "Obsluga awari silnika" << endl;
			}
		}
	}
	catch (...) {
		cout << "Wyjatek!" << endl;
	}
	getchar();
	return 0;
}