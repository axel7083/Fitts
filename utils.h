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
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>


QT_CHARTS_USE_NAMESPACE

QString getLangue(int i);
void setupLanguage(QApplication* app, QTranslator *translator);
void updateLanguage(QSettings *settings, QTranslator *translator);
QChart *buildGraph_1(FittsModel *fittsModel);
QChart *buildGraph_2(FittsModel *fittsModel);
QWidget *generateResultLayout(FittsModel *model, QChartView* chart);


#endif // UTILS_H
