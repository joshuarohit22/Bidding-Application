/********************************************************************************
** Form generated from reading UI file 'subtree.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBTREE_H
#define UI_SUBTREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_subtree
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *rootBtn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QScrollArea *seqScrollArea;
    QWidget *seqScrollContents;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QScrollArea *childScrollArea;
    QWidget *childScrollContents;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QWidget *subtree)
    {
        if (subtree->objectName().isEmpty())
            subtree->setObjectName(QString::fromUtf8("subtree"));
        subtree->resize(772, 467);
        verticalLayout_3 = new QVBoxLayout(subtree);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(subtree);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        rootBtn = new QPushButton(widget);
        rootBtn->setObjectName(QString::fromUtf8("rootBtn"));

        horizontalLayout_2->addWidget(rootBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        seqScrollArea = new QScrollArea(widget1);
        seqScrollArea->setObjectName(QString::fromUtf8("seqScrollArea"));
        seqScrollArea->setWidgetResizable(true);
        seqScrollContents = new QWidget();
        seqScrollContents->setObjectName(QString::fromUtf8("seqScrollContents"));
        seqScrollContents->setGeometry(QRect(0, 0, 750, 143));
        seqScrollArea->setWidget(seqScrollContents);

        verticalLayout->addWidget(seqScrollArea);

        splitter->addWidget(widget1);
        widget2 = new QWidget(splitter);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        childScrollArea = new QScrollArea(widget2);
        childScrollArea->setObjectName(QString::fromUtf8("childScrollArea"));
        childScrollArea->setWidgetResizable(true);
        childScrollContents = new QWidget();
        childScrollContents->setObjectName(QString::fromUtf8("childScrollContents"));
        childScrollContents->setGeometry(QRect(0, 0, 750, 144));
        childScrollArea->setWidget(childScrollContents);

        verticalLayout_2->addWidget(childScrollArea);

        splitter->addWidget(widget2);
        widget3 = new QWidget(splitter);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        horizontalLayout = new QHBoxLayout(widget3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(widget3);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(widget3);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);

        splitter->addWidget(widget3);

        verticalLayout_3->addWidget(splitter);


        retranslateUi(subtree);

        QMetaObject::connectSlotsByName(subtree);
    } // setupUi

    void retranslateUi(QWidget *subtree)
    {
        subtree->setWindowTitle(QApplication::translate("subtree", "Form", nullptr));
        rootBtn->setText(QApplication::translate("subtree", "root", nullptr));
        label->setText(QApplication::translate("subtree", "Current Sequence", nullptr));
        label_2->setText(QApplication::translate("subtree", "Current Children", nullptr));
        okBtn->setText(QApplication::translate("subtree", "Ok", nullptr));
        cancelBtn->setText(QApplication::translate("subtree", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class subtree: public Ui_subtree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBTREE_H
