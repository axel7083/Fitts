#include "home.h"
#include "ui_home.h"

Home::Home(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    // On met en place l'UI avec le fichier généré à partir de mainwindows.ui
    ui->setupUi(this);

    information = new QLabel();
    //information->setText("Hello world");
    ui->homeContainer->addWidget(information);
    information->setFont(QFont("Roboto", 15));

    // On ajoute nous même le graphique CAR il ne peut pas être ajouter depuis l'éditeur
    graphicView = new GraphicWidget(model);
    connect(graphicView, SIGNAL(onFinish(FittsModel*)), this, SLOT(onGraphFinish(FittsModel*)));
    connect(graphicView, SIGNAL(onTargetChange(int)), this, SLOT(onTargetChange(int)));
    ui->homeContainer->addWidget(graphicView);


}

Home::~Home()
{
    delete ui;
}

void Home::onTargetChange(int val) {
    information->setText("Target left: " + QString::number(val));
}

// Cette fonction est un callback du widget graphwidget
void Home::onGraphFinish(FittsModel* val) {
    qDebug() << "onGraphFinish";
    emit onHomeEvent(HOME_GAME_END, (void *) val);
}

// Simple listener du bouton
void Home::on_home_settings_btn_clicked()
{
    emit onHomeEvent(HOME_OPEN_SETTINGS,NULL);
}

void Home::on_home_rappel_btn_clicked()
{
    emit onHomeEvent(HOME_OPEN_RAPPEL,NULL);
}

void Home::on_Exit_clicked()
{
    emit onHomeEvent(HOME_EXIT_PRGM,NULL);
}

void Home::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        // retranslate designer form (single inheritance approach)
        ui->retranslateUi(this);
}
