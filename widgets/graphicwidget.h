#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QDebug>
#include <QElapsedTimer>
#include <math.h>

#include "./models/fittsmodel.h"

class GraphicWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicWidget();
    void reset();

signals:
    void onFinish(int);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    void setup();
    void initGame();
    void cibleClicked(int x, int y);
    void nextCible();
    void finish();
    FittsModel * fittsModel;
    QElapsedTimer *timer;
};


#endif // GRAPHICWIDGET_H
