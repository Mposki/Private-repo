#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <memory>

#include "obsluzbaze.h"
#include "obsluga.h"
#include "lekarz.h"
#include "szyfrowanie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

signals:
    void sendId(int id);

private:
    Ui::Widget *ui;
    obsluzBaze *obsl;

protected:
    std::shared_ptr<Obsluga> obs;
    std::shared_ptr<Lekarz> lekarz;
};
#endif // WIDGET_H
