#include "Regrex.h"
#include <iostream>
#include <regex>
using namespace std;

//ZADANIE 2A
void PrintMatches(string str, regex reg)
{
	smatch matches;

	while (regex_search(str, matches, reg))
	{
		cout << matches.str() << "\n";
		str = matches.suffix().str();
		cout << "\n";
	}
}
//ZADANIE 2B
void PrintMatches2(string str, regex reg)
{
	sregex_iterator currentMatch(str.begin(), str.end(), reg);
	sregex_iterator lastMatch;
	while (currentMatch != lastMatch) {
		smatch match = *currentMatch;
		cout << "\nemail: " << match[0] << "\n";
		cout << "user: " << match[1] << "\n";
		cout << "domain: " << match[3] << "\n";
		cout << "country: " << match[4] << "\n";

		currentMatch++;
	}
	cout << endl;
}