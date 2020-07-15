/********************************************************************************
** Form generated from reading UI file 'lengthmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LENGTHMENU_H
#define UI_LENGTHMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LengthMenu
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *LengthMenu)
    {
        if (LengthMenu->objectName().isEmpty())
            LengthMenu->setObjectName(QString::fromUtf8("LengthMenu"));
        LengthMenu->resize(400, 300);
        gridLayoutWidget = new QWidget(LengthMenu);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 30, 331, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        okBtn = new QPushButton(LengthMenu);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(180, 260, 89, 25));
        cancelBtn = new QPushButton(LengthMenu);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(290, 260, 89, 25));

        retranslateUi(LengthMenu);

        QMetaObject::connectSlotsByName(LengthMenu);
    } // setupUi

    void retranslateUi(QDialog *LengthMenu)
    {
        LengthMenu->setWindowTitle(QApplication::translate("LengthMenu", "Dialog", nullptr));
        okBtn->setText(QApplication::translate("LengthMenu", "Ok", nullptr));
        cancelBtn->setText(QApplication::translate("LengthMenu", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LengthMenu: public Ui_LengthMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LENGTHMENU_H
