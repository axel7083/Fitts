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
        openResults((FittsModel *) obj); // => sends parameters
        break;
    case HOME_OPEN_SETTINGS:
        openSettings();
        break;
    case HOME_OPEN_RAPPEL:
        openReminder();
        break;
    case HOME_EXIT_PRGM:
        qApp->exit();
        break;
    default:

        break;
    }
}

// Ceci permet de recevoir des events depuis le widget Settings
void MainWindow::onSettingsEvent(int val, void *obj) {
    qDebug() << "[MainWindow] onSettingsEvent";

    switch(val) {
    case SETTINGS_CLOSE:
        model = (FittsModel*) obj;
        qDebug() << model->nbCible;
        openHome();
        break;
    default:

        break;
    }
}
//Ceci permet de recevoir des events depuis le widget Reminder
void MainWindow::onReminderEvent(int val, void *obj) {
    qDebug() << "[MainWindow] onRappelEvent";

    switch(val) {
    case REMINDER_CLOSE:
        openHome();
        break;
    default:

        break;
    }
}

// Ceci permet de recevoir des events depuis le widget Results
void MainWindow::onResultsEvent(int val) {
    qDebug() << "[MainWindow] onResultsEvent";
    switch(val) {
    case RESULTS_RESTART:
        openHome();
        break;
    case RESULTS_EXIT_PRGM:
        qApp->exit();
    default:

        break;
    }
}

void MainWindow::openHome() {
    qDebug() << "Opening home";
    home = new Home(model);
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
    settings = new Settings(model);
    connect(settings, SIGNAL(onSettingsEvent(int,void*)), this, SLOT(onSettingsEvent(int,void*)));
    this->setCentralWidget(settings);
}

void MainWindow::openReminder() {
    qDebug() << "Opening Reminder";
    reminder = new Reminder();
    connect(reminder, SIGNAL(onReminderEvent(int,void*)), this, SLOT(onReminderEvent(int,void*)));
    this->setCentralWidget(reminder);
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
