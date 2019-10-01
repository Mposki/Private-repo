#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "klasy.h"
#include <QObject>
#include <QMainWindow>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_zamknij_clicked();
    
    void on_zamknij_bez_zapisu_clicked();

    void on_szukaj_clicked();

    void on_usun_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool sprawdz_czy_istnieje;
    vector<Lek> tab_leki;
    vector<Badanie> tab_badania;
};

#endif // MAINWINDOW_H
