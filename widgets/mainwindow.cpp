#include "./widgets/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_settings(new QSettings("options.ini", QSettings::IniFormat))
{
    // On setup l'ui depuis le fichier
    ui->setupUi(this);

    // On créer puis place le widget Home au centre
    openHome();

}

// Ceci permet de recevoir des events depuis le widget Home
void MainWindow::onHomeEvent(int val, void *obj) {
    qDebug() << "[MainWindow] onHomeEvent";
    switch(val) {
    case HOME_GAME_END:
        // TODO: go to result page
        openResults((FittsModel *) obj); // => sends parameters
        break;
    case HOME_OPEN_SETTINGS:
        openSettings();
        break;
    default:

        break;
    }
}

// Ceci permet de recevoir des events depuis le widget Settings
void MainWindow::onSettingsEvent(int val) {
    qDebug() << "[MainWindow] onSettingsEvent";

    switch(val) {
    case SETTINGS_CLOSE:
        home = new Home;
        connect(home, SIGNAL(onHomeEvent(int)), this, SLOT(onHomeEvent(int)));
        this->setCentralWidget(home);
        break;
    default:

        break;
    }
}

void MainWindow::onResultsEvent(int val) {
    qDebug() << "[MainWindow] onResultsEvent";
    switch(val) {
    case RESULTS_RESTART:
        openHome();
        break;
    default:

        break;
    }
}

void MainWindow::openHome() {
    qDebug() << "Opening home";
    home = new Home;
    connect(home, SIGNAL(onHomeEvent(int,void*)), this, SLOT(onHomeEvent(int,void*)));
    this->setCentralWidget(home);
}

void MainWindow::openResults(FittsModel *model) {
    qDebug() << "Opening results";
    results = new Results(model);
    connect(results, SIGNAL(onResultsEvent(int)), this, SLOT(onResultsEvent(int)));
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

// Cette fonction est appelé lorsque l'utilisateur appuis sur "langue->français"
void MainWindow::on_actionFran_ais_triggered()
{
    m_settings->setValue("Language",1);
    updateLanguage(m_settings, &translator);
}

// Cette fonction est appelé lorsque l'utilisateur appuis sur "langue->English"
void MainWindow::on_actionEnglish_triggered()
{
    m_settings->setValue("Language",2);
    updateLanguage(m_settings, &translator);
}

// Cette fonction est appelé lorsque l'utilisateur appuis sur "Fichier->quitter"
void MainWindow::on_actionQuitter_triggered()
{
    qApp->exit();
}
