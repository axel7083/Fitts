#include "utils.h"


// Cette fonction retourne le chemin du fichier langage
QString getLangue(int i) {
    switch (i) {
        case 1: // FR
            return ":/translation/Fitts_fr_FR.qm";
            break;
        case 2: // EN
            return ":/translation/Fitts_en_EN.qm";
        default:
            return NULL;
    }
}

// Cette fonction permet d'installer un fichier langage
void setupLanguage(QApplication* app, QTranslator *translator)
{
    QSettings *m_settings;
    m_settings = new QSettings("options.ini", QSettings::IniFormat);

    QString val = getLangue(m_settings->value("Language").toInt());
    if(val == NULL) {
        QStringList languages;
        languages << "English" << "French";
        QString lang = QInputDialog::getItem(NULL,"Select language",
                                             "Language", languages);

        if(lang == "English") {
            m_settings->setValue("Language", 2);
        }
        else {
            m_settings->setValue("Language", 1);
        }
        setupLanguage(app, translator);
        return;
    }

    translator->load(val);
    app->installTranslator(translator);
}

// Cette fonction permet d'actualisé un langage
void updateLanguage(QSettings *settings, QTranslator *translator) {

    QString lang = getLangue(settings->value("Language").toInt());
    if(lang == NULL)
        return;

    QApplication::instance()->removeTranslator(translator);
    if (translator->load(lang)) {
        qDebug() << "LOAD FINISHED";
        QApplication::instance()->installTranslator(translator);
    } else {
        qDebug() << "COULD NOT INSTALL TRANSLATIONS ";
    }
}

QChart *buildGraph_2(FittsModel *fittsModel) {
    QChart *chart = new QChart;

    chart->setTitle("Temps d'exécution en fonction de la distance relative");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QLineSeries *fittsSeries = new QLineSeries;
    fittsSeries->setName("Courbe théorique");
    QCategoryAxis *axis = new QCategoryAxis;

    QList<double> fittsValues;

    for(int i = 0; i < fittsModel->nbCible; ++i) {
        // Calculé la valeur théorique
        double D = sqrt(pow(fittsModel->clickPoints[i].x() - fittsModel->cercleCenter[i].x(),2) + pow(fittsModel->clickPoints[i].y() - fittsModel->cercleCenter[i].y(),2));
        // On multiplie par 1000 pour être en ms
        double value = log2((((2*D) / fittsModel->cercleSize[i]) + 1));
        fittsValues.append(value);
        fittsSeries->append(i,value);

        axis->append(QString::number(value),i);
    }

    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axis->setTitleText("log2(2D/L)");

    chart->addSeries(fittsSeries);

    chart->setAxisX(axis,fittsSeries);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("temps (en ms)");
    chart->setAxisY(axisY,fittsSeries);

    return chart;
}




QChart *buildGraph_1(FittsModel *fittsModel) {

    QChart *chart = new QChart;

    chart->setTitle("Résultats loi Fitts");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QLineSeries *expSeries = new QLineSeries;
    expSeries->setName("Courbe expérimentale");
    QLineSeries *fittsSeries = new QLineSeries;
    fittsSeries->setName("Courbe théorique");
    QCategoryAxis *axis = new QCategoryAxis;

    QList<double> fittsValues;

    for(int i = 0; i < fittsModel->nbCible; ++i) {
        double T = fittsModel->times[i];
        expSeries->append(i,T);


        // Calculé la valeur théorique
        double D = sqrt(pow(fittsModel->clickPoints[i].x() - fittsModel->cercleCenter[i].x(),2) + pow(fittsModel->clickPoints[i].y() - fittsModel->cercleCenter[i].y(),2));
        // On multiplie par 1000 pour être en ms
        double value = (fittsModel->a * 1000) + ((fittsModel->b * 1000) *  log2((D / fittsModel->cercleSize[i]) + 1));
        fittsValues.append(value);
        fittsSeries->append(i,value);

        axis->append(QString::number(i + 1) + "<br />T: "+QString::number(T)+"<br />D: " + QString::number(D),i);
    }

    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addSeries(expSeries);
    chart->addSeries(fittsSeries);

    chart->setAxisX(axis,expSeries);
    chart->setAxisX(axis,fittsSeries);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("temps (en ms)");
    chart->setAxisY(axisY,expSeries);



    // Calcul des valeurs
    // Moyennes
    QList<double> diffValues;
    double diffMoy = 0;

    for (int i = 0; i < fittsValues.size(); ++i) {
        diffValues.append(fabs(fittsValues[i] - fittsModel->times[i]));
        diffMoy += fabs(fittsValues[i] - fittsModel->times[i]);
    }
    diffMoy /= fittsValues.size();

    // On stock la difference de moyenne
    fittsModel->diffMoy = fabs(diffMoy);


    // Ecart type
    double variance = 0;

    for (int i = 0; i < fittsValues.size(); ++i) {
        variance += pow(diffValues[i] - diffMoy,2);
    }
    variance /= fittsValues.size();

    double ecartType = sqrt(variance);

    // On stock l'ecart type
    fittsModel->ecartType = ecartType;
    // On stock l'erreur type
    fittsModel->erreurType = fabs(ecartType / sqrt(fittsValues.size()));

    // On stock itc 95%
    fittsModel->itc95 = 2 * fittsModel->erreurType;

    return chart;
}

QWidget *generateResultLayout(FittsModel *model, QChartView* chart) {
    QWidget *central = new QWidget;
    central->setStyleSheet("background: white");
    QVBoxLayout *resultLayout = new QVBoxLayout(central);


    resultLayout->addWidget(chart);

    QGroupBox *resultBox =  new QGroupBox("Stats");
    resultLayout->addWidget(resultBox);
    QGridLayout *resultBoxLayout = new QGridLayout(resultBox);

    QLabel *label = new QLabel("Ecart-Type : ");
    resultBoxLayout->addWidget(label,0,0);
    QLabel *ecartType = new QLabel(QString::number(model->ecartType));
    resultBoxLayout->addWidget(ecartType,0,1);

    label = new QLabel("Erreur-Type : ");
    resultBoxLayout->addWidget(label,1,0);
    QLabel *erreurType = new QLabel(QString::number(model->erreurType));
    resultBoxLayout->addWidget(erreurType,1,1);

    label = new QLabel("Différence moyenne : ");
    resultBoxLayout->addWidget(label,0,2);
    QLabel *diffMoy = new QLabel(QString::number(model->diffMoy));
    resultBoxLayout->addWidget(diffMoy,0,3);

    label = new QLabel("Intervalle de confiance à 95% : ");
    resultBoxLayout->addWidget(label,1,2);
    QLabel *itc95 = new QLabel(QString::number(model->itc95));
    resultBoxLayout->addWidget(itc95,1,3);

    resultBoxLayout->setColumnStretch(1,10);
    resultBoxLayout->setColumnStretch(3,10);

    resultLayout->addWidget(resultBox);
    return central;
}
