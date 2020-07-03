#ifndef OBSLUZBAZE_H
#define OBSLUZBAZE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <string>
#include <memory>
#include <thread>
#include <future>
#include <utility>

#include "obsluga.h"
#include "pacjent.h"
#include "pacjentstruct.h"
#include "sprawdzPisanie.h"

#include "edycja.h"
#include "pokazpacjent.h"

namespace Ui {
class obsluzBaze;
}

class obsluzBaze : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief obsluzBaze konstruktor domyślny obiektu obsluzBaze
     * \param parent wskaźnik na "rodzica" obiektu
     */
    explicit obsluzBaze(QWidget *parent = nullptr);
    /*!
      * \brief ~obsluzBaze destruktor domyślny obiektu obsluzBaze
      */
    ~obsluzBaze();

private slots:
    /*!
     * \brief on_usun_clicked obsługa zdarzenia kliknięcia przycisku usunięcia pacjenta z bazy
     */
    void on_usun_clicked();
    /*!
     * \brief on_dodaj_clicked obsluga zdarzenia kliknięcia przycisku dodania pacjenta do bazy
     */
    void on_dodaj_clicked();
    /*!
     * \brief on_szukaj_clicked obsluga zdarzenia kliknięcia przycisku szukania pacjenta w bazie
     */
    void on_szukaj_clicked();
    /*!
     * \brief recieveId odebranie przekazywanego identyfikatora lekarza
     * \param id przekazywany identyfikator lekarza
     */
    void recieveId(int id)
    {
        this->idLekarz = id; /**< zapis identyfikatora lekarza w zmiennej idLekarz należącej do obiektu klasy obsluzBaze */
    }

signals:
    /*!
     * \brief signalSend wysyłanie sygnału ze wskaźnikami na obiekty Pacjent i Obsluga
     * \param pacjent wskaźnik na obiekt Pacjent
     * \param obsluga wskaźnik na obiekt Obsluga
     */
    void signalSend(std::shared_ptr<Pacjent> &pacjent, std::shared_ptr<Obsluga>& obsluga);

private:
    /*!
     * \brief ui wskaźnik na obiekt obsluzBaze będący oknem wyszukiwania
     * \brief edycja wskaźnik na obiekt Edycja będący oknem edycji danych pacjenta
     * \brief pokaz wskaźnik na obiekt pokazPacjent będący oknem wyświetlania danych pacjenta
     */
    Ui::obsluzBaze *ui;
    Edycja *edycja;
    pokazPacjent *pokaz;

protected:
    /*!
     * \brief obsluga wskaźnik na obiekt Obsluga
     * \brief pacjent wskaźnik na obiekt Pacjent
     * \brief idLekarz zmienna przechowująca (tymczasowo) identyfikator lekarza prowadzącego
     */
    std::shared_ptr<Obsluga> obsluga;
    std::shared_ptr<Pacjent> pacjent;
    int idLekarz;

};

#endif // OBSLUZBAZE_H
