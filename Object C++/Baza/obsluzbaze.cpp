#include "obsluzbaze.h"
#include "ui_obsluzbaze.h"

obsluzBaze::obsluzBaze(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::obsluzBaze)
{
    this->obsluga = std::make_shared<Obsluga>();/*!< alokacja pamięci na wskaźnik na obiekt klasy Pacjent */
    this->pacjent = std::make_shared<Pacjent>();/*!< alokacja pamięci na wskaźnik na obiekt klasy Obsluga */
    ui->setupUi(this);/*!< stworzenie okna wyszukiwania */
    this->edycja = new Edycja(this); /*!< alokacja pamięci okno Edycja */
    this->pokaz = new pokazPacjent(this);/*!< alokacja pamieci na okno pokazPacjent */

    connect(this,SIGNAL(signalSend(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&)),edycja,SLOT(signalRecieve(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&)));/*!< połączenie okna Edycji i oknem wyszukiwania w celu przekazania wskaźnika na obiekt Pacjent i Obsluga*/
    connect(this,SIGNAL(signalSend(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&)),pokaz,SLOT(signalReciever(std::shared_ptr<Pacjent>&, std::shared_ptr<Obsluga>&)));/*!< połączenie okna pokazPacjent i oknem wyszukiwania w celu przekazania wskaźnika na obiekt Pacjent i Obsluga*/

}
obsluzBaze::~obsluzBaze()
{
    delete ui;
}

void obsluzBaze::on_usun_clicked()
{
    std::shared_ptr<PacjentStruct>pacjent(new PacjentStruct());/*!< wskaźnik na obiekt PacjentStruct, który ma posłużyć do inicjalizacji nowego wskaźnika na obiekt Pacjent */
    pacjent->imie = ui->imie->text().toStdString();/*!< przechwycenie imienia podanego w oknie wyszukiwania i wpisanie go do pola imie obiektu wsazywanego przez pacjent */
    pacjent->nazwisko = ui->nazwisko->text().toStdString();/*!< przechwycenie nazwiska podanego w oknie wyszukiwania */
    pacjent->pesel = ui->pesel->text().toStdString();/*!< przechwycenie peselu podanego w oknie wyszukiwania */
    pacjent->idLekarza = this->idLekarz;/*!< przechwycenie identyfikatora lekarza wyszukanego w oknie logowania*/
    try{
        Pismo pisz;/*!< obiekt Pismo */
        pisz.sprawdz<std::string, int>(pacjent->imie, 1);/*!< sprawdzenie piswoni imienia */
        pisz.sprawdz<std::string, int>(pacjent->nazwisko, 1);/*!< sprawdzenie pisowni nazwiska */
        pisz.sprawdz<std::string, int>(pacjent->pesel, 0);/*!< sprawdzenie pisowni peselu */
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok);/*!< okno powiadamiające o błędzie pisowni */
        ui->imie->clear(); /*!< usunięcie wpisanej zawartości w oknie */
        ui->nazwisko->clear();/*! usunięcie wpisanej zawartości w oknie */
        ui->pesel->clear();/*! usunięcie wpisanej zawartości w oknie */
    }
    this->pacjent.reset(new Pacjent(pacjent)); /*!< aktualizacja obiektu Pacjent */
    this->pacjent->czyJest = this->obsluga->sprawdzCzyIstniejePacjent(pacjent); /*!< sprawdzenie czy istnieje pacjent w bazie danych */
    if(this->pacjent->czyJest){/*!< jeżeli istnieje */
        this->pacjent->pobierzId(this->obsluga);/*!< pobranie identyfikatora pacjenta*/
        this->pacjent->usunPac(this->obsluga);/*!< usunięcie pacjenta z bazy */
        QMessageBox::information(this, "Usunieto pacjenta!", QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok);/*!< okno powiadamiające o usunięciu pacjenta z bazy danych*/
        ui->imie->clear();/*! usunięcie wpisanej zawartości w oknie */
        ui->nazwisko->clear();/*! usunięcie wpisanej zawartości w oknie */
        ui->pesel->clear();/*! usunięcie wpisanej zawartości w oknie */
    }
    else {
        QMessageBox::information(this, "Error!", "Brak pacjenta w bazie", QMessageBox::Ok);/*!< powiadomienie, że pacjet nie istnieje w bazie */
    }
}

void obsluzBaze::on_dodaj_clicked()
{
    std::shared_ptr<PacjentStruct> pacjent(new PacjentStruct());/*!< wskaźnik na obiekt PacjentStruct, który ma posłużyć do inicjalizacji nowego wskaźnika na obiekt Pacjent */
    pacjent->imie = ui->imie->text().toStdString();/*!< przechwycenie imienia podanego w oknie wyszukiwania i wpisanie go do pola imie obiektu wsazywanego przez pacjent */
    pacjent->nazwisko = ui->nazwisko->text().toStdString();/*!< przechwycenie nazwiska podanego w oknie wyszukiwania */
    pacjent->pesel = ui->pesel->text().toStdString();/*!< przechwycenie peselu podanego w oknie wyszukiwania */
    pacjent->idLekarza = this->idLekarz;/*!< przechwycenie identyfikatora lekarza wyszukanego w oknie logowania*/
    try{
        Pismo pisz;
        pisz.sprawdz<std::string, int>(pacjent->imie, 1);/*!< sprawdzenie piswoni imienia */
        pisz.sprawdz<std::string, int>(pacjent->nazwisko, 1);/*!< sprawdzenie pisowni nazwiska */
        pisz.sprawdz<std::string, int>(pacjent->pesel, 0);/*!< sprawdzenie pisowni peselu */
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok);/*!< okno informujące o błędzie w pisowni */
        ui->imie->clear();/*!< usunięcie wpisanej zawartości w oknie */
        ui->nazwisko->clear();/*!< usunięcie wpisanej zawartości w oknie */
        ui->pesel->clear();/*!< usunięcie wpisanej zawartości w oknie */
    }
    this->pacjent.reset(new Pacjent(pacjent)); /*!< aktualizacja obiektu Pacjent*/
    this->pacjent->czyJest = this->obsluga->sprawdzCzyIstniejePacjent(pacjent); /*!< sprawdzenie czy pacjent istnieje */
    this->pacjent->edytuj_Pacjent(pacjent, obsluga); /*!< edycja danych pacjenta */
    if(!this->pacjent->czyJest){/*!< jeśli pacjent nie istnieje */
        QMessageBox::information(this, "Dodaję Pacjenta", QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok); /*!< okno informujące o dodawaniu pacjenta do bazy */
        emit signalSend(this->pacjent, this->obsluga);/*!< wysłanie wsaźników Pacjent i Obsluga do kolejnego okna */
        edycja->show();/*!< otwarcie okna Edycja */
    }
    else
    {
        QMessageBox msgBox;/*!< okno informujące o znalezieniu pacjenta w bazie */
        msgBox.setText("Informacja");/*!< tytuł okna */
        msgBox.setInformativeText("Znaleziono pacjenta.\n Przejść do edycji?"); /*!< tekst okna */
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);/*!< przyciski funkcyjne */
        int ret = msgBox.exec();/*!< przypisanie wartości zwracanej przez kliknięty przycisk */
        switch(ret){
        case QMessageBox::Cancel: /*!< jeśli kliknięto Cancel */
            ui->imie->clear();/*!< usunięcie wpisanej zawartości w oknie */
            ui->nazwisko->clear();/*!< usunięcie wpisanej zawartości w oknie */
            ui->pesel->clear();/*!< usunięcie wpisanej zawartości w oknie */
            break;
        case QMessageBox::Ok:/*!< jeśli kliknięto OK */
            emit signalSend(this->pacjent, this->obsluga);/*!< wyślij sygnał do okna Edycja */
            edycja->show();/*!< otwórz okno Edycja */
            break;
        }
    }
}

void obsluzBaze::on_szukaj_clicked()
{
    std::shared_ptr<PacjentStruct>pacjent(new PacjentStruct());
    pacjent->imie = ui->imie->text().toStdString();
    pacjent->nazwisko = ui->nazwisko->text().toStdString();
    pacjent->pesel = ui->pesel->text().toStdString();
    pacjent->idLekarza = this->idLekarz;
    try{
        Pismo pisz;
        pisz.sprawdz<std::string, int>(pacjent->imie, 1);/*!< sprawdzenie piswoni imienia */
        pisz.sprawdz<std::string, int>(pacjent->nazwisko, 1);/*!< sprawdzenie pisowni nazwiska */
        pisz.sprawdz<std::string, int>(pacjent->pesel, 0);/*!< sprawdzenie pisowni peselu */
    } catch (std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(typeid(pacjent).name()), QMessageBox::Ok);
        ui->imie->clear();
        ui->nazwisko->clear();
        ui->pesel->clear();
    }

    this->pacjent.reset(new Pacjent(pacjent));
    this->pacjent->czyJest = this->obsluga->sprawdzCzyIstniejePacjent(pacjent);
    if(this->pacjent->czyJest){
        this->pacjent->edytuj_Pacjent(pacjent, obsluga);
        QMessageBox msgBox;
        msgBox.setText("Informacja");
        msgBox.setInformativeText("Znaleziono pacjenta.\n Przejść do edycji czy wyswietlic?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::Yes);
        int ret = msgBox.exec();
        switch(ret){
        case QMessageBox::Cancel:
            ui->imie->clear();
            ui->nazwisko->clear();
            ui->pesel->clear();
            break;
        case QMessageBox::Ok:
            emit signalSend(this->pacjent, this->obsluga);
            edycja->show();
            break;
        case QMessageBox::Yes:
            emit signalSend(this->pacjent, this->obsluga);
            pokaz->show();
            break;
        }
    }
    else{
        QMessageBox::information(this, "Error!", "Brak Pacjenta", QMessageBox::Ok);
    }
}

