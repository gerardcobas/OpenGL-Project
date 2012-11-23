/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created: Mon 21. May 10:32:39 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Principal
{
public:
    QHBoxLayout *hboxLayout;
    GLWidget *gLWidget1;
    QVBoxLayout *_3;
    QPushButton *pushButton2;
    QPushButton *pushButton2_2;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QSpacerItem *spacer1;
    QHBoxLayout *_2;
    QSpacerItem *spacer3;
    QPushButton *pushButton1;

    void setupUi(QWidget *Principal)
    {
        if (Principal->objectName().isEmpty())
            Principal->setObjectName(QString::fromUtf8("Principal"));
        Principal->resize(814, 575);
        Principal->setMinimumSize(QSize(700, 550));
        Principal->setSizeIncrement(QSize(1, 1));
        hboxLayout = new QHBoxLayout(Principal);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        gLWidget1 = new GLWidget(Principal);
        gLWidget1->setObjectName(QString::fromUtf8("gLWidget1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(gLWidget1->sizePolicy().hasHeightForWidth());
        gLWidget1->setSizePolicy(sizePolicy);
        gLWidget1->setMinimumSize(QSize(600, 550));
        gLWidget1->setFocusPolicy(Qt::StrongFocus);

        hboxLayout->addWidget(gLWidget1);

        _3 = new QVBoxLayout();
        _3->setSpacing(6);
        _3->setObjectName(QString::fromUtf8("_3"));
        pushButton2 = new QPushButton(Principal);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));

        _3->addWidget(pushButton2);

        pushButton2_2 = new QPushButton(Principal);
        pushButton2_2->setObjectName(QString::fromUtf8("pushButton2_2"));

        _3->addWidget(pushButton2_2);

        pushButton = new QPushButton(Principal);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        _3->addWidget(pushButton);

        checkBox = new QCheckBox(Principal);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        _3->addWidget(checkBox);

        checkBox_2 = new QCheckBox(Principal);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        _3->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(Principal);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        _3->addWidget(checkBox_3);

        spacer1 = new QSpacerItem(20, 340, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _3->addItem(spacer1);

        _2 = new QHBoxLayout();
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        spacer3 = new QSpacerItem(101, 31, QSizePolicy::Fixed, QSizePolicy::Minimum);

        _2->addItem(spacer3);

        pushButton1 = new QPushButton(Principal);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton1->sizePolicy().hasHeightForWidth());
        pushButton1->setSizePolicy(sizePolicy1);
        pushButton1->setMinimumSize(QSize(75, 0));

        _2->addWidget(pushButton1);


        _3->addLayout(_2);


        hboxLayout->addLayout(_3);


        retranslateUi(Principal);
        QObject::connect(pushButton1, SIGNAL(clicked()), Principal, SLOT(close()));
        QObject::connect(pushButton2_2, SIGNAL(clicked()), gLWidget1, SLOT(resetCam()));
        QObject::connect(pushButton2, SIGNAL(clicked()), gLWidget1, SLOT(loadModel()));
        QObject::connect(pushButton, SIGNAL(clicked()), gLWidget1, SLOT(switchCam()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), gLWidget1, SLOT(mostrarcapsa(bool)));
        QObject::connect(checkBox_2, SIGNAL(clicked(bool)), gLWidget1, SLOT(mostrarllumglobal(bool)));
        QObject::connect(checkBox_3, SIGNAL(clicked(bool)), gLWidget1, SLOT(mostrarllumdofi(bool)));

        QMetaObject::connectSlotsByName(Principal);
    } // setupUi

    void retranslateUi(QWidget *Principal)
    {
        Principal->setWindowTitle(QApplication::translate("Principal", "Form1", 0, QApplication::UnicodeUTF8));
        pushButton2->setText(QApplication::translate("Principal", "load model", 0, QApplication::UnicodeUTF8));
        pushButton2_2->setText(QApplication::translate("Principal", "reset cam", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Principal", "switch cam", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("Principal", "Mostar esferes contenidores", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("Principal", "Mostrar llum global", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("Principal", "Mostrar llum dofi", 0, QApplication::UnicodeUTF8));
        pushButton1->setText(QApplication::translate("Principal", "&Sortir", 0, QApplication::UnicodeUTF8));
        pushButton1->setShortcut(QApplication::translate("Principal", "Alt+S", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Principal: public Ui_Principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
