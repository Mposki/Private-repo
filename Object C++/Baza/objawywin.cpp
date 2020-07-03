#include "objawywin.h"
#include "ui_objawywin.h"

objawyWin::objawyWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::objawyWin)
{
    ui->setupUi(this);
}

objawyWin::~objawyWin()
{
    delete ui;
}

void objawyWin::on_anuluj_clicked()
{
    this->close();/*!< zamknięcie okna */
}

void objawyWin::on_zapisz_clicked()//nie zapisuje danych w bazie, problem!
{
    this->pac->objawy->chorobaPtr->edytujChoroba(ui->choroba->text().toStdString());/*!< aktualizacja Choroba */
    this->pac->objawy->edytujObjawy(ui->objawy->toPlainText().toStdString());/*!< aktualizacja Objawy */
    if(this->pac->objawy->czySa == true){ this->pac->objawy->edytujObjawyBaza(this->pac->zwrocId(), this->obs); }/*!< jeśli obiekt Objawy istnieje dla pacjenta, to aktualizuj objawy */
    else { this->pac->objawy->zapiszObjawyBaza(this->pac->zwrocId(), this->obs); }/*!< jeśli obiekt nie istnieje, to przypisz objawy pacjentowi i zapisz w bazie */
    this->close();/*!< zamknięcie okna */
}

void objawyWin::signalR(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o)
{
    this->pac = p; /*! przypisz przekazywany wskażnik na obiekt Pacjent wskaźnikowi pac */
    this->obs = o; /*!< przypisz wskazywany wskaźnik na obiekt Obsluga wskaźnikowi obs */
    ui->choroba->setText(QString::fromStdString(this->pac->objawy->chorobaPtr->zwrocChoroba())); /*! przypisz do pola choroba nazwę choroby */
    ui->objawy->setText(QString::fromStdString(this->pac->objawy->zwrocObjawy())); /*!< przypisz do pola objawy tekst objawów */
}
