#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Nag³ówek.h"

using namespace sf;
using namespace std;

void unactivation(vector <stolik>& tab_stolik, vector <krzeslo_z_lokietnikami>& tab_lokietki, vector <krzeslo_z_oparciem>& tab_oparcie, vector <szafa> &tab_szafa, vector <lampa> &tab_lampa, vector <lozko> &tab_lozko, vector <taboret>& tab_taboret, vector <paprotka>& tab_paprotka)
{
	for (auto i = 0; i < tab_taboret.size(); i++) tab_taboret[i].set_active(false);
	for (auto i = 0; i < tab_paprotka.size(); i++) tab_paprotka[i].set_active(false);
	for (auto i = 0; i < tab_lozko.size(); i++) tab_lozko[i].set_active(false);
	for (auto i = 0; i < tab_lampa.size(); i++) tab_lampa[i].set_active(false);
	for (auto i = 0; i < tab_szafa.size(); i++) tab_szafa[i].set_active(false);
	for (auto i = 0; i < tab_oparcie.size(); i++) tab_oparcie[i].set_active(false);
	for (auto i = 0; i < tab_lokietki.size(); i++) tab_lokietki[i].set_active(false);
	for (auto i = 0; i < tab_stolik.size(); i++) tab_stolik[i].set_active(false);
}
element* szukaj_aktywa(vector <stolik> &tab_stolik, vector <krzeslo_z_lokietnikami>& tab_lokietki, vector <krzeslo_z_oparciem>& tab_oparcie, vector <szafa>& tab_szafa, vector <lampa>& tab_lampa, vector <lozko>& tab_lozko, vector <taboret> &tab_taboret, vector <paprotka>& tab_paprotka)
{
	for (auto i = 0; i < tab_taboret.size(); i++) if (tab_taboret[i].get_active()) return &tab_taboret[i];
	for (auto i = 0; i < tab_paprotka.size(); i++)  if (tab_paprotka[i].get_active()) return &tab_paprotka[i];
	for (auto i = 0; i < tab_lozko.size(); i++)  if (tab_lozko[i].get_active()) return &tab_lozko[i];
	for (auto i = 0; i < tab_lampa.size(); i++)  if (tab_lampa[i].get_active()) return &tab_lampa[i];
	for (auto i = 0; i < tab_szafa.size(); i++)  if (tab_szafa[i].get_active()) return &tab_szafa[i];
	for (auto i = 0; i < tab_oparcie.size(); i++)  if (tab_oparcie[i].get_active()) return &tab_oparcie[i];
	for (auto i = 0; i < tab_lokietki.size(); i++)  if (tab_lokietki[i].get_active()) return &tab_lokietki[i];
	for (auto i = 0; i < tab_stolik.size(); i++)  if (tab_stolik[i].get_active()) return &tab_stolik[i];
	return NULL;

}
void left_clik(vector <stolik> &tab_stolik, vector <krzeslo_z_lokietnikami>& tab_lokietki, vector <krzeslo_z_oparciem>& tab_oparcie, vector <szafa>& tab_szafa, vector <lampa>& tab_lampa, vector <lozko>& tab_lozko, vector <taboret> &tab_taboret, vector <paprotka>& tab_paprotka, bool& sprawdzanie, int x1, int y1)
{
	for (auto i = 0; i < tab_paprotka.size() && sprawdzanie; i++)
	{
		if (tab_paprotka[i].get_positionX() < x1
			&& x1<tab_paprotka[i].get_positionX() + tab_paprotka[i].get_rozmiarX()
			&& y1>tab_paprotka[i].get_positionY()
			&& y1 < tab_paprotka[i].get_positionY() + tab_paprotka[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_paprotka[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_stolik.size() && sprawdzanie; i++)
	{
		if (tab_stolik[i].get_positionX() < x1
			&& x1<tab_stolik[i].get_positionX() + tab_stolik[i].get_rozmiarX()
			&& y1>tab_stolik[i].get_positionY()
			&& y1 < tab_stolik[i].get_positionY() + tab_stolik[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_stolik[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_szafa.size() && sprawdzanie; i++)
	{
		if (tab_szafa[i].get_positionX() < x1
			&& x1<tab_szafa[i].get_positionX() + tab_szafa[i].get_rozmiarX()
			&& y1>tab_szafa[i].get_positionY()
			&& y1 < tab_szafa[i].get_positionY() + tab_szafa[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_szafa[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_lokietki.size() && sprawdzanie; i++)
	{
		if (tab_lokietki[i].get_positionX() < x1
			&& x1<tab_lokietki[i].get_positionX() + tab_lokietki[i].get_rozmiarX()
			&& y1>tab_lokietki[i].get_positionY()
			&& y1 < tab_lokietki[i].get_positionY() + tab_lokietki[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_lokietki[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_oparcie.size() && sprawdzanie; i++)
	{
		if (tab_oparcie[i].get_positionX() < x1
			&& x1<tab_oparcie[i].get_positionX() + tab_oparcie[i].get_rozmiarX()
			&& y1>tab_oparcie[i].get_positionY()
			&& y1 < tab_oparcie[i].get_positionY() + tab_oparcie[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_oparcie[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_lampa.size() && sprawdzanie; i++)
	{
		if (tab_lampa[i].get_positionX() < x1
			&& x1<tab_lampa[i].get_positionX() + tab_lampa[i].get_rozmiarX()
			&& y1>tab_lampa[i].get_positionY()
			&& y1 < tab_lampa[i].get_positionY() + tab_lampa[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_lampa[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
	for (auto i = 0; i < tab_lozko.size() && sprawdzanie; i++)
	{
		if (tab_lozko[i].get_positionX() < x1
			&& x1<tab_lozko[i].get_positionX() + tab_lozko[i].get_rozmiarX()
			&& y1>tab_lozko[i].get_positionY()
			&& y1 < tab_lozko[i].get_positionY() + tab_lozko[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_lozko[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}

	for (auto i = 0; i < tab_taboret.size() && sprawdzanie; i++)
	{
		if (tab_taboret[i].get_positionX() < x1
			&& x1<tab_taboret[i].get_positionX() + tab_taboret[i].get_rozmiarX()
			&& y1>tab_taboret[i].get_positionY()
			&& y1 < tab_taboret[i].get_positionY() + tab_taboret[i].get_rozmiarY())
		{
			unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
			tab_taboret[i].set_active(true);
			sprawdzanie = false;
			break;
		}
	}
}
int main()
{
	RenderWindow window(VideoMode(800, 450), "Menadzer wnetrz");
	Event event;

	/*Texture texture;
	texture.loadFromFile("grafika/cursor.png");
	Sprite sprite(texture);*/



	vector <stolik> tab_stolik;
	vector <krzeslo_z_lokietnikami> tab_lokietki;
	vector <krzeslo_z_oparciem> tab_oparcie;
	vector <szafa> tab_szafa;
	vector <lampa> tab_lampa;
	vector <lozko> tab_lozko;
	vector <taboret> tab_taboret;
	vector <paprotka> tab_paprotka;



	Font font;
	font.loadFromFile("Font/Lato-Regular.ttf");
	Text text1, text2;
	text1.setFont(font);
	text2.setFont(font);
	text1.setString("Wizualizacja");
	text2.setString("Menu");
	text1.setFillColor(Color::Black);
	text2.setFillColor(Color::Black);
	text1.setPosition(190, 25);
	text2.setPosition(610, 25);
	text1.setCharacterSize(15);
	text2.setCharacterSize(15);

	window.setMouseCursorVisible(false);
	Texture cursor2, cursor1;
	cursor1.loadFromFile("grafika/cursor1.jpg");
	cursor2.loadFromFile("grafika/cursor2.jpg");
	Sprite cursor(cursor1);
	bool cursor_check = false;


	Texture t1, t2, t3, t4, t5, t6, t7, t8;

	t1.loadFromFile("grafika/4.png");
	t2.loadFromFile("grafika/2.png");
	t3.loadFromFile("grafika/3.png");
	t4.loadFromFile("grafika/7.png");
	t5.loadFromFile("grafika/8.png");
	t6.loadFromFile("grafika/1.png");
	t7.loadFromFile("grafika/6.png");
	t8.loadFromFile("grafika/5.png");


	Sprite doniczkaX(t1), krzeslozlokciamiX(t2), krzeslozoparciemX(t3), lampaX(t4), lozkoX(t5), stolX(t6), szafaX(t7), taboretX(t8);

	doniczkaX.setPosition(590, 150);
	krzeslozlokciamiX.setPosition(670, 70);
	krzeslozoparciemX.setPosition(515, 150);
	lampaX.setPosition(680, 240);
	lozkoX.setPosition(580, 315);
	stolX.setPosition(510, 60);
	szafaX.setPosition(515, 230);
	taboretX.setPosition(670, 150);

	RectangleShape wizualizacja(Vector2f(400, 350));
	wizualizacja.setPosition(50, 50);

	RectangleShape wizualizacja_ramka(Vector2f(402, 352));
	wizualizacja_ramka.setPosition(49, 49);
	wizualizacja_ramka.setFillColor(Color(0, 0, 0, 255));			//kolor czarny

	RectangleShape menu(Vector2f(250, 350));
	menu.setPosition(500, 50);

	RectangleShape menu_ramka(Vector2f(252, 352));
	menu_ramka.setPosition(499, 49);
	menu_ramka.setFillColor(Color(0, 0, 0, 255));



	window.setKeyRepeatEnabled(false);
	int x1, y1;

	bool sprawdzanie = true;

	element *tmp;


	while (window.isOpen())
	{

		window.clear(Color::White);
		window.pollEvent(event);
		switch (event.type)
		{
		case Event::Closed:
			tab_stolik.clear();
			tab_lampa.clear();
			tab_lokietki.clear();
			tab_lozko.clear();
			tab_oparcie.clear();
			tab_szafa.clear();
			tab_taboret.clear();
			tab_paprotka.clear();

			window.close();
			break;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) window.close();
			break;
		case Event::EventType::MouseButtonPressed:
			if (Mouse::Button::Left == event.mouseButton.button)
			{
				cout << "Left mouse botton" << endl;
				x1 = Mouse::getPosition(window).x;
				y1 = Mouse::getPosition(window).y;

				left_clik(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka, sprawdzanie, x1, y1);

				if (sprawdzanie == true)																			//jesli nie kliknie sie na obiekt to przestaje one byc aktywne
				{
					unactivation(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				}
			}
			sprawdzanie = true;
			break;
		case Event::EventType::TextEntered:
			//cout << event.text.unicode << endl;
			if (event.text.unicode == 56)
			{
				//cout << "8" << endl;
				lozko *x = new lozko();
				tab_lozko.push_back(*x);
			}

			else if (event.text.unicode == 49)
			{
				//cout << "1" << endl;
				stolik *x = new stolik();
				tab_stolik.push_back(*x);
			}
			else if (event.text.unicode == 50)
			{
				//cout << "2" << endl;
				krzeslo_z_lokietnikami *x = new krzeslo_z_lokietnikami();
				tab_lokietki.push_back(*x);
			}
			else if (event.text.unicode == 51)
			{
				//cout << "3" << endl;
				krzeslo_z_oparciem *x = new krzeslo_z_oparciem();
				tab_oparcie.push_back(*x);
			}
			else if (event.text.unicode == 52)
			{
				//cout << "4" << endl;
				paprotka *x = new paprotka();
				tab_paprotka.push_back(*x);
			}
			else if (event.text.unicode == 53)
			{
				//cout << "5" << endl;
				taboret *x = new taboret();
				tab_taboret.push_back(*x);
			}
			else if (event.text.unicode == 54)
			{
				//cout << "6" << endl;
				szafa *x = new szafa();
				tab_szafa.push_back(*x);
			}
			else if (event.text.unicode == 55)
			{
				//cout << "7" << endl;
				lampa *x = new lampa();
				tab_lampa.push_back(*x);
			}

			else if (event.text.unicode == 119)					//przesuniecia WASD
			{
				//cout << "W" << endl;				
				tmp = szukaj_aktywa(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				if (tmp) tmp->change_duszek_position(0, -10);


			}
			else if (event.text.unicode == 97)
			{
				//	cout << "A" << endl;
				tmp = szukaj_aktywa(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				if (tmp) tmp->change_duszek_position(-10, 0);
			}

			else if (event.text.unicode == 115)
			{
				//	cout << "S" << endl;
				tmp = szukaj_aktywa(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				if (tmp) tmp->change_duszek_position(0, 10);
			}


			else if (event.text.unicode == 100)
			{
				//	cout << "D" << endl;
				tmp = szukaj_aktywa(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				if (tmp) tmp->change_duszek_position(10, 0);
			}

			else if (event.text.unicode == 113)				//obrot w lewo
			{
				//	cout << "Q" << endl;
				tmp = szukaj_aktywa(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				if (tmp) tmp->rotate_left();
			}
			else if (event.text.unicode == 101)				//obrot w prawo
			{
				//cout << "E" << endl;
				tmp = szukaj_aktywa(tab_stolik, tab_lokietki, tab_oparcie, tab_szafa, tab_lampa, tab_lozko, tab_taboret, tab_paprotka);
				if (tmp) tmp->rotate_right();
			}
			else if (event.text.unicode == 117)				//usuniecie elementu [klawisz U]
			{
				//cout << "U" << endl;
				for (int i = 0; i < tab_taboret.size(); i++) if (tab_taboret[i].get_active()) tab_taboret.erase(tab_taboret.begin() + i);
				for (int i = 0; i < tab_paprotka.size(); i++)  if (tab_paprotka[i].get_active()) tab_paprotka.erase(tab_paprotka.begin() + i);
				for (int i = 0; i < tab_lozko.size(); i++)  if (tab_lozko[i].get_active())	tab_lozko.erase(tab_lozko.begin() + i);
				for (int i = 0; i < tab_lampa.size(); i++)  if (tab_lampa[i].get_active()) tab_lampa.erase(tab_lampa.begin() + i);
				for (int i = 0; i < tab_szafa.size(); i++)  if (tab_szafa[i].get_active()) tab_szafa.erase(tab_szafa.begin() + i);
				for (int i = 0; i < tab_oparcie.size(); i++)  if (tab_oparcie[i].get_active()) tab_oparcie.erase(tab_oparcie.begin() + i);
				for (int i = 0; i < tab_lokietki.size(); i++)  if (tab_lokietki[i].get_active()) tab_lokietki.erase(tab_lokietki.begin() + i);
				for (int i = 0; i < tab_stolik.size(); i++)  if (tab_stolik[i].get_active()) tab_stolik.erase(tab_stolik.begin() + i);

			}
			break;
			/*	case Event::EventType::MouseMoved:
			cout << event.mouseMove.x << " . " << event.mouseMove.y << endl;
			break;*/
		}

		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		if (cursor_check) cursor.setTexture(cursor2);
		else cursor.setTexture(cursor1);


		window.draw(menu_ramka);
		window.draw(menu);

		window.draw(wizualizacja_ramka);
		window.draw(wizualizacja);

		window.draw(text1);
		window.draw(text2);

		window.draw(stolX);
		window.draw(krzeslozlokciamiX);
		window.draw(krzeslozoparciemX);
		window.draw(doniczkaX);
		window.draw(taboretX);
		window.draw(szafaX);
		window.draw(lampaX);
		window.draw(lozkoX);


		for (auto i = 0; i < tab_stolik.size(); i++)	window.draw(tab_stolik[i].get_sprite());					//rysowanie poszczegolnych obiektow
		for (auto i = 0; i < tab_lokietki.size(); i++) window.draw(tab_lokietki[i].get_sprite());
		for (auto i = 0; i < tab_oparcie.size(); i++) window.draw(tab_oparcie[i].get_sprite());
		for (auto i = 0; i < tab_szafa.size(); i++) window.draw(tab_szafa[i].get_sprite());
		for (auto i = 0; i < tab_lampa.size(); i++) window.draw(tab_lampa[i].get_sprite());
		for (auto i = 0; i < tab_lozko.size(); i++) window.draw(tab_lozko[i].get_sprite());
		for (auto i = 0; i < tab_taboret.size(); i++) window.draw(tab_taboret[i].get_sprite());
		for (auto i = 0; i < tab_paprotka.size(); i++) window.draw(tab_paprotka[i].get_sprite());

		window.draw(cursor);


		window.waitEvent(event);

		window.display();
	}


	return 0;
}