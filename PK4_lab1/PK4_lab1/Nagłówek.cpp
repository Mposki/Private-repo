#include <iostream>
#include "Nag³ówek.h"
using namespace std;

//-------Class-------
Class::Class()
{
}

Class::~Class()
{
}

Class::Class(double t) : time_of_class(t)
{
	this->done_hours = 0;
}

void Class::AttendClass()
{
	this->done_hours = this->done_hours + 2;
}

void Class::ShowDoneHours()
{
	cout << "Zrealizowanych godzin: " << this->done_hours << endl;
}

double Class::GetTime()
{
	return this->time_of_class;
}

//-------Laboratory-------
Laboratory::Laboratory()
{
}

Laboratory::~Laboratory()
{
}

Laboratory::Laboratory(string n, int hours) : Class(hours), name(n), work_hours(0)
{
}

void Laboratory::AttendLab()
{
	this->work_hours++;
	this->done_hours = this->done_hours + 1.5;
}

void Laboratory::ShowDoneHours()
{
	cout << "Zrealizowano " << this->done_hours << " godzin laboratorium." << endl;
}

string Laboratory::GetLeader()
{
	return this->name;
}

//-------PK4-------
PK4::PK4()
{
}

PK4::~PK4()
{
}

PK4::PK4(string n, double wh) : Laboratory(n, wh)
{
	this->nr_of_topic = 0;
}

void PK4::ShowDoneHours()
{
	cout << "Zrealizowano " << this->done_hours << " godzin z przedmiotu PK4." << endl;
}

void PK4::AttendLab()
{
	this->work_hours++;
	this->done_hours = this->done_hours + 1.5;
	this->nr_of_topic++;
}

//-------FUNKCJE-------

void ShowNames(Class* tab[], int size) {
	for (int i = 0; i < size; i++)
		cout << i << "=" << typeid(*tab[i]).name() << endl;
}

void Show(Class* tab[], int size) {
	for (int i = 0; i < size; i++)
		tab[i]->ShowDoneHours();
}

void Action(Class * tab[], int size) {
	Class* tmpC;
	Laboratory* tmpL;
	PK4* tmpP;
	for (int i = 0; i < size; i++) {
		if (tmpC = dynamic_cast<Class*>(tab[i])) {
			tmpC->AttendClass();
			cout << "Wykonano metodê AttendClass()." << endl;
		}
		if (tmpL = dynamic_cast<Laboratory*>(tab[i])) {
			tmpL->AttendLab();
			cout << "Wykonano metodê AttendLab()." << endl;
		}
		if (tmpP = dynamic_cast<PK4*>(tab[i])) {
			tmpP->AttendLab();
			cout << "Wykonano metodê AttendLab() dla klasy PK4." << endl;
		}
	}
}

void Average(Class * tab[], int size, string name) {
	double n = 0, s = 0, r;
	for (int i = 0; i < size; i++) {
		PK4* tmpP;
		if (typeid(*tab[i]).name() == typeid(PK4).name()) {
			tmpP = dynamic_cast<PK4*>(tab[i]);
			if (tmpP->GetLeader() == name) {
				n++;
				s = s + tab[i]->GetTime();
			}
		}
	}
	r = s / n;
	cout << r << endl;
}

