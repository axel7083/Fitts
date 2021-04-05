#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLabel>

#include "./models/fittsmodel.h"
#include "graphicwidget.h"
#include "constants.h"

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(FittsModel *model = NULL, QWidget *parent = nullptr);
    ~Home();

private:
    Ui::Home *ui;
    GraphicWidget *graphicView;
    QLabel *information;

signals:
    void onHomeEvent(int, void *);

private slots:
    void onGraphFinish(FittsModel*);
    void onTargetChange(int);
    void on_home_settings_btn_clicked();
    void on_home_rappel_btn_clicked();
    void on_Exit_clicked();
    void changeEvent(QEvent* event);
};

#endif // HOME_H
