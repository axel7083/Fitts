#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTranslator>
#include <QSettings>
#include "./widgets/home.h"
#include "./widgets/settings.h"
#include "./widgets/results.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "rappel.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionEnglish_triggered();
    void on_actionFran_ais_triggered();
    void on_actionQuitter_triggered();
    void onHomeEvent(int, void *);
    void onSettingsEvent(int, void *);
    void onRappelEvent(int, void *);
    void onResultsEvent(int);
    void changeEvent(QEvent* event);

private:
    void openSettings();
    void openRappel();
    void openHome();
    void openResults(FittsModel *model);
    Ui::MainWindow *ui;
    QSettings* m_settings;
    QTranslator translator;

    Home *home = NULL;
    Settings *settings = NULL;
    Rappel *rappel = NULL;
    Results *results = NULL;

    FittsModel *model = NULL;
};
#endif // MAINWINDOW_H
