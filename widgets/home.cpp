#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{

    ui->setupUi(this);

    //QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //QStackedLayout *mainStack = new QStackedLayout;
    //mainLayout->addLayout(mainStack);

    QLabel *label = new QLabel(this);
    label->setText("Test");
    ui->homeContainer->addWidget(label);

    graphicView = new GraphicWidget;
    connect(graphicView, SIGNAL(onFinish(int)), this, SLOT(onGraphFinish(int)));
    ui->homeContainer->addWidget(graphicView);
}

Home::~Home()
{
    delete ui;
}

void Home::reset() {
    graphicView->reset();
}


void Home::onGraphFinish(int i) {
    qDebug() << "onGraphFinish ";
    emit onHomeEvent(HOME_GAME_END);
}

void Home::on_home_settings_btn_clicked()
{
    emit onHomeEvent(HOME_OPEN_SETTINGS);
}
