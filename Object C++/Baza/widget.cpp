#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    try{
        this->obs = std::make_shared<Obsluga>();
    }
    catch(std::string err){
        QString error = QString::fromStdString(err);
        QMessageBox::information(this, "Error!", error, QMessageBox::Ok);
    }
    ui->setupUi(this);
    this->obsl = new obsluzBaze();
    connect(this,SIGNAL(sendId(int)),obsl,SLOT(recieveId(int)));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    std::string login = ui->login->text().toStdString();
    std::string haslo = ui->haslo->text().toStdString();

//    std::shared_ptr<Szyfrowanie> tmp(new Szyfrowanie());
//    tmp->zapiszLogin(login);
//    tmp->zapiszHaslo(haslo);
    std::shared_ptr<Szyfrowanie> szyfr(new Szyfrowanie());
    bool jest;
    try{
        jest = szyfr->porownajSHA(haslo);
    } catch(std::string err){
        QMessageBox::information(this, QString::fromStdString(err), QString::fromStdString(err), QMessageBox::Ok);
        ui->login->clear();
        ui->haslo->clear();
    }
    if(jest){
        this->lekarz = std::make_shared<Lekarz>();
        this->lekarz->dodajLogin(login);
        this->lekarz->dodajHaslo(haslo);

        try{
            if(this->obs->sprawdzLekarza(login, haslo)) { this->lekarz->dodajId(this->obs); }
        }catch(std::string err){
            QMessageBox::information(this, QString::fromStdString(err), typeid(this->obs).name(), QMessageBox::Ok);
            ui->login->clear();
            ui->haslo->clear();
        }
        emit sendId(this->lekarz->zwrocId());
        obsl->show();
        this->hide();
    }
}
