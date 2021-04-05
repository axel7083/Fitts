#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "constants.h"
#include "./models/fittsmodel.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(FittsModel *model = NULL, QWidget *parent = nullptr);
    ~Settings();

signals:
    void onSettingsEvent(int, void *);

private slots:
    void on_validate_btn_clicked();
    void on_restore_default_clicked();
    void changeEvent(QEvent* event);

private:
    Ui::Settings *ui;
    FittsModel * fittsModel;
    void setupData();
};

#endif // SETTINGS_H
