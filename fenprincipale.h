#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QSpinBox>
#include <QTextEdit>

class FenPrincipale : public QWidget
{
    Q_OBJECT
public:
    FenPrincipale();
private slots:
    void genererTrame();
private:
    QLineEdit *Charactere;
    QSpinBox *Decimal;
    QSpinBox *HexaDecimal;
    QSpinBox *Binaire;
    QComboBox *Bits;
    QComboBox *Stops;
    QComboBox *Bauds;
    QPushButton *Generer;
    QPushButton *Quitter;

    QTextEdit *InfoFinals;

};

QString convertHexa(int deci);

#endif // FENPRINCIPALE_H
