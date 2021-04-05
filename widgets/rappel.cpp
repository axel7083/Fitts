#include "rappel.h"
#include "ui_rappel.h"

Rappel::Rappel(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rappel)
{
    ui->setupUi(this);

    if(model == NULL)
        fittsModel = new FittsModel();
    else
        fittsModel = model;

    ui->image->setPixmap(QPixmap("data/formule").scaled(200,100,Qt::KeepAspectRatio));
    ui->retranslateUi(this);
}

Rappel::~Rappel()
{
    delete ui;
}


void Rappel::on_RetourButton_clicked()
{
      emit onRappelEvent(RAPPEL_CLOSE, fittsModel);
}
