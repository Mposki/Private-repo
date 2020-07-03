#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Logowanie; }
QT_END_NAMESPACE

class Logowanie : public QMainWindow
{
    Q_OBJECT

public:
    Logowanie(QWidget *parent = nullptr);
    ~Logowanie();
    void log_in();
    void check_password();


private slots:
    void on_pushButton_clicked();


private:
    Ui::Logowanie *ui;
};
#endif // LOGOWANIE_H
