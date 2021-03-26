#include "results.h"
#include "ui_results.h"


Results::Results(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);


    // Creating a chart view
    plot = new QChartView;

    // Using utils function, building the chart
    plot->setChart(buildGraphResults(model));
    plot->setRenderHint(QPainter::Antialiasing);

    // Adding the chart to the layout
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
