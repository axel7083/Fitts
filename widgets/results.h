#ifndef RESULTS_H
#define RESULTS_H

#include <QWidget>
#include <QChart>
#include <QChartView>

#include "utils.h"
#include "constants.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Results;
}

class Results : public QWidget
{
    Q_OBJECT

public:
    explicit Results(FittsModel *model, QWidget *parent = nullptr);
    ~Results();

private:
    Ui::Results *ui;
    QChartView *plot;


signals:
    void onResultsEvent(int);
private slots:
    void on_restart_clicked();
};

#endif // RESULTS_H