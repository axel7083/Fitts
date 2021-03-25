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
    void onHomeEvent(int);
    void onSettingsEvent(int);
    void changeEvent(QEvent* event);

private:
    void openSettings();
    void openHome();
    void openResults();
    Ui::MainWindow *ui;
    QSettings* m_settings;
    QTranslator translator;

    Home *home = NULL;
    Settings *settings = NULL;
    Results *results = NULL;
};
#endif // MAINWINDOW_H
