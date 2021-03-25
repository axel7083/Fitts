#ifndef UTILS_H
#define UTILS_H

#include <QApplication>
#include <QString>
#include <QMainWindow>
#include <QDebug>
#include <QTranslator>
#include <QSettings>
#include <QInputDialog>

QString getLangue(int i);
void setupLanguage(QApplication* app, QTranslator *translator);
void updateLanguage(QSettings *settings, QTranslator *translator);


#endif // UTILS_H
