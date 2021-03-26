#include "results.h"
#include "ui_results.h"


Results::Results(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);

    qDebug() << model->a;

    plot = new QChartView;
    plot->setChart(buildGraphResults(model));
    plot->setRenderHint(QPainter::Antialiasing);
    ui->container->addWidget(plot);



}

Results::~Results()
{
    delete ui;
}

void Results::on_restart_clicked()
{
     emit onResultsEvent(RESULTS_RESTART);
}
