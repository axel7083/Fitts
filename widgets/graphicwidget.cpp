#include "graphicwidget.h"


#include <QtGlobal>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QHorizontalBarSeries>
#include <QCategoryAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QStringList>
#include <QElapsedTimer>

/*
Cette classe contient de nombreuse fonction
qui n'ont pas été créer par les auteurs du programme
elles ont été reprise à partir du programme initial à
modifier
*/

GraphicWidget::GraphicWidget() {
    fittsModel = new FittsModel();

    // On met en place le widget
    setup();

    // On lance le jeu
    initGame();
}


// Click listener
void GraphicWidget::mousePressEvent(QMouseEvent *event) {
    cibleClicked(event->x(), event->y());
}

void GraphicWidget::setup() {
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsScene *scene = new QGraphicsScene;
    this->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    this->setScene(scene);
    scene->setSceneRect(0,0,this->width(),300);
}

void GraphicWidget::initGame() {

    scene()->clear();

    this->fittsModel->times.clear();

    if(this->fittsModel->maxSize >= this->width() / 2)
        this->fittsModel->maxSize = this->width() / 2;

    if(this->fittsModel->maxSize >= this->height() / 2)
        this->fittsModel->maxSize = this->height() / 2;

    qreal posX = scene()->width() / 2;
    qreal posY = scene()->height() / 2;
    int size = 100;

    scene()->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor("blue")),QBrush(QColor("blue")));
}


void GraphicWidget::cibleClicked(int x, int y) {
    if(this->fittsModel->cercleCenter.isEmpty()) {
        qDebug() << "premier click";
        // Si vide alors premier click, on demarre le timer TODO: fix that
        this->timer = new QElapsedTimer;
        timer->start();

        // On démarre avec la première cible
        this->fittsModel->clickPoints.append(QPoint(x,y));
        this->nextCible();
    }
    else {
        qDebug() << "click";
        QPointF coords = this->mapToScene(x,y);
        if(sqrt(pow(coords.x() - this->fittsModel->cercleCenter.last().x(),2) + pow(coords.y() - this->fittsModel->cercleCenter.last().y(),2)) <= this->fittsModel->cercleSize.last() / 2) {
            // On stock le temps de click
            this->fittsModel->times.append(timer->elapsed());
            // On restart le chrono
            timer->restart();

            // On stock la position du click
            this->fittsModel->clickPoints.append(QPoint(x,y));
            this->nextCible();
        }
    }
}

void GraphicWidget::nextCible() {
    if(!this->fittsModel->cercleCenter.isEmpty())
        this->fittsModel->cibleLeft--;
    //this->fittsView->updateTestMsg(); TODO:

    scene()->clear();

    // On stop si c'est finis
    if(this->fittsModel->cibleLeft == 0) {
        this->finish();
        return;
    }

    // On génère la taille du cercle rouge
    // qrand() % ((high + 1) - low) + low;
    int size = qrand() % ((this->fittsModel->maxSize + 1) - this->fittsModel->minSize) + this->fittsModel->minSize;
    // Car on veut le rayon
    // On place le cercle dans la scene (Attention faut pas qu'il soit en dehors du cadre)
    int sceneW = int(scene()->width());
    int sceneH = int(scene()->height());

    qreal posX = qrand() % ((sceneW - size) - size) + size;
    qreal posY = qrand() % ((sceneH - size) - size) + size;

    // On stock les infos sur le cercle
    this->fittsModel->cercleCenter.append(QPoint(int(posX),int(posY)));
    this->fittsModel->cercleSize.append(size);

    // On place le cercle
    scene()->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor("red")),QBrush(QColor("red")));
}

void GraphicWidget::finish() {

    qDebug() << "Program finish";
    emit onFinish(fittsModel);
    //this->fittsView->graphicView->setEnabled(false);
    //this->fittsView->resultBtn->setEnabled(true);
}

