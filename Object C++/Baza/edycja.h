#ifndef EDYCJA_H
#define EDYCJA_H

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

#include "pokazpacjent.h"
#include "pokazbaze.h"
#include "objawywin.h"

namespace Ui {
class Edycja;
}

class Edycja : public QMainWindow, public Pismo
{
    Q_OBJECT

public:
    explicit Edycja(QWidget *parent = nullptr);
    ~Edycja();

private slots:
    void on_anuluj_clicked();

    void on_zmienChoroba_clicked();

    void on_zmienLeki_clicked();

    void on_zapisz_clicked();

    void signalRecieve(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o);

    void on_zmienBadania_clicked();

signals:
    void signalS(std::shared_ptr<Pacjent> &pacjent, std::shared_ptr<Obsluga>& obsluga);
    void signalR(std::shared_ptr<Pacjent>& pacjent, std::shared_ptr<Obsluga>& obsluga, int i);

private:
    Ui::Edycja *ui;
    pokazBaze *baza;
    objawyWin *objW;

protected:
    std::shared_ptr<Obsluga> obsluga;
    std::shared_ptr<Pacjent> pacjent;

};

#endif // EDYCJA_H
