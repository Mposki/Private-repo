#ifndef OBJAWYWIN_H
#define OBJAWYWIN_H

#include <QMainWindow>

#include "obsluga.h"
#include "pacjent.h"

namespace Ui {
class objawyWin;
}

class objawyWin : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief objawyWin konstruktor domyśly okna edycji objawów
     * \param parent wskaźnik na obiekt "rodzic"
     */
    explicit objawyWin(QWidget *parent = nullptr);
    ~objawyWin();

private slots:
    /*!
     * \brief on_anuluj_clicked obsluga anulowania zmiany choroby i objawów
     */
    void on_anuluj_clicked();
    /*!
     * \brief on_zapisz_clicked obsluga zapisu/edycji choroby i objawów
     */
    void on_zapisz_clicked();
    /*!
     * \brief signalR odbieranie przekazywanych wskaźników z okna Edycja
     * \param p przekazywany wskaźnik na obiekt Pacjent
     * \param o przekazywany wskaźnik na obiekt Obsluga
     */
    void signalR(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o);

private:
    /*!
     * \brief ui wskaźnik na obiekt edycji choroby z objawami
     */
    Ui::objawyWin *ui;

protected:
    std::shared_ptr<Obsluga> obs;/*!< wskaźnik na obiekt Obsluga */
    std::shared_ptr<Pacjent> pac;/*!< wskaźnik na obiekt Pacjent */
};

#endif // OBJAWYWIN_H
