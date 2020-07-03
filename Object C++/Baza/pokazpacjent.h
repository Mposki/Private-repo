#ifndef POKAZPACJENT_H
#define POKAZPACJENT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <string>
#include <memory>

#include "obsluga.h"
#include "pacjent.h"
#include "pacjentstruct.h"

#include "edycja.h"
#include "pokazpacjent.h"

namespace Ui {
class pokazPacjent;
}

class pokazPacjent : public QMainWindow
{
    Q_OBJECT

public:
    explicit pokazPacjent(QWidget *parent = nullptr);
    ~pokazPacjent();

private slots:
    void signalReciever(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o);

    void on_ok_clicked(){
        this->close();
    }

private:
    Ui::pokazPacjent *ui;
    std::shared_ptr<Obsluga> obsluga;
    std::shared_ptr<Pacjent> pacjent;

};

#endif // POKAZPACJENT_H
