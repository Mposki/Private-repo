#pragma once
#include <iostream>
#include <QLineEdit>
#include <QString>
using namespace std;

class Objawy
{
public:
    Objawy();
    ~Objawy();
    QString objawy;
};

class Lek
{
public:
    Lek();
    ~Lek();
    QString nazwa, dawkowanie; //ile razy dziennie

private:

};

class Badanie
{
public:
    Badanie();
    ~Badanie();
    QString nazwa;
    /*obraz z badaniem*/
private:

};

class Choroba
{
public:
    Choroba();
    ~Choroba();
    QString nazwa;
};

class Adres
{
public:
    Adres();
    ~Adres();
    QString miasto, adres;
};

class Pacjent : public Choroba, public Objawy, public Adres
{
public:
    Pacjent();
    ~Pacjent();
    QString imie, nazwisko, pesel, data_uro;
};
