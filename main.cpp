#include "./widgets/mainwindow.h"
#include "utils.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

QTranslator translator;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("HM40");
    QCoreApplication::setApplicationName("Fitts");

    // On met en place le langage enregistré.
    setupLanguage(&a, &translator);

    MainWindow w;
    w.show();

    return a.exec();
}



