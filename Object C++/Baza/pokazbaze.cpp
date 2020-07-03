#include "pokazbaze.h"
#include "ui_pokazbaze.h"
#include <QSqlTableModel>

pokazBaze::pokazBaze(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pokazBaze)
{
    ui->setupUi(this);
}

pokazBaze::~pokazBaze()
{
    delete ui;
}

void pokazBaze::signalR(std::shared_ptr<Pacjent>& p, std::shared_ptr<Obsluga>& o, int i)
{
    this->pac = p;
    this->obs = o;
    this->wyborOpcji = i;
    model = new QSqlTableModel(this, obs->db);
    switch(wyborOpcji){
    case 1:
        model->setTable("leki");
        break;
    case 2:
        model->setTable("badanie");
    }
    model->setFilter("idPacjent = " + QString::number(pac->id));
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->show();
}

void pokazBaze::on_dodaj_clicked()
{
    model->insertRow(model->rowCount());//doczytać w dokumentacji
}

void pokazBaze::on_usun_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
}

void pokazBaze::on_aktualizuj_clicked()
{
    model->submitAll();
    model->select();
}
