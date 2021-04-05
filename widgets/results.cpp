#include "results.h"
#include "ui_results.h"


Results::Results(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);

    //container
    // TabWidget
    QTabWidget *tab = new QTabWidget();

    // createQChartView(buildGraph_1(model))

    tab->addTab(generateResultLayout(model,createQChartView(buildGraph_1(model))), "Graphique 1");
    tab->addTab(createQChartView(buildGraph_2(model)), "Graphique 2");

    ui->container->addWidget(tab);
}


QChartView *Results::createQChartView(QChart *chart) {
    QChartView *plot = new QChartView;

    // Using utils function, building the chart
    plot->setChart(chart);
    plot->setRenderHint(QPainter::Antialiasing);
    plot->setStyleSheet("background: white");
    return plot;
}

Results::~Results()
{
    delete ui;
}

void Results::on_restart_clicked()
{
    emit onResultsEvent(RESULTS_RESTART);
}

void Results::on_exit_clicked()
{
    emit onResultsEvent(RESULTS_EXIT_PRGM);
}

void Results::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        // retranslate designer form (single inheritance approach)
        ui->retranslateUi(this);
}
