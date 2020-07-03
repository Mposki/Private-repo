#ifndef OBSLUGA_H
#define OBSLUGA_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>
#include <QMessageBox>
#include <QTextStream>
#include <QPushButton>
#include <QDebug>

#include "pacjentstruct.h"

class Obsluga
{
public:
    QSqlDatabase db;
    Obsluga(){
        this->db = QSqlDatabase::addDatabase("QODBC"); // tworzę bazę danych z wykorzystaniem sterownika QODBC
        this->db.setDatabaseName("Driver={MySQL ODBC 8.0 Unicode Driver}; Database=pacjent"); // ustawiam nazwę schematu, pod który chcę się podpiąć
        this->db.setHostName("localhost"); // nazwa serwera
        this->db.setUserName("root"); // nazwa użytkownika
        this->db.setPassword("root"); // hasło
        this->db.setPort(3306); // port połączenia z bazą danych
        if(db.open()){ // próbuję otworzyć bazę danych i jak się nie otworzy to
            qDebug()<<"Poloczono";
        }
        else{
            qDebug()<<"Nie poloczono!";
            throw db.lastError().text(); // błąd ładowania

        }
    }
    ~Obsluga(){
        db.close();
    }
    QSqlDatabase zwrocDb(){
        return this->db;
    }

    bool sprawdzCzyIstniejePacjent(std::shared_ptr<PacjentStruct>p){
        QSqlQuery zapytaj(this->db);
        QVariant imie = QString::fromStdString(p->imie);
        QVariant nazwisko = QString::fromStdString(p->nazwisko);
        QVariant id = QString::number(p->idLekarza);
        zapytaj.prepare("SELECT pesel FROM pacjent WHERE imie= :imie AND nazwisko= :nazwisko AND idLekarz = :lekarz");
        zapytaj.bindValue(":imie", imie);
        zapytaj.bindValue(":nazwisko", nazwisko);
        zapytaj.bindValue(":lekarz", id);
        zapytaj.exec();
        zapytaj.next();
        QString pesel = zapytaj.value(0).toString();
        if(!pesel.isEmpty()){
            return true;
        }
        else { return false; }
    }

    bool sprawdzLekarza(std::string login, std::string haslo){
        QSqlQuery zapytaj(this->db);
        QVariant log = QString::fromStdString(login);
        QVariant has = QString::fromStdString(haslo);
        zapytaj.prepare("SELECT idLekarz FROM lekarz WHERE login= :login AND haslo= :haslo");
        zapytaj.bindValue(":login", log);
        zapytaj.bindValue(":haslo", has);
        zapytaj.exec();
        zapytaj.next();
        if(zapytaj.value(0).toString() != ""){
            return true;
        }
        else { throw "Brak lekarza w bazie!"; }
    }


};

#endif // OBSLUGA_H
