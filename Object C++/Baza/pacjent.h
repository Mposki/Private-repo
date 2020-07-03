#ifndef PACJENT_H
#define PACJENT_H

#include <memory>
#include <string>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "data.h"
#include "adres.h"
#include "badanie.h"
#include "pacjentstruct.h"
#include "objawy.h"
#include "obsluga.h"

class Edycja;
class pokazBaze;
class pokazPacjent;

class Pacjent //: public Data, public Adres, public Objawy
{
private:
    int id, idLek;
    std::string imie, nazwisko, pesel;
    friend Edycja;
    friend pokazBaze;
    friend pokazPacjent;
public:
    std::shared_ptr<Data> data_ur, data_rej;
    std::shared_ptr<Adres> adres_zamieszkania;
    std::shared_ptr<Objawy> objawy;
    bool czyJest;

    Pacjent(){}
    Pacjent(std::shared_ptr<PacjentStruct> p){
        this->imie = p->imie;
        this->nazwisko = p->nazwisko;
        this->pesel = p->pesel;
        this->id = 0;
        this->idLek = p->idLekarza;
        this->data_rej.reset(new Data());
        this->data_ur.reset(new Data(data_rej));
        this->adres_zamieszkania.reset(new Adres());
        this->objawy.reset(new Objawy());
    }
    void edytuj_Pacjent(std::shared_ptr<PacjentStruct> p, std::shared_ptr<Obsluga> &obs){
        this->imie = p->imie;
        this->nazwisko = p->nazwisko;
        this->pesel = p->pesel;
        pobierzId(obs);
        this->data_ur->pobierzDataUr(this->id, obs);
        this->adres_zamieszkania->pobierzAdres(this->id, obs);
        this->objawy->pobierzObjawy(this->id, obs);
    }

    void edytujPacjentKlasa(std::shared_ptr<PacjentStruct> p, std::string data, std::shared_ptr<AdresStruct> a){//edycja przy dodawaniu pacjenta/zmiany danych w bazie
        this->imie = p->imie;
        this->nazwisko = p->nazwisko;
        this->pesel = p->pesel;
        this->data_ur->edytujData(data);
        this->adres_zamieszkania->edytujAdres(a);
    }

    void dodajPacjentDoBazy(std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant imie = QString::fromStdString(this->imie);
        QVariant nazwisko = QString::fromStdString(this->nazwisko);
        QVariant pesel = QString::fromStdString(this->pesel);
        QVariant data_ur = QString::fromStdString(this->data_ur->zwrocData());
        QVariant data_rej = QString::fromStdString(this->data_rej->zwrocData());
        QVariant idLekarz = QString::number(this->idLek);
        QVariant idPacjent = QString::number(id);
        zapytaj.prepare("INSERT INTO pacjent VALUES (:idP, :imie, :nazwisko, :pesel, :data_ur, :data_rej, :idLekarz)");
        zapytaj.bindValue(":imie", imie);
        zapytaj.bindValue(":nazwisko", nazwisko);
        zapytaj.bindValue(":pesel", pesel);
        zapytaj.bindValue(":data_ur", data_ur);
        zapytaj.bindValue(":data_rej", data_rej);
        zapytaj.bindValue(":idLekarz", idLekarz);
        zapytaj.bindValue(":idP", idPacjent);
        zapytaj.exec();
        this->adres_zamieszkania->dodajAdresBaza(this->id, obs);
    }

    void edytujPacjentBaza(std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant imie = QString::fromStdString(this->imie);
        QVariant nazwisko = QString::fromStdString(this->nazwisko);
        QVariant pesel = QString::fromStdString(this->pesel);
        QVariant data_ur = QString::fromStdString(this->data_ur->zwrocData());
        QVariant data_rej = QString::fromStdString(this->data_rej->zwrocData());
        QVariant idLekarz = QString::number(this->idLek);
        QVariant idPacjent = QString::number(id);
        zapytaj.prepare("UPDATE pacjent SET imie = :imie, nazwisko = :nazwisko, pesel = :pesel, data_ur = :data_ur, data_rej = :data_rej, idLekarz = :idLekarz WHERE idPacjent = :idP");
        zapytaj.bindValue(":imie", imie);
        zapytaj.bindValue(":nazwisko", nazwisko);
        zapytaj.bindValue(":pesel", pesel);
        zapytaj.bindValue(":data_ur", data_ur);
        zapytaj.bindValue(":data_rej", data_rej);
        zapytaj.bindValue(":idLekarz", idLekarz);
        zapytaj.bindValue(":idP", idPacjent);
        zapytaj.exec();
        this->adres_zamieszkania->edytujAdresBaza(this->id, obs);
    }

    void usunPac(std::shared_ptr<Obsluga> &obs)
    {
        QSqlQuery usun(obs->db);
        QVariant idP = QString::number(this->id);
        usun.prepare("DELETE FROM pacjent WHERE idPacjent = :idP");
        usun.bindValue(":idP", idP);
        usun.exec();
        this->objawy->usunObjawyBaza(this->id, obs);
        this->adres_zamieszkania->usunAdresBaza(this->id, obs);

    }

    void pobierzId(std::shared_ptr<Obsluga> &obs)
    {
        QSqlQuery zapytaj(obs->db);
        QVariant pesel = QString::fromStdString(this->pesel);
        zapytaj.prepare("SELECT idPacjent FROM pacjent WHERE pesel= :pesel");
        zapytaj.bindValue(":pesel", pesel);
        zapytaj.exec();
        zapytaj.next();
        if(zapytaj.value(0).toString() != ""){
            this->id = zapytaj.value(0).toInt();
        }
        else{
            zapytaj.prepare("SELECT MAX(idPacjent) FROM pacjent");
            zapytaj.exec();
            zapytaj.next();
            this->id = (zapytaj.value(0).toInt() + 1);
        }
    }

    int zwrocId(){
        return this->id;
    }

};

#endif // PACJENT_H
