#ifndef POKAZBAZE_H
#define POKAZBAZE_H

#include <QMainWindow>
#include <QSql>
#include <memory>
#include <QString>

#include "obsluga.h"
#include "pacjent.h"

namespace Ui {
class pokazBaze;
}

class QSqlTableModel;

class pokazBaze : public QMainWindow
{
    Q_OBJECT

public:
    explicit pokazBaze(QWidget *parent = nullptr);
    ~pokazBaze();
    int wyborOpcji;

private slots:
    void signalR(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o, int i);

    void on_dodaj_clicked();

    void on_usun_clicked();

    void on_aktualizuj_clicked();

private:
    Ui::pokazBaze *ui;
    QSqlTableModel *model;

protected:
    std::shared_ptr<Obsluga> obs;
    std::shared_ptr<Pacjent> pac;
};

#endif // POKAZBAZE_H
