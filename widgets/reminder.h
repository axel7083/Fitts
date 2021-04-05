#ifndef REMINDER_H
#define REMINDER_H

#include <QWidget>
#include "constants.h"
#include "./models/fittsmodel.h"

namespace Ui {
class Reminder;
}

class Reminder : public QWidget
{
    Q_OBJECT

public:
    explicit Reminder(FittsModel *model = NULL, QWidget *parent = nullptr);
    ~Reminder();

signals:
    void onReminderEvent(int, void *);

private slots:
    void on_RetourButton_clicked();
    void changeEvent(QEvent* event);

private:
    Ui::Reminder *ui;
    FittsModel * fittsModel;
};


#endif // REMINDER_H
