#include "pokazpacjent.h"
#include "ui_pokazpacjent.h"

pokazPacjent::pokazPacjent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pokazPacjent)
{
    this->pacjent=std::make_shared<Pacjent>();
    this->obsluga=std::make_shared<Obsluga>();
    ui->setupUi(this);
}

pokazPacjent::~pokazPacjent()
{
    delete ui;
}

void pokazPacjent::signalReciever(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o){
    this->pacjent = p;
    this->obsluga = o;
    ui->imie->setText(QString::fromStdString(pacjent->imie));
    ui->nazwisko->setText(QString::fromStdString(pacjent->nazwisko));
    ui->pesel->setText(QString::fromStdString(pacjent->pesel));
    ui->data_ur->setText(QString::fromStdString(pacjent->data_ur->zwrocData()));
    ui->kraj->setText(QString::fromStdString(pacjent->adres_zamieszkania->zwrocKraj()));
    ui->wojewodztwo->setText(QString::fromStdString(pacjent->adres_zamieszkania->zwrocWojewodztwo()));
    ui->miasto->setText(QString::fromStdString(pacjent->adres_zamieszkania->zwrocMiasto()));
    ui->ulica->setText(QString::fromStdString(pacjent->adres_zamieszkania->zwrocUlica()));
    ui->dom->setText(QString::number(pacjent->adres_zamieszkania->zwrocDom()));
    ui->mieszkanie->setText(QString::number(pacjent->adres_zamieszkania->zwrocMieszkanie()));

}
