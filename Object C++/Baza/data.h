#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include <ctime>
#include <string>
#include <sstream>

#include <QSqlError>
#include <QDebug>


class Pacjent;/*!< deklaracja klasy Pacjent w celu umożliwienia dostępu do zmiennych prywatnych klasy Data*/
/*!
 * \brief The Data class przechowuje datę
 */
class Data
{
private:
    std::string data;
    friend Pacjent; /*!< delaracja przyjaźni klasy Pacjent */
public:
    /*!
     * \brief zwrocData zwraca datę
     * \return data z obiektu
     */
    std::string zwrocData(){
        return this->data;
    }
    /*!
     * \brief Data konstruktor domyślny
     */
    Data() { //data rejestracji
        time_t ttime = time(0); /*!< zmienna pobierająca aktualny czas */
        tm *local_time = localtime(&ttime); /*!< wypełnienie struktury lockal_time wartościami czasu */
        int dzien = (local_time->tm_mday);/*!< przypisanie dnia z lockal_time */
        int miesiac = (1 + local_time->tm_mon);/*!< przypisanie miesiąca dnia z lockal_time */
        int rok = (1900 + local_time->tm_year);/*!< przypisanie roku dnia z lockal_time */
        delete local_time;/*!< usunięcie wskaźnika przechującej czas */
        /*std::stringstream ss;
        ss << std::to_string(dzien) << "-" << std::to_string(miesiac) << "-" << std::to_string(rok);
        ss >> this->data;*/
        //chrono
        /* naprawić zapis daty, bo wywala error debuggera odnośnie realokacji */
        std::string tmp = std::to_string(dzien) + "-" + std::to_string(miesiac) + "-" + std::to_string(rok);/*!< zmienna przechowująca datę w postaci std::string */
        edytujData(tmp);/*!< zapisanie daty w obiekcie */
    }
    /*!
     * \brief Data konstruktor na podstawie wskaźnika na obiekt Data
     * \param d wskaźnik na obiekt Data
     */
    Data(std::shared_ptr<Data> d) {
        this->data = d->data;
    }
    /*!
     * \brief edytujData edycja daty w obiekcie Data
     * \param data nowa data
     */
    void edytujData(std::string data){
        this->data = data;
    }
    /*!
     * \brief pobierzDataUr pobiranie daty urodznia pacjenta z bazy
     * \param id identyfikator pacjenta
     * \param db obiekt przechowujący dane dostępu do bazy
     * \return jeśli data istnieje true, inaczej false
     */
    bool pobierzDataUr(int id, std::shared_ptr<Obsluga> &obs){
        QSqlQuery zapytaj(obs->db);
        QVariant idP = QString::number(id);
        zapytaj.prepare("SELECT data_ur FROM pacjent WHERE idPacjent= :id");
        zapytaj.bindValue(":id", idP);
        zapytaj.exec();
        zapytaj.next();
        if(zapytaj.value(0).toString() != ""){
            QString var = zapytaj.value(0).toString();
            this->data = var.toStdString();
            return true;
        }
        else{
            qDebug() << zapytaj.lastError();
            this->data = "";
            return false;
        }
    }
};

#endif // DATA_H
