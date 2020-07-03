#include "logowanie.h"
#include "ui_logowanie.h"
#include "mainwindow.h"

Logowanie::Logowanie(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logowanie)
{
    ui->setupUi(this);
}

Logowanie::~Logowanie()
{
    delete ui;
}


void Logowanie::on_pushButton_clicked()
{
    QString loginN, hasloN;
    loginN = ui->login->text();
    hasloN = ui->haslo->text();
    QWidget *mainWindow = new QWidget;
    mainWindow->show();
    Logowanie::close();
}
