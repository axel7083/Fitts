#include "settings.h"
#include "ui_settings.h"

Settings::Settings(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    if(model == NULL)
        fittsModel = new FittsModel();
    else
        fittsModel = model;

    setupData();
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_validate_btn_clicked()
{
    //TODO: put some constraint ? => limit a to some values etc..
    fittsModel->a = ui->edit_a->value();
    fittsModel->b = ui->edit_b->value();

    fittsModel->nbCible = ui->edit_target_count->value();
    fittsModel->minSize = ui->edit_min_target->value(); // TODO: checking min < max STRICT
    fittsModel->maxSize = ui->edit_max_target->value();

    emit onSettingsEvent(SETTINGS_CLOSE, fittsModel);
}

void Settings::setupData() {
    ui->edit_a->setValue(fittsModel->a);
    ui->edit_b->setValue(fittsModel->b);

    ui->edit_target_count->setValue(fittsModel->nbCible);
    ui->edit_min_target->setValue(fittsModel->minSize);
    ui->edit_max_target->setValue(fittsModel->maxSize);
}

void Settings::on_restore_default_clicked()
{
    fittsModel = new FittsModel();
    setupData();
}
