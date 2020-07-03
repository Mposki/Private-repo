#ifndef CHOROBA_H
#define CHOROBA_H
#include <string>
#include <array>
#include <memory>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
/*!
 * \brief The Choroba class przechowuje chorobę
 */
class Choroba
{
    std::string nazwa;

public:
    /*!
     * \brief Choroba konstruktor domyślny
     */
    Choroba(){
        this->nazwa = "";
    }
    /*!
     * \brief zwrocChoroba zwraca nazwę choroby
     * \return nazwa choroby z obiektu
     */
    std::string zwrocChoroba(){
        return this->nazwa;
    }
    /*!
     * \brief edytujChoroba edytuje nazwę choroby
     * \param nazwa nowa nazwa choroby
     */
    void edytujChoroba(std::string nazwa){
        this->nazwa = nazwa;
    }
    /*!
     * \brief pobierzChoroba pobiera nazwę choroby pacjenta
     * \param id identyfikator pacjenta
     * \param db obiekt przechowujący dane dostępu do bazy danych
     * \return jeśli choroba istnieje zwraca true, inaczej false
     */
    bool pobierzChoroba(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);/*!< tworzy zmienną zapytania SQL */
        QVariant idP = QString::number(id);/*!< przygotowuje zmienną do zapytania SQL */
        zapytaj.prepare("SELECT nazwa FROM choroba WHERE idPacjent= :id");/*!< przygotowuje zapytanie SQL */
        zapytaj.bindValue(":id", idP);/*!< podmiana w zapytaniu SQL */
        zapytaj.exec();/*!< wykonanie zapytania */
        zapytaj.next();/*!< niezbędne do uzyskania poprawnego wyniku zapytania */
        if(zapytaj.value(0).toString() != "")/*!< jeśli wynik zapytania nie jest pusty */{
            QString var = zapytaj.value(0).toString();/*!< pobieranie wyniku zapytania */
            this->nazwa = var.toStdString();/*!< aktualizuje nazwę choroby w obiekcie Choroba */
            return true;
        }
        else{
            return false;
        }
    }
    /*!
     * \brief edytujChorobaBaza aktualizuje nazwę choroby pacjenta w bazie
     * \param id identyfikator pacjenta
     * \param db obiekt przechowujący dane dostępu do bazy danych
     */
    void edytujChorobaBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);/*!< tworzy zmienną zapytania SQL */
        QVariant choroba = QString::fromStdString(this->zwrocChoroba());/*!< przygotowuje zmienną do zapytania SQL */
        QVariant idP = QString::number(id);/*!< przygotowuje zmienną do zapytania SQL */
        zapytaj.prepare("UPDATE choroba SET nazwa = :choroba WHERE idPacjent = :idP");/*!< przygotowuje zapytanie SQL */
        zapytaj.bindValue(":choroba", choroba);/*!< podmiana w zapytaniu SQL */
        zapytaj.bindValue(":idP", idP);/*!< podmiana w zapytaniu SQL */
        zapytaj.exec();/*!< wykonanie zapytania */
    }
};

#endif // CHOROBA_H
