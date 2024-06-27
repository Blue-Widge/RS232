/********************************************************************************
** Form generated from reading UI file 'fenprincipale.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENPRINCIPALE_H
#define UI_FENPRINCIPALE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fenprincipale
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *fenprincipale)
    {
        if (fenprincipale->objectName().isEmpty())
            fenprincipale->setObjectName(QString::fromUtf8("fenprincipale"));
        fenprincipale->resize(800, 600);
        centralwidget = new QWidget(fenprincipale);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        fenprincipale->setCentralWidget(centralwidget);
        menubar = new QMenuBar(fenprincipale);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        fenprincipale->setMenuBar(menubar);
        statusbar = new QStatusBar(fenprincipale);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        fenprincipale->setStatusBar(statusbar);

        retranslateUi(fenprincipale);

        QMetaObject::connectSlotsByName(fenprincipale);
    } // setupUi

    void retranslateUi(QMainWindow *fenprincipale)
    {
        fenprincipale->setWindowTitle(QCoreApplication::translate("fenprincipale", "fenprincipale", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fenprincipale: public Ui_fenprincipale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPALE_H
