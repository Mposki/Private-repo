#ifndef LEKARZ_H
#define LEKARZ_H
#include <string>
#include <obsluga.h>

class Lekarz
{
private:
    std::string login, haslo;
    int id;
public:
    Lekarz(){
        this->login = "";
        this->haslo = "";
        this->id = 0;
    }
    void dodajId(std::shared_ptr<Obsluga> &obs){
        obs->db.open();
        QSqlQuery zapytaj(obs->db);
        QVariant log = QString::fromStdString(login);
        QVariant has = QString::fromStdString(haslo);
        zapytaj.prepare("SELECT idLekarz FROM lekarz WHERE login= :login AND haslo= :haslo");
        zapytaj.bindValue(":login", log);
        zapytaj.bindValue(":haslo", has);
        zapytaj.exec();
        zapytaj.next();
        if(zapytaj.value(0).toString() != ""){
            this->id = zapytaj.value(0).toInt();
        }
        else { throw "Brak lekarza w bazie!"; }
    }
    void dodajLogin(std::string login){
        this->login = login;
    }
    void dodajHaslo(std::string haslo){
        this->haslo = haslo;
    }
    int zwrocId(){
        return this->id;
    }
};

#endif // LEKARZ_H
