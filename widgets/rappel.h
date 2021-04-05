#ifndef RAPPEL_H
#define RAPPEL_H

#include <QWidget>
#include "constants.h"
#include "./models/fittsmodel.h"

namespace Ui {
class Rappel;
}

class Rappel : public QWidget
{
    Q_OBJECT

public:
    explicit Rappel(FittsModel *model = NULL, QWidget *parent = nullptr);
    ~Rappel();

signals:
    void onRappelEvent(int, void *);

private slots:
    void on_RetourButton_clicked();

private:
    Ui::Rappel *ui;
    FittsModel * fittsModel;
};


#endif // RAPPEL_H
