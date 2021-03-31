#ifndef UTILS_H
#define UTILS_H

#include <QApplication>
#include <QString>
#include <QMainWindow>
#include <QDebug>
#include <QTranslator>
#include <QSettings>
#include <QInputDialog>
#include <math.h>

#include "./models/fittsmodel.h"

#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QCategoryAxis>




QT_CHARTS_USE_NAMESPACE

QString getLangue(int i);
void setupLanguage(QApplication* app, QTranslator *translator);
void updateLanguage(QSettings *settings, QTranslator *translator);
QChart *buildGraphResults(FittsModel *fittsModel);

#endif // UTILS_H
