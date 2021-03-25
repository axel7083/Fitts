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
    explicit Home(QWidget *parent = nullptr);
    ~Home();
    void reset();

private:
    Ui::Home *ui;
    GraphicWidget *graphicView;

signals:
    void onHomeEvent(int);

private slots:
    void onGraphFinish(int);
    void on_home_settings_btn_clicked();
};

#endif // HOME_H
