#ifndef ADRES_H
#define ADRES_H
#include <string>
#include <memory>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>

//#include "obsluga.h"
/*!
 * \brief The AdresStruct struct struktura tymczasowo przechowująca adres, służy do edycji/ tworzenia adresu głównego
 */
struct AdresStruct
{
    std::string kraj, wojewodztwo, miasto, ulica;
    int dom, mieszkanie;
};
/*!
 * \brief The Adres class klasa przechująca adres
 */
class Adres
{
private:
    std::string kraj, wojewodztwo, miasto, ulica;
    int dom, mieszkanie;
public:
    /*!
     * \brief Adres konstruktor inicjalizujący adres inicjalizujący dane adresu na podstawie podanego wskąxnika na AdresStruct
     * \param adres obiekt AdresStruct przechowujący tymczasowo adres
     */
    Adres(std::shared_ptr<AdresStruct>adres){
        this->kraj = adres->kraj;
        this->wojewodztwo = adres->wojewodztwo;
        this->miasto = adres->kraj;
        this->ulica = adres->ulica;
        this->dom = adres->dom;
        this->mieszkanie = adres->mieszkanie;
    }
    /*!
     * \brief Adres konstruktor domyślny
     */
    Adres(){
        this->kraj = "";
        this->wojewodztwo = "";
        this->miasto = "";
        this->ulica = "";
        this->dom = 0;
        this->mieszkanie = 0;
    }
    /*!
     * \brief edytujAdres edycja adresu na podstawie AdresStruct
     * \param adres obiekt AdresStruct przechowujący tymczasowo adres
     */
    void edytujAdres(std::shared_ptr<AdresStruct>adres){
        this->kraj = adres->kraj;
        this->wojewodztwo = adres->wojewodztwo;
        this->miasto = adres->miasto;
        this->ulica = adres->ulica;
        this->dom = adres->dom;
        this->mieszkanie = adres->mieszkanie;
    }
    /*!
     * \brief pobierzAdres pobiera adres pacjenta z bazy danych
     * \param id identyfikator pacjenta
     * \param db zmienna przechowująca dane logowania do bazy danych
     * \return jeśli adres pacjenta jest to true, inaczej false
     */
    bool pobierzAdres(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);/*!< stwórz zmienną zapytania SQL */
        QVariant idP = QString::number(id);/*!< stwórz zmienną identyfikującą pacjenta w zapytaniu SQL */
        zapytaj.prepare("SELECT kraj, miasto, wojewodztwo, ulica, dom, mieszkanie FROM adres WHERE idPacjent= :id");/*!< przygotuj zapytanie SQL */
        zapytaj.bindValue(":id", idP);/*!< podmień wartość :id na identyfikator pacjenta */
        zapytaj.exec();/*!< wykonaj zapytanie SQL */
        zapytaj.next();/*!< konieczne, aby uzyskać wynik zapytania */
        if(zapytaj.value(0).toString() != "")/*!< jeśli wynik ma wartość od pustego wyrażenia */ {
            QString var = zapytaj.value(0).toString();/*!< tymczasowy kontener na wynik wyrażenia dla danych std::string */
            this->kraj = var.toStdString();/*!< wpisz pobrany kraj */
            var = zapytaj.value(1).toString();
            this->miasto = var.toStdString();/*!< wpisz pobrane miasto */
            var = zapytaj.value(2).toString();
            this->wojewodztwo = var.toStdString();/*!< wpisz pobrane województwo */
            var = zapytaj.value(3).toString();
            this->ulica = var.toStdString();/*!< wpisz pobraną ulicę */
            this->dom = zapytaj.value(4).toInt();/*!< wpisz pobrany numer domu */
            this->mieszkanie = zapytaj.value(5).toInt();/*!< wpisz pobrany numer mieszkania */
            return true;
        }
        else{
            return false;
        }
    }
    /*!
     * \brief edytujAdresBaza zapisanie nowych danych adresu pacjenta w bazie
     * \param id identyfikator pacjenta
     * \param db zmienna przechowująca dane logowania do bazy danych
     */
    void edytujAdresBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);/*!< stwórz zmienną zapytania SQL */
        QVariant kraj = QString::fromStdString(this->kraj);/*!< stwórz zmienną do zapytania SQL */
        QVariant wojewodztwo = QString::fromStdString(this->wojewodztwo);/*!< stwórz zmienną do zapytania SQL */
        QVariant miasto = QString::fromStdString(this->miasto);/*!< stwórz zmienną do zapytania SQL */
        QVariant ulica = QString::fromStdString(this->ulica);/*!< stwórz zmienną do zapytania SQL */
        QVariant dom = QString::number(this->dom);/*!< stwórz zmienną do zapytania SQL */
        QVariant mieszkanie = QString::number(this->mieszkanie);/*!< stwórz zmienną do zapytania SQL */
        QVariant idP = QString::number(id);/*!< stwórz zmienną w zapytaniu SQL */
        zapytaj.prepare("UPDATE adres SET kraj = :kraj, miasto = :miasto, wojewodztwo = :wojewodztwo, ulica = :ulica, dom = :dom, mieszkanie = :mieszkanie WHERE idPacjent = :idP");/*!< przygotuj zapytanie SQL */
        zapytaj.bindValue(":kraj", kraj);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":miasto", miasto);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":wojewodztwo", wojewodztwo);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":ulica", ulica);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":dom", dom);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":mieszkanie", mieszkanie);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":idP", idP);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.exec();/*!< wykonaj zapytanie SQL */
    }

    void dodajAdresBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);/*!< stwórz zmienną zapytania SQL */
        QVariant kraj = QString::fromStdString(this->kraj);/*!< stwórz zmienną do zapytania SQL */
        QVariant wojewodztwo = QString::fromStdString(this->wojewodztwo);/*!< stwórz zmienną do zapytania SQL */
        QVariant miasto = QString::fromStdString(this->miasto);/*!< stwórz zmienną do zapytania SQL */
        QVariant ulica = QString::fromStdString(this->ulica);/*!< stwórz zmienną do zapytania SQL */
        QVariant dom = QString::number(this->dom);/*!< stwórz zmienną do zapytania SQL */
        QVariant mieszkanie = QString::number(this->mieszkanie);/*!< stwórz zmienną do zapytania SQL */
        QVariant idP = QString::number(id);/*!< stwórz zmienną do zapytania SQL */
        zapytaj.prepare("INSERT INTO adres VALUES (:idP, :kraj, :miasto, :wojewodztwo, :ulica, :dom, :mieszkanie)");/*!< przygotuj zapytanie SQL */
        zapytaj.bindValue(":kraj", kraj);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":miasto", miasto);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":wojewodztwo", wojewodztwo);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":ulica", ulica);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":dom", dom);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":mieszkanie", mieszkanie);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.bindValue(":idP", idP);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.exec();/*!< wykonaj zapytanie SQL */
    }
    /*!
     * \brief usunAdresBaza usuń adres pacjenta
     * \param id identyfikator pacjenta
     * \param db zmienna przechowująca dane logowania do bazy danych
     */
    void usunAdresBaza(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);/*!< stwórz zmienną zapytania SQL */
        QVariant idP = QString::number(id);/*!< stwórz zmienną do zapytania SQL */
        zapytaj.prepare("DELETE FROM adres WHERE idPacjent= :idP");/*!< przygotuj zapytanie SQL */
        zapytaj.bindValue(":idP", idP);/*!< podmień wartość w zapytaniu SQL */
        zapytaj.exec();
    }
    /*!
     * \brief zwrocKraj zwraca kraj
     * \return kraj z obiektu
     */
    std::string zwrocKraj(){
        return this->kraj;
    }
    /*!
     * \brief zwrocWojewodztwo zwraca województwo
     * \return województwo z obiektu
     */
    std::string zwrocWojewodztwo(){
        return this->wojewodztwo;
    }
    /*!
     * \brief zwrocMiasto zwraca miasto
     * \return miasto z obiektu
     */
    std::string zwrocMiasto(){
        return this->miasto;
    }
    /*!
     * \brief zwrocUlica zwara ulicę
     * \return ulica z obiektu
     */
    std::string zwrocUlica(){
        return this->ulica;
    }
    /*!
     * \brief zwrocDom zwraca numer domu
     * \return numer domu z obiektu
     */
    int zwrocDom(){
        return this->dom;
    }
    /*!
     * \brief zwrocMieszkanie zwraca numer mieszkania
     * \return numer mieszkania z obiektu
     */
    int zwrocMieszkanie(){
        return this->mieszkanie;
    }

};

#endif // ADRES_H
