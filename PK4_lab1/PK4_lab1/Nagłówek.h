#pragma once
#include <iostream>
using namespace std;

class Class
{
public:
	Class();
	~Class();
	Class(double);
	void AttendClass();
	virtual void ShowDoneHours();
	double GetTime();
protected:
	double done_hours;
	double time_of_class;
};

class Laboratory : public Class
{
public:
	Laboratory();
	~Laboratory();
	Laboratory(string, int);
	virtual void AttendLab();
	void ShowDoneHours();
	string GetLeader();
protected:
	string name;
	double work_hours;
};

class PK4 : public Laboratory
{
public:
	PK4();
	~PK4();
	PK4(string, double);
	double nr_of_topic;
	void ShowDoneHours();
	void AttendLab();
};

//-------Funkcje------

void ShowNames(Class* tab[], int size);

void Show(Class* tab[], int size);

void Action(Class* tab[], int size);

void Average(Class* tab[], int size, string name);