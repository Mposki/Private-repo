#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double a, b, c, x, y, delta;
	cout << "Wpisz a: ";
	cin >> a;

	cout << "Wpisz b: ";
	cin >> b;

	cout << "Wpisz c: ";
	cin >> c;

	cin.ignore(100, '\n');

	if (a == 0 && b == 0 && c == 0)
	{
		cout << "Brak wynikow. Rownanie tozsamosciowe!" << endl;
	}
	else
	{
		if (a == 0 && b != 0 && c != 00)
		{
			x = (-(b / c));
			cout << "Wynikiem jest 1 miejsce zerowe. Jest nim x=" << x << endl;
		}
		else
		{
			if (a == 0 && b == 0 && c != 0)
			{
				cout << "Brak wyniku. Brak miejsc zerowych!" << endl;
			}
			else
			{
				if (a == 0 && b != 0 && c == 0)
				{
					x = 0;
					cout << "Obecne jedno miejsce zerowe. Jest nim x=" << x << endl;
				}
				else
				{
					if (a != 0 && b != 0 && c == 0)
					{
						x = (-(b / a));
						y = 0;
						cout << "Obecne sa 2 wyniki: x1=" << y << " x2=" << x << endl;
					}
					else
					{
						if (a != 0 && b == 0 && c == 0)
						{
							x = 0;
							cout << "Obecny jest 1 wynik: x=" << x << endl;
						}
						else
						{
							if (a != 0 && b == 0 && c != 00)
							{
								x = (-sqrt(c / a));
								y = sqrt(c / a);
								cout << "Obecne sa 2 wyniki: x1=" << x << " i x2=" << y << endl;
							}
							else
							{
								if (a != 0 && b != 0 && c != 0)
								{
									delta = ((b*b) - (4 * a * c));

									if (delta < 0)
									{
										cout << "Brak wyniku. Delta ujemna!" << endl;
									}
									else
									{
										if (delta == 0)
										{
											x = (a / (2 * b));
											cout << "Obecny jest 1 wynik: x=" << x << endl;
										}
										else
										{
											x = (((-b) - (sqrt(delta))) / (4 * a));
											y = (((-b) + (sqrt(delta))) / (4 * a));
											cout << "Obecne sa 2 wyniki: x1=" << x << ", x2=" << y << endl;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cin.get();
	return 0;
}