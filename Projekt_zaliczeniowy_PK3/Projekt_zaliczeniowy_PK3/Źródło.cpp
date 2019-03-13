#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Klasy.h"
#include "Funkcje.h"
using namespace sf;
using namespace std;

int main()
{
	//renderowanie okna obs�ugi programu
	RenderWindow okno_program(VideoMode(500, 450), "Aranzacja");
	okno_program.setMouseCursorVisible(true);//ustawiam widoczno�� kursora w oknie g��wnym
	okno_program.setKeyRepeatEnabled(true); //umo�liwiam potwarzanie klikni��
	//inicjalizacja pola roboczego
	RectangleShape pole_robocze(Vector2f(400, 350));//pole robocze
	pole_robocze.setPosition(50, 50);//punkt zaczepienia pola roboczego
	pole_robocze.setFillColor(Color::White); //wype�niam pole robocze kolorem bia�ym
	//inicjalizacja ramki
	RectangleShape ramka(Vector2f(402, 352));//ramka wok� pola roboczego (granica dzia�ania); w rzeczywisto�ci to pe�ny, czarny prostok�t
	ramka.setPosition(49, 49); //ramka zaczyna si� 1 piksel przed polem roboczym
	ramka.setFillColor(Color::Black); //wype�niam ramk� kolorem czarnym
	//inicjalizacja kontener�w obiekt�w
	vector <Biurko> tab_biurko;
	vector <Fotel> tab_fotel;
	vector <Krzeslo> tab_krzeslo;
	vector <Szafa> tab_szafa;
	vector <Lampa> tab_lampa;
	vector <Lozko> tab_lozko;
	vector <Kwiat> tab_kwiat;
	//renderowanie okna pomocy z zawarto�ci�
	RenderWindow okno_pomoc(VideoMode(300, 400), "Pomoc");
	Texture menu;
	menu.loadFromFile("grafika/menu.png");
	Sprite menuX(menu);
	menuX.setPosition(0, 0);
	okno_pomoc.setMouseCursorVisible(true);
	int x, y; //pozycja myszki
	//incjalizacja zmiennej, od kt�rej zale�y czy klikni�to poza obszarem
	bool sprawdz = true;
	//incjalizacja elementu klasy g��wnej
	Element *temp;
	//zmienne potrzebne do zapisu do pliku
	Image zapis;
	Vector2u window_size;
	Texture window_capture;
	//zmienna event od kt�rej zale�y dzia�anie programu
	Event event;
	//p�tla g��wna programu
	while (okno_program.isOpen())
	{
		okno_program.clear(Color(234, 230, 202));
		okno_program.pollEvent(event);
		switch (event.type)
		{
		case Event::Closed:
			window_size = okno_program.getSize();
			window_capture.create(window_size.x, window_size.y);
			window_capture.update(okno_program);
			zapis = window_capture.copyToImage();
			zapis.saveToFile("C:/Users/Maike/source/repos/Projekt_zaliczeniowy_PK3/Projekt_zaliczeniowy_PK3/aranzacja.png");
			okno_program.close();
			break;;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) {
				window_size = okno_program.getSize();
				window_capture.create(window_size.x, window_size.y);
				window_capture.update(okno_program);
				zapis = window_capture.copyToImage();
				zapis.saveToFile("C:/Users/Maike/source/repos/Projekt_zaliczeniowy_PK3/Projekt_zaliczeniowy_PK3/aranzacja.png");
				okno_program.close();
			}
			//PRZESUNI�CIA OSIOWE
			else if (event.key.code == Keyboard::Up) {//do g�ry
				temp = szukaj_aktywnego_elementu(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				if (temp)
					temp->zmie�_pozycj�_obiekt(0, -10);//x= x- 10
			}
			else if (event.key.code == Keyboard::Down) {//na d�
				temp = szukaj_aktywnego_elementu(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				if (temp)
					temp->zmie�_pozycj�_obiekt(0, 10);//x = x + 10
			}
			else if (event.key.code == Keyboard::Left) {//w lewo
				temp = szukaj_aktywnego_elementu(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				if (temp)
					temp->zmie�_pozycj�_obiekt(-10, 0);//y = y -10
			}
			else if (event.key.code == Keyboard::Right) {//w prawo
				temp = szukaj_aktywnego_elementu(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				if (temp)
					temp->zmie�_pozycj�_obiekt(10, 0);//y = y + 10
			}
			else if (event.key.code == Keyboard::Delete) //usu� obiekt
				usun_element(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
			break;
		case Event::EventType::MouseButtonPressed:
			if (Mouse::Button::Left == event.mouseButton.button) {
				//przechwyt pozycji kursora
				x = Mouse::getPosition(okno_program).x;
				y = Mouse::getPosition(okno_program).y;
				myszka(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat, sprawdz, x, y);
				//je�li klikni�to poza obiekt
				if (sprawdz == true){
					deaktywuj(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				}
			}
			sprawdz = true;
			break;
		case Event::EventType::TextEntered:
			if (event.text.unicode == 49) {
				Krzeslo *x = new Krzeslo();
				tab_krzeslo.push_back(*x);//nowy obiekt o tkesturze x dodany na koniec kontenera
			}
			else if (event.text.unicode == 50) {
				Fotel *x = new Fotel();
				tab_fotel.push_back(*x);
			}
			else if (event.text.unicode == 51) {
				Lozko *x = new Lozko();
				tab_lozko.push_back(*x);
			}
			else if (event.text.unicode == 52) {
				Szafa *x = new Szafa();
				tab_szafa.push_back(*x);
			}
			else if (event.text.unicode == 53) {
				Kwiat *x = new Kwiat();
				tab_kwiat.push_back(*x);
			}
			else if (event.text.unicode == 54) {
				Lampa *x = new Lampa();
				tab_lampa.push_back(*x);
			}
			else if (event.text.unicode == 55) {
				Biurko *x = new Biurko();
				tab_biurko.push_back(*x);
			}
			//OBROTY WOKӣ PUNKTU ZACZEPU
			//obr�t w lewo L
			else if (event.text.unicode == 108) {
				temp = szukaj_aktywnego_elementu(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				if (temp)
					temp->pochyl_lewo();
			}
			//obr�t w prawo P
			else if (event.text.unicode == 112) {
				temp = szukaj_aktywnego_elementu(tab_biurko, tab_fotel, tab_krzeslo, tab_szafa, tab_lampa, tab_lozko, tab_kwiat);
				if (temp)
					temp->pochyl_prawo();
			}
			break;
		}
		//wy�witlanie podstawowej zawarto�ci okien
		okno_pomoc.draw(menuX);
		okno_program.draw(ramka);
		okno_program.draw(pole_robocze);
		//rysowanie element�w
		for (auto i = 0; i < tab_kwiat.size(); i++)
			okno_program.draw(tab_kwiat[i].pobierz_obiekt());
		for (auto i = 0; i < tab_biurko.size(); i++)
			okno_program.draw(tab_biurko[i].pobierz_obiekt());
		for (auto i = 0; i < tab_szafa.size(); i++)
			okno_program.draw(tab_szafa[i].pobierz_obiekt());
		for (auto i = 0; i < tab_fotel.size(); i++)
			okno_program.draw(tab_fotel[i].pobierz_obiekt());
		for (auto i = 0; i < tab_krzeslo.size(); i++)
			okno_program.draw(tab_krzeslo[i].pobierz_obiekt());
		for (auto i = 0; i < tab_lampa.size(); i++)
			okno_program.draw(tab_lampa[i].pobierz_obiekt());
		for (auto i = 0; i < tab_lozko.size(); i++)
			okno_program.draw(tab_lozko[i].pobierz_obiekt());
		okno_program.waitEvent(event);//poczekaj na reakcj�
		//wy�wietlanie okien
		okno_program.display();
		okno_pomoc.display();
	}
	return 0;
}