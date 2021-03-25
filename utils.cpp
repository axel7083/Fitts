#include "utils.h"

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
