#include <iostream>
#include <regex>
#include "Regrex.h"
using namespace std;

int main()
{
	//ZADANIE 1
	cout << "zadanie 1:\n";
	string s = "kod pocztowy: 44-280";
	regex reg1("\\d{2}-\\d{3}");
	smatch match;
	regex_search(s, match, reg1);
	cout << "znaleziony kod: " << match.str() << "\n"
		<< "prefix: " << match.prefix().str()
		<< "\nsuffix:" << match.suffix().str() << "\n";
	//ZADANIE 2
	cout << "\nzadanie 2:\n";
	string tekst = "z@l.y A glupi, a glupi wy na kim sie mlelo na was skrupi? mail.fajnyjest@fajny.pl To poki o wskrzeszeniu Polski byla rada"
		"O dobru pospolitym, takisobie.@op.pl glupi, u was zwada ?"
		"Nie mozna bylo, mail@gmail.com glupi, ani siê rozmowic,"
		"Glupi, ani karara.marara@student.polsl.pl porzadku, ani postanowic"
		"Wodza nad wami, macko.nad.mackami@polsl.pl glupi! a niech no kto podda"
		"Osobiste urazy, glupi, u was zgoda! zly.@op.pl smi.smi.smi.smi.smi@o2.pl";

	regex reg2("(([A-z]+\\w+)(?:\\.(?:[A-z]+\\w*))*)@((?:[A-z]+\\w+)(?:\\.(?:[A-z]+\\w*))*)\\.([a-z]{2,3})");

	PrintMatches2(tekst, reg2);

	cout << "\nzadanie 4:\n";
	//ZADANIE 4
	string tekst2 = "moj email: blabla@gmail.com albo blabla@polsl.student.pl";
	cout << '\n' << tekst2 << '\n' << regex_replace(tekst2, reg2, "Michal@$3.$5") << endl;;

	system("pause");
	return 0;
}