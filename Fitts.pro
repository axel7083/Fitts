QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./models/fittsmodel.cpp \
    ./widgets/graphicwidget.cpp \
    ./widgets/home.cpp \
    ./widgets/mainwindow.cpp \
    ./widgets/settings.cpp \
    ./widgets/results.cpp \
    main.cpp \
    utils.cpp \
    widgets/reminder.cpp

HEADERS += \
    ./models/fittsmodel.h \
    ./widgets/graphicwidget.h \
    ./widgets/home.h \
    ./widgets/mainwindow.h \
    ./widgets/settings.h \
    ./widgets/results.h \
    constants.h \
    utils.h \
    widgets/reminder.h

FORMS += \
    ./forms/home.ui \
    ./forms/mainwindow.ui \
    ./forms/results.ui \
    ./forms/settings.ui \
    forms/reminder.ui

TRANSLATIONS += \
    src/translations/Fitts_en_EN.ts

# Icon
win32:RC_ICONS += src/icons/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/icons.qrc \
    src/translations.qrc

DISTFILES += \
    src/translation/Fitts_en_EN.qm \
    src/translation/Fitts_fr_FR.qm \
    data/formule.png
