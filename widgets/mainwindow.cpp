#include "./widgets/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_settings(new QSettings("options.ini", QSettings::IniFormat))
{
    ui->setupUi(this);

    //this->settings = QSettings settings("Settings", QSettings::NativeFormat);
    home = new Home;
    connect(home, SIGNAL(onHomeEvent(int)), this, SLOT(onHomeEvent(int)));
    this->setCentralWidget(home);

}

void MainWindow::onHomeEvent(int val) {
    qDebug() << "[MainWindow] onHomeEvent";

    switch(val) {
    case HOME_GAME_END:
        // TODO: go to result page
        openResults(); // => sends parameters
        break;
    case HOME_OPEN_SETTINGS:
        openSettings();
        break;
    default:

        break;
    }
}

void MainWindow::onSettingsEvent(int val) {
    qDebug() << "[MainWindow] onSettingsEvent";

    switch(val) {
    case SETTINGS_CLOSE:
        home = new Home;
        connect(home, SIGNAL(onHomeEvent(int)), this, SLOT(onHomeEvent(int)));
        this->setCentralWidget(home);
        //this->setCentralWidget(home);
        break;
    default:

        break;
    }
}

void MainWindow::openHome() {
    home = new Home;
    connect(home, SIGNAL(onHomeEvent(int)), this, SLOT(onHomeEvent(int)));
    this->setCentralWidget(home);
}

void MainWindow::openResults() {
    results = new Results;
    //connect(home, SIGNAL(onHomeEvent(int)), this, SLOT(onHomeEvent(int)));
    this->setCentralWidget(results);
}


void MainWindow::openSettings() {
    qDebug() << "Opening settings";
    settings = new Settings(this);
    connect(settings, SIGNAL(onSettingsEvent(int)), this, SLOT(onSettingsEvent(int)));
    this->setCentralWidget(settings);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // retranslate designer form (single inheritance approach)
        ui->retranslateUi(this);
    }
    // remember to call base class implementation
    QMainWindow::changeEvent(event);
}


void MainWindow::on_actionFran_ais_triggered()
{
    m_settings->setValue("Language",1);
    updateLanguage(m_settings, &translator);
}

void MainWindow::on_actionEnglish_triggered()
{
    m_settings->setValue("Language",2);
    updateLanguage(m_settings, &translator);
}

void MainWindow::on_actionQuitter_triggered()
{
    qApp->exit();
}
