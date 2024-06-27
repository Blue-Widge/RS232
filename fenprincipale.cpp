#include "fenprincipale.h"
#include "qapplication.h"
FenPrincipale::FenPrincipale()
{
    setWindowTitle("RS232");
    QFormLayout *transmissionLayout = new QFormLayout;
    Charactere = new QLineEdit;
    Decimal = new QSpinBox;
    Decimal->setDisplayIntegerBase(10);
    Decimal->setRange(0,255);
    HexaDecimal = new QSpinBox;
    HexaDecimal->setDisplayIntegerBase(16);
    HexaDecimal->setRange(0,0xFF);
    Binaire = new QSpinBox;
    Binaire->setDisplayIntegerBase(2);
    Binaire->setRange(0,0b11111111);
    transmissionLayout->addRow("&Charactere",Charactere);
    transmissionLayout->addRow("&Decimal", Decimal);
    transmissionLayout->addRow("&Hexadecimal", HexaDecimal);
    transmissionLayout->addRow("&Binaire",Binaire);
    QGroupBox *ChoixTrans = new QGroupBox("Choisissez ce que vous transmettez");
    ChoixTrans->setLayout(transmissionLayout);

    QFormLayout *optionsLayout= new QFormLayout;
    Bits = new QComboBox;
    Bits->addItem("7 bits");
    Bits->addItem("8 bits");
    Stops = new QComboBox;
    Stops->addItem("1 stop");
    Stops->addItem("2 stops");
    Bauds = new QComboBox;
    Bauds->addItem("4800 bauds");
    Bauds->addItem("6300 bauds");
    Bauds->addItem("9600 bauds");
    Bauds->addItem("12800 bauds");
    optionsLayout->addRow("&Nombre de bits : ",Bits);
    optionsLayout->addRow("Nombre de &stops : ",Stops);
    optionsLayout->addRow("&Vitesse en Bauds : ",Bauds);
    QGroupBox *Options = new QGroupBox("Choisissez les options ");
    Options->setLayout(optionsLayout);

    QFormLayout *trameLayout = new QFormLayout;
    InfoFinals = new QTextEdit;
    InfoFinals->setReadOnly(true);
    trameLayout->addRow(InfoFinals);
    QGroupBox *Trame = new QGroupBox("Ici s'affiche les infos finales : ");
    Trame->setLayout(trameLayout);

    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    Generer = new QPushButton("Générer");
    Quitter = new QPushButton("Quitter");
    boutonsLayout->addWidget(Generer);
    boutonsLayout->addWidget(Quitter);
    boutonsLayout->setAlignment(Qt::AlignRight);
    QVBoxLayout *principaleLayout = new QVBoxLayout;
    principaleLayout->addWidget(ChoixTrans);
    principaleLayout->addWidget(Options);
    principaleLayout->addWidget(Trame);
    principaleLayout->addLayout(boutonsLayout);
    setLayout(principaleLayout);

    resize(450,520);

    QObject::connect(Generer,SIGNAL(clicked()), this, SLOT(genererTrame()));
    QObject::connect(Quitter,SIGNAL(clicked()), qApp, SLOT(quit()));

    /*QLineEdit *Charactere;
    QLineEdit *Decimal;
    QLineEdit *HexaDecimal;
    QLineEdit *Binaire;
    QComboBox *Bits;
    QComboBox *Stops;
    QComboBox *Bauds;
    QPushButton *Generer;
    QPushButton *Quitter;*/
}




QString convertHexa(int deci)
{
    QString hexaTemp;
    while (deci != 0)
    {
        int demiOctet = deci % 16;
        if (demiOctet > 9)
        {
            hexaTemp += char(64 - 9 + demiOctet);
        }
        else
        {
            hexaTemp += QString::number(demiOctet);
        }
        deci /= 16;
    }
    QString hexa;
    for (int i(hexaTemp.size()-1); i >=0; i--)
    {
        hexa += hexaTemp[i];
    }
    return hexa;
}

void FenPrincipale::genererTrame() // ICI SE TROUVE TOUTES LES CONVERTIONS ET LES MESSAGES D'ERREURS

// AU CAS OU L'UTILISATEUR RENTRE LES MAUVAISES VALEURS
{

    int deci=Decimal->text().toInt();
    QString carac=Charactere->text();
    QString hexa=HexaDecimal->text().toUpper();
    int bin=Binaire->text().toInt();

    // SI IL N'A RIEN MIS
    if (Charactere->text().isEmpty() && Decimal->value()==0 && HexaDecimal->value()==0 && Binaire->value()==0)
    {
        QMessageBox::warning(this,"ERROR", "Veuillez remplir une des cases");
        return;
    }
    // SI IL A REMPLI PLUSIEURS CASES
    if (!Charactere->text().isEmpty()&&(Decimal->value()!=0||HexaDecimal->value()!=0||Binaire->value()!=0))
    {
        QMessageBox::critical(this,"ERROR", "Veuillez remplir qu'une seule des cases !");
        return;
    }
    else if (Decimal->value()!=0 &&(!Charactere->text().isEmpty()||HexaDecimal->value()!=0||Binaire->value()!=0))
    {
        QMessageBox::critical(this,"ERROR", "Veuillez remplir qu'une seule des cases !");
        return;
    }
    else if (HexaDecimal->value()!=0 &&(Decimal->value()!=0||!Charactere->text().isEmpty()||Binaire->value()!=0))
    {
        QMessageBox::critical(this,"ERROR", "Veuillez remplir qu'une seule des cases !");
        return;
    }
    else if (Binaire->value()!=0 &&(Decimal->value()!=0||HexaDecimal->value()!=0||!Charactere->text().isEmpty()))
    {
        QMessageBox::critical(this,"ERROR", "Veuillez remplir qu'une seule des cases !");
        return;
    }
    //FIN

    // SI IL A REMPLI INCORRECTEMENT
    if (Charactere->text().size()>1)
    {
        QMessageBox::critical(this,"ERROR", "Veuillez entrer qu'un seul caractère à envoyer");
    }
    // FIN

    if (!Charactere->text().isEmpty())
    {
        carac=Charactere->text()[0];
        deci=Charactere->text().toLatin1()[0];
        hexa=convertHexa(deci);
        bin=QString::number(deci,2).toInt();

    }
    if (HexaDecimal->value() != 0)
    {
        deci = QString::number(HexaDecimal->value(),10).toInt();
        bin = QString::number(deci,2).toInt();
        carac =QString(QChar(deci+0));
    }
    if (Decimal->value()!=0)
    {
        hexa=convertHexa(deci);
        bin= QString::number(deci,2).toInt();
        carac = QString(QChar(deci+0))[0];
    }
    if (Binaire->value()!=0)
    {
        deci = QString::number(Binaire->value(),10).toInt();
        hexa=convertHexa(deci);
        carac = QString(QChar(deci+0))[0];
    }

    QString affBin=QString::number(bin);
    QString resultat="Voici les résultats : \n Caractere = "+carac+"\n Decimal = "+QString::number(deci)
                       +"\n Hexadecimal = "+hexa+"\n Binaire = "+affBin+"\n Vitesse = ";
    // A PARTIR D'ICI SE TROUVE LE DESSIN DE LA TRAME


    //TRAITEMENT BITS AVEC STOPS
    int nbBits;
    QString toBin="0";
    if (Bits->currentText()=="7 bits")
    {
        while (affBin.size()<7)
        {
            QString temp= affBin;
            affBin="0";
            affBin+=temp;
        }
        while (affBin.size()>7)
        {
            QString temp;
            for (int i=1; i<affBin.size(); i++)
            {
                temp+=affBin[i];
            }
            affBin=temp;
        }
        nbBits=7;
        for (int i(7); i>=0; i=i-1)
        {
            toBin+=affBin[i];
        }

        if (Stops->currentText()=="1 stop")
        { toBin+='1';} else { toBin+="11";}
    }
    else if (Bits->currentText()=="8 bits")
    {
        while (affBin.size()<8)
        {
            QString temp= affBin;
            affBin="0";
            affBin+=temp;
        }
        nbBits=8;
        for (int i(8); i>=0; i--)
        {
            toBin+=affBin[i];
        }

        if (Stops->currentText()=="1 stop")
        { toBin+='1';} else { toBin+="11";}
    }

    // TRAITEMENT VITESSE
    int nbBauds;
    if (Bauds->currentText()=="4800 bauds")
    {
        resultat+="4800 bauds\n"; nbBauds=4800;
    }
    else if (Bauds->currentText()=="6300 bauds")
    {
        resultat+="6300 bauds\n"; nbBauds=6300;
    }
    else if (Bauds->currentText()=="9600 bauds")
    {
        resultat+="9600 bauds\n"; nbBauds=9600;
    }
    else if (Bauds->currentText()=="12800 bauds")
    {
        resultat+="12800 bauds\n"; nbBauds=12800;
    }
    // TRAITEMENT TEMPS PAR BIT

    float tpBit=toBin.size()*(1000.0/nbBauds);
    QString b;
    b.setNum(tpBit);
    resultat+="un bit s'envoie en " +b+"ms";


    // TRAITEMENT DESSIN
    QString ligneDuHaut;
    QString ligneDuMilieu;
    QString ligneDuBas;

    for (int i=0; i<toBin.size(); i++)
    {
        if (toBin[i]=='1')
        {
            if (i-1>0)
            {
                if (toBin[i-1]=='0')
                {
                    ligneDuBas+="|     ";
                    ligneDuMilieu+="|     ";
                    ligneDuHaut+="___";
                }
                else if (toBin[i-1]=='1')
                {
                    ligneDuBas+="      ";
                    ligneDuMilieu+="      ";
                    ligneDuHaut+="___";
                }
            }
            else
            {
                ligneDuHaut+="___";
                ligneDuMilieu+="      ";
                ligneDuBas+="      ";
            }

            ligneDuHaut+="___";
            ligneDuMilieu+="      ";
            ligneDuBas+="      ";

        }
        else if (toBin[i]=='0')
        {
            if (i-1>0)
            {
                if (toBin[i-1]=='0')
                {
                    ligneDuHaut+="      ";
                    ligneDuMilieu+="      ";
                    ligneDuBas+="___";
                }
                else if (toBin[i-1]=='1')
                {
                    ligneDuHaut+="      ";
                    ligneDuMilieu+="|    ";
                    ligneDuBas+="|__";
                }
            }
            else
            {
                ligneDuBas+="___";
                ligneDuMilieu+="      ";
                ligneDuHaut+="      ";
            }
            ligneDuBas+="___";
            ligneDuMilieu+="      ";
            ligneDuHaut+="      ";

        }
    }

    // AFFICHAGE DES RESULTATS


    resultat+=+"\n Liaison série :\n"+ligneDuHaut+"\n"+ligneDuMilieu+"\n"+ligneDuBas+"\n\nCorrespondance : "+toBin;
    InfoFinals->setText(resultat);
}

