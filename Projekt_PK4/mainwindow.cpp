#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo.h>
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->show();

    ui->imie->setPlaceholderText("Wpisz imię");
    ui->nazwisko->setPlaceholderText("Wpisz nazwisko");
    ui->pesel->setPlaceholderText("Wpisz pesel");
    ui->data_uro->setPlaceholderText("Wpisz data uro");
    ui->miasto->setPlaceholderText("Wpisz miasto");
    ui->adres->setPlaceholderText("Wpisz adres");
    ui->choroba->setPlaceholderText("Wpisz chorobę");
    ui->lek1->setPlaceholderText("Wpisz lek");
    ui->lek2->setPlaceholderText("Wpisz lek");
    ui->lek3->setPlaceholderText("Wpisz lek");
    ui->lek4->setPlaceholderText("Wpisz lek");
    ui->dawka1->setPlaceholderText("Wpisz dawkowanie");
    ui->dawka2->setPlaceholderText("Wpisz dawkowanie");
    ui->dawka3->setPlaceholderText("Wpisz dawkowanie");
    ui->dawka4->setPlaceholderText("Wpisz dawkowanie");
    ui->badanie1->setPlaceholderText("Wpisz badanie");
    ui->badanie2->setPlaceholderText("Wpisz badanie");
    ui->badanie3->setPlaceholderText("Wpisz badanie");
    ui->badanie4->setPlaceholderText("Wpisz badanie");
    ui->objawy->setPlaceholderText("Wpisz objawy");

    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPort(3306);
    db.setPassword("");
    db.setDatabaseName("projekt");

    try {
        if(!db.open())
                throw 1;

    } catch (int) {
        QMessageBox::information(this, "Połączenie z bazą danych", "Błąd!");
        MainWindow::close();
        ui->~MainWindow();
    }

}

void usun(Pacjent *p)
{
    delete p;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_zamknij_clicked()
{
    unique_ptr<Pacjent> pacjent(new Pacjent);

    pacjent->imie=ui->imie->text();
    pacjent->nazwisko=ui->nazwisko->text();
    pacjent->pesel=ui->pesel->text();
    pacjent->data_uro=ui->data_uro->text();
    pacjent->Adres::adres=ui->adres->text();
    pacjent->Adres::miasto=ui->miasto->text();
    pacjent->Choroba::nazwa = ui->choroba->text();

    QString lek1 = ui->lek1->text();
    QString lek2 = ui->lek2->text();
    QString lek3 = ui->lek3->text();
    QString lek4 = ui->lek4->text();
    QString badanie1 = ui->badanie1->text();
    QString badanie2 = ui->badanie2->text();
    QString badanie3 = ui->badanie3->text();
    QString badanie4 = ui->badanie4->text();
    QString dawka1 = ui->dawka1->text();
    QString dawka2 = ui->dawka2->text();
    QString dawka3 = ui->dawka3->text();
    QString dawka4 = ui->dawka4->text();
    QString objawy = ui->objawy->text();


    QString tab_lek[4][2];
    tab_lek[0][0]=lek1;
    tab_lek[0][1]=dawka1;
    tab_lek[1][0]=lek2;
    tab_lek[1][1]=dawka2;
    tab_lek[2][0]=lek3;
    tab_lek[2][1]=dawka3;
    tab_lek[3][0]=lek4;
    tab_lek[3][1]=dawka4;

    for (int i=0;i<4;i++) {
        Lek *lek=new Lek;
        lek->nazwa=tab_lek[i][0];
        lek->dawkowanie=tab_lek[i][1];
        tab_leki.push_back(*lek);
    }

    QString tab_badanie[4];
    tab_badanie[0]=badanie1;
    tab_badanie[1]=badanie2;
    tab_badanie[2]=badanie3;
    tab_badanie[3]=badanie4;

    for (int i=0;i<4;i++) {
        Badanie *badanie=new Badanie;
        badanie->nazwa=tab_badanie[i];
        tab_badania.push_back(*badanie);
    }

    pacjent->Objawy::objawy=objawy;

    vector<Lek>::iterator lek;
    vector<Badanie>::iterator badanie;

    lek=tab_leki.begin();
    badanie=tab_badania.begin();

    QSqlQuery query(db);

    query.prepare("select imie, nazwisko, pesel from pacjenci where imie like" + pacjent->imie + "and nazwisko like" + pacjent->nazwisko + "and pesel like" + pacjent->pesel);

    MainWindow::sprawdz_czy_istnieje=query.exec();

    if(sprawdz_czy_istnieje == true){

        query.prepare("Update pacjenci where imie like " + pacjent->imie + " and nazwisko like " + pacjent->nazwisko + " and pesel like " + pacjent->pesel + " set imie= imie_n, nazwisko= nazwisko_n, pesel= pesel_n, data_uro=data_uro_n, miasto= miasto_n, adres= adres_n, choroba= choroba_n, lek1= lek1_n, dawka1=dawka1_n, lek2= lek2_n, dawka2=dawka2_n, lek3= lek3_n, dawka3=dawka3_n, lek4= lek4_n, dawka4=dawka4_n, badanie1= badanie1_n, badanie2= badanie2_n, badanie3= badanie3_n, badanie4= badanie4_n, objawy=objawy_n");

        query.bindValue("imie_n", QVariant::fromValue(pacjent->imie));
        query.bindValue("nazwisko_n", QVariant::fromValue(pacjent->nazwisko));
        query.bindValue("pesel_n", QVariant::fromValue(pacjent->pesel));
        query.bindValue("data_uro", QVariant::fromValue(pacjent->data_uro));
        query.bindValue("miasto_n", QVariant::fromValue(pacjent->Adres::miasto));
        query.bindValue("adres_n", QVariant::fromValue(pacjent->Adres::adres));

        query.bindValue("lek1_n", QVariant::fromValue(lek->nazwa));
        query.bindValue("dawka1_n", QVariant::fromValue(lek->dawkowanie));
        query.bindValue("lek2_n", QVariant::fromValue(lek++->nazwa));
        query.bindValue("dawka2_n", QVariant::fromValue(lek->dawkowanie));
        query.bindValue("lek3_n", QVariant::fromValue(lek++->nazwa));
        query.bindValue("dawka3_n", QVariant::fromValue(lek->dawkowanie));
        query.bindValue("lek4_n", QVariant::fromValue(lek++->nazwa));
        query.bindValue("dawka3_n", QVariant::fromValue(lek->dawkowanie));

        query.bindValue("badanie1_n", QVariant::fromValue(badanie->nazwa));
        query.bindValue("badanie2_n", QVariant::fromValue(badanie++->nazwa));
        query.bindValue("badanie3_n", QVariant::fromValue(badanie++->nazwa));
        query.bindValue("badanie4_n", QVariant::fromValue(badanie++->nazwa));

        query.bindValue("objawy_n", QVariant::fromValue(pacjent->Objawy::objawy));

        query.exec();




    }
    else {
        query.prepare("Insert into pacjenci  values (" + pacjent->imie + pacjent->nazwisko + pacjent->pesel + pacjent->data_uro + pacjent->Adres::miasto + pacjent->Adres::adres + pacjent->Choroba::nazwa + badanie->nazwa + badanie++->nazwa + badanie++->nazwa + badanie++->nazwa + lek->nazwa + lek->dawkowanie + lek++->nazwa + lek->dawkowanie + lek++->nazwa + lek->dawkowanie + lek++->nazwa + lek->dawkowanie + ")");
        query.exec();

    }


    db.commit();
    db.close();
    MainWindow::close();
    ui->~MainWindow();
    QString typ=typeid(Pacjent).name();

    QMessageBox::information(this, "Informacja", "Dodałeś " + typ);
}

void MainWindow::on_zamknij_bez_zapisu_clicked()
{
    db.close();
    MainWindow::close();
    ui->~MainWindow();
    QMessageBox::information(this, "Informacja", "Zamknięto bez zapisu!");
}

void MainWindow::on_szukaj_clicked()
{
    QString imie = ui->imie->text();
    QString nazwisko = ui->nazwisko->text();
    QString pesel = ui->pesel->text();

    QSqlQuery query(db);
    query.prepare("Select * from pacjenci where imie like " + imie + " and nazwisko like " + nazwisko + " and pesel like " + pesel);
    if (!query.exec())
        QMessageBox::information(this, "Informacja", "Pacjent o podanych parametrach nieistnieje");
    else
        QMessageBox::information(this, "Informacja", "Pacjent o podanych parametrach nieistnieje");

}

void MainWindow::on_usun_clicked()
{
    QString imie = ui->imie->text();
    QString nazwisko = ui->nazwisko->text();
    QString pesel = ui->pesel->text();

    QSqlQuery query(db);
    query.prepare("Delete from pacjenci where imie like " + imie + " and nazwisko like " + nazwisko + " and pesel like " + pesel);
    query.exec();
    QString typ=typeid(Pacjent).name();

    QMessageBox::information(this, "Informacja", "Usunieto " + typ);
}
