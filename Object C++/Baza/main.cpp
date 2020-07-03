#include "widget.h"

#include <QApplication>

/*!
 * \brief main
 * \param argc ilość parametrów
 * \param argv parametry rozpoczęcia programu
 * \return wynik działania poprogramu
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);/*!< wykonanie podprogramu */
    Widget w;/*!< zmienna okna logowania */
    w.show();/*!< okno logowania */
    return a.exec();
}
