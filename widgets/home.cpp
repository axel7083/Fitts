#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    // On met en place l'UI avec le fichier généré à partir de mainwindows.ui
    ui->setupUi(this);

    // On ajoute nous même le graphique CAR il ne peut pas être ajouter depuis l'éditeur
    graphicView = new GraphicWidget;
    connect(graphicView, SIGNAL(onFinish(FittsModel*)), this, SLOT(onGraphFinish(FittsModel*)));
    ui->homeContainer->addWidget(graphicView);
}

Home::~Home()
{
    delete ui;
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
