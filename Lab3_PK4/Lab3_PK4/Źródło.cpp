#include "Nag��wek.h"
#include <iostream>
using namespace std;

int main() {
	float a = 6.12, b = 5.76;
	double c = 6.122254441239987, d = 12.155763225974621;
	cout << "Mnozenie: " << mnoz<float>(a, b) << endl;
	cout << "Dzielenie: " << dziel<float>(a, b) << endl;
	cout << "Wieksze: " << max<float>(a, b) << endl;
	cout << "Mnozenie: " << mnoz<double>(c, d) << endl;
	cout << "Dzielenie: " << dziel<double>(c, d) << endl;
	cout << "Wieksze: " << max<double>(c, d) << endl;
	//wype�nianie samej klasy pacjent
	pacjent<float, double> pacjent1("Tomasz", "Kowalski", "Robo�", 39.6, 1.17754);
	pacjent<int, float> pacjent2("Bo�ydar", "�l�ski", "Kupczyk", 37, 2.0012);
	pacjent<int, double> pacjent3("Marek", "Czekalski", "Gosik", 37, 1.971525512);
	//pe�na inicjalizacja klasy lista_pacjent�w
	lista_pacjentow<pacjent<float, double>, float, double> pacjenci;
	pacjenci.add("Tomasz", "Kowalski", "Robo�", 39.6, 1.17754);
	pacjenci.add("Bo�ydar", "�l�ski", "Kupczyk", 37, 2.0012);
	pacjenci.add("Marek", "Czekalski", "Gosik", 37, 1.971525512);
	getchar();
	return 0;
}