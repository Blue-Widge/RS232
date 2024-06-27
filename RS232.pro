TEMPLATE += app
QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    fenprincipale.cpp

HEADERS += \
    fenprincipale.h

FORMS += \
    fenprincipale.ui

# Include paths for Qt headers
INCLUDEPATH += E:/Programmes/Qt/5.15.2/msvc2019/include
INCLUDEPATH += E:/Programmes/Qt/5.15.2/msvc2019/include/QtWidgets

# Libraries
LIBS += -LE:/Programmes/Qt/5.15.2/msvc2019/lib
LIBS += -lQt5Core -lQt5Gui -lQt5Widgets
QMAKE_PROJECT_DEPTH = 0
