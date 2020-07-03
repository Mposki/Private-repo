#ifndef OBJAWY_H
#define OBJAWY_H
#include <string>
#include "choroba.h"
#include <memory>
#include <array>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class Objawy
{
    std::string objawy;
public:
    std::shared_ptr<Choroba> chorobaPtr;
    bool czySa;
    Objawy(){
        this->objawy = "";
        this->chorobaPtr = std::make_shared<Choroba>();
    }
    std::string zwrocObjawy(){
        return this->objawy;
    }
    void edytujObjawy(std::string obj){
        this->objawy = obj;
    }
    bool pobierzObjawy(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant idP = QString::number(id);
        zapytaj.prepare("SELECT objawy FROM choroba WHERE idPacjent= :id");
        zapytaj.bindValue(":id", idP);
        zapytaj.exec();
        zapytaj.next();
        if(zapytaj.value(0).toString() != ""){
            QString var = zapytaj.value(0).toString();
            this->objawy = var.toStdString();
            if(this->objawy != ""){ this->czySa = true; }
            else { this->czySa = false; }
            this->chorobaPtr->pobierzChoroba(id, obs);
            return true;
        }
        else{
            return false;
        }
    }
//zamienić QSqlDatabase db na const &
    void edytujObjawyBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant objawy = QString::fromStdString(this->zwrocObjawy());
        QVariant idP = QString::number(id);
        zapytaj.prepare("UPDATE choroba SET objawy = :objawy WHERE idPacjent = :idP");
        zapytaj.bindValue(":objawy", objawy);
        zapytaj.bindValue(":idP", idP);
        zapytaj.exec();
        this->chorobaPtr->edytujChorobaBaza(id, obs);
    }

    void zapiszObjawyBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant objawy = QString::fromStdString(this->zwrocObjawy());
        QVariant idP = QString::number(id);
        zapytaj.prepare("INSERT INTO choroba (idPacjent, objawy) VALUES (:idP, :objawy)");
        zapytaj.bindValue(":objawy", objawy);
        zapytaj.bindValue(":idP", idP);
        zapytaj.exec();
        this->chorobaPtr->edytujChorobaBaza(id, obs);
    }

    void usunObjawyBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant idP = QString::number(id);
        zapytaj.prepare("DELETE FROM choroba WHERE idPacjent= :idP");
        zapytaj.bindValue(":idP", idP);
        zapytaj.exec();
    }


};

#endif // OBJAWY_H
