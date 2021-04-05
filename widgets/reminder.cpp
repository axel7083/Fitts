#include "reminder.h"
#include "ui_reminder.h"

Reminder::Reminder(FittsModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Reminder)
{
    ui->setupUi(this);

    ui->retranslateUi(this);
}

Reminder::~Reminder()
{
    delete ui;
}


void Reminder::on_RetourButton_clicked()
{
      emit onReminderEvent(REMINDER_CLOSE, NULL);
}
