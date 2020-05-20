/********************************************************************************
** Form generated from reading UI file 'bidgrid.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIDGRID_H
#define UI_BIDGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bidGrid
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QDialog *bidGrid)
    {
        if (bidGrid->objectName().isEmpty())
            bidGrid->setObjectName(QString::fromUtf8("bidGrid"));
        bidGrid->resize(478, 317);
        gridLayoutWidget = new QWidget(bidGrid);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 60, 271, 211));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(bidGrid);

        QMetaObject::connectSlotsByName(bidGrid);
    } // setupUi

    void retranslateUi(QDialog *bidGrid)
    {
        bidGrid->setWindowTitle(QCoreApplication::translate("bidGrid", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bidGrid: public Ui_bidGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIDGRID_H
