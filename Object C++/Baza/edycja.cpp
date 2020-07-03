#include "edycja.h"
#include "ui_edycja.h"

Edycja::Edycja(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Edycja)
{
    ui->setupUi(this);
    this->pacjent=std::make_shared<Pacjent>();
    this->obsluga=std::make_shared<Obsluga>();
    baza = new pokazBaze(this);
    objW = new objawyWin(this);
    connect(this,SIGNAL(signalR(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&, int)),baza,SLOT(signalR(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&, int)));
    connect(this,SIGNAL(signalS(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&)),objW,SLOT(signalR(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&)));
}

Edycja::~Edycja()
{
    delete ui;
}

void Edycja::on_anuluj_clicked()
{
    this->close();
}

void Edycja::on_zmienChoroba_clicked()
{
    emit signalS(this->pacjent, this->obsluga);
    objW->show();
}

void Edycja::on_zmienLeki_clicked()
{
    emit signalR(this->pacjent, this->obsluga, 1);
    baza->show();
}

void Edycja::on_zapisz_clicked()
{
    /* zapis i kontrola wpisanych ciągów, pobiera wartości do sprawdzenia */
    Pismo pisz;
    try{
        pisz.sprawdz<std::string, int>(ui->imie->text().toStdString(), 1);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->imie).name()), QMessageBox::Ok);
        ui->imie->clear();
    }
    try{
        pisz.sprawdz<std::string, int>(ui->nazwisko->text().toStdString(), 1);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->nazwisko).name()), QMessageBox::Ok);
        ui->nazwisko->clear();
    }
    try{
        pisz.sprawdz<std::string, int>(ui->pesel->text().toStdString(), 0);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->pesel).name()), QMessageBox::Ok);
        ui->pesel->clear();
    }
    try{
        pisz.sprawdz<std::string, int>(ui->data_ur->text().toStdString(), 2);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->data_ur).name()), QMessageBox::Ok);
        ui->data_ur->clear();
    }
    try{
        pisz.sprawdz<std::string, int>(ui->kraj->text().toStdString(), 1);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->kraj).name()), QMessageBox::Ok);
        ui->kraj->clear();
    }
    /*try{
        pisz.sprawdz<std::string, int>(ui->wojewodztwo->text().toStdString(), 1);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->wojewodztwo).name()), QMessageBox::Ok);
        ui->wojewodztwo->clear();
    }*/
    try{
        pisz.sprawdz<std::string, int>(ui->miasto->text().toStdString(), 1);
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(ui->miasto).name()), QMessageBox::Ok);
        ui->miasto->clear();
    }
    std::shared_ptr<PacjentStruct>p(new PacjentStruct());
    std::shared_ptr<AdresStruct>a(new AdresStruct());
    p->imie = ui->imie->text().toStdString();
    p->nazwisko = ui->nazwisko->text().toStdString();
    p->pesel = ui->pesel->text().toStdString();
    a->kraj = ui->kraj->text().toStdString();
    a->wojewodztwo = ui->wojewodztwo->text().toStdString();
    a->miasto = ui->miasto->text().toStdString();
    a->ulica = ui->ulica->text().toStdString();
    a->dom = ui->dom->text().toInt();
    a->mieszkanie = ui->mieszkanie->text().toInt();
    this->pacjent->edytujPacjentKlasa(p, ui->data_ur->text().toStdString(), a);
    if(!this->pacjent->czyJest){
        this->pacjent->dodajPacjentDoBazy(this->obsluga);
        QMessageBox::information(this, "Dodano pacjenta do bazy!", QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok);
    }
    else{
        this->pacjent->edytujPacjentBaza(this->obsluga);
        QMessageBox::information(this, "Edycja pacjenta udana!", QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok);
    }
    this->close();
}

void Edycja::signalRecieve(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o)
{
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

void Edycja::on_zmienBadania_clicked()
{
    emit signalR(this->pacjent, this->obsluga, 2);
    baza->show();
}
