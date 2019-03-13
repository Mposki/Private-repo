#include <stdio.h>

void show(int a) {
	for (int i = 0; i < 10; i++) {
		if (a == i)
			putchar(a + 48);
	}
}
int main() {
	printf(":%16s:\n", "Hello world!");
	printf(":%-16s:\n", "Hello world!");
	printf("%+d\n", 12);
	printf("%+d\n", -13);
	printf("%.4f\n", 1.532801);
	printf("%#x\n", 0);
	printf("%#x\n", 128);
	printf("%#.4x\n", 128);
	printf("%u\n", -10);
	show(6);
	printf("\n");
	//---------------
	char text[12];
	int liczba;
	printf("%s\n", "Podaj swoje imie:");
	scanf_s("&\s", text);
	printf("%s\n", "Witaj ");
	printf("%s\n", text);
	printf("%s\n", "Podaj liczbe dziesietna:");
	scanf_s("&\i", liczba);
	printf("%s\n", "Wprowadzona liczba: "); //wprowadzenie b³êdnej danej
	printf("%i\n", liczba);
	system("pause");
	return 0;
}