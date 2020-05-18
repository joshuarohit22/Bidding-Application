/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

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

class Ui_test
{
public:
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *root;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *seqLabel;
    QScrollArea *seqScrollArea;
    QWidget *seqScrollContents;
    QLabel *parentInfoLabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *childLabel;
    QScrollArea *saveScrollArea;
    QWidget *saveScrollContents;
    QVBoxLayout *verticalLayout_2;
    QPushButton *addSubTree;
    QPushButton *addChildButton;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *newFile;
    QPushButton *LoadFile;
    QPushButton *SaveFile;

    void setupUi(QWidget *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QString::fromUtf8("test"));
        test->resize(800, 437);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(test->sizePolicy().hasHeightForWidth());
        test->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(test);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter = new QSplitter(test);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        root = new QPushButton(layoutWidget);
        root->setObjectName(QString::fromUtf8("root"));

        horizontalLayout_3->addWidget(root);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_3->setStretch(1, 1);
        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        seqLabel = new QLabel(layoutWidget1);
        seqLabel->setObjectName(QString::fromUtf8("seqLabel"));
        seqLabel->setSizeIncrement(QSize(1, 1));
        seqLabel->setAutoFillBackground(false);

        verticalLayout->addWidget(seqLabel);

        seqScrollArea = new QScrollArea(layoutWidget1);
        seqScrollArea->setObjectName(QString::fromUtf8("seqScrollArea"));
        seqScrollArea->setSizeIncrement(QSize(1, 1));
        seqScrollArea->setAutoFillBackground(true);
        seqScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        seqScrollArea->setWidgetResizable(true);
        seqScrollContents = new QWidget();
        seqScrollContents->setObjectName(QString::fromUtf8("seqScrollContents"));
        seqScrollContents->setGeometry(QRect(0, 0, 778, 119));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(seqScrollContents->sizePolicy().hasHeightForWidth());
        seqScrollContents->setSizePolicy(sizePolicy1);
        seqScrollContents->setSizeIncrement(QSize(1, 1));
        seqScrollArea->setWidget(seqScrollContents);

        verticalLayout->addWidget(seqScrollArea);

        verticalLayout->setStretch(1, 1);
        splitter->addWidget(layoutWidget1);
        parentInfoLabel = new QLabel(splitter);
        parentInfoLabel->setObjectName(QString::fromUtf8("parentInfoLabel"));
        parentInfoLabel->setAutoFillBackground(true);
        splitter->addWidget(parentInfoLabel);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        childLabel = new QLabel(layoutWidget2);
        childLabel->setObjectName(QString::fromUtf8("childLabel"));
        childLabel->setSizeIncrement(QSize(1, 1));
        childLabel->setAutoFillBackground(true);

        verticalLayout_3->addWidget(childLabel);

        saveScrollArea = new QScrollArea(layoutWidget2);
        saveScrollArea->setObjectName(QString::fromUtf8("saveScrollArea"));
        saveScrollArea->setSizeIncrement(QSize(1, 1));
        saveScrollArea->setAutoFillBackground(true);
        saveScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        saveScrollArea->setWidgetResizable(true);
        saveScrollContents = new QWidget();
        saveScrollContents->setObjectName(QString::fromUtf8("saveScrollContents"));
        saveScrollContents->setGeometry(QRect(0, 0, 675, 120));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(saveScrollContents->sizePolicy().hasHeightForWidth());
        saveScrollContents->setSizePolicy(sizePolicy2);
        saveScrollContents->setSizeIncrement(QSize(1, 1));
        saveScrollArea->setWidget(saveScrollContents);

        verticalLayout_3->addWidget(saveScrollArea);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        addSubTree = new QPushButton(layoutWidget2);
        addSubTree->setObjectName(QString::fromUtf8("addSubTree"));

        verticalLayout_2->addWidget(addSubTree);

        addChildButton = new QPushButton(layoutWidget2);
        addChildButton->setObjectName(QString::fromUtf8("addChildButton"));
        addChildButton->setSizeIncrement(QSize(1, 1));
        addChildButton->setAutoFillBackground(true);

        verticalLayout_2->addWidget(addChildButton);


        horizontalLayout->addLayout(verticalLayout_2);

        splitter->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(splitter);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        newFile = new QPushButton(layoutWidget3);
        newFile->setObjectName(QString::fromUtf8("newFile"));

        horizontalLayout_2->addWidget(newFile);

        LoadFile = new QPushButton(layoutWidget3);
        LoadFile->setObjectName(QString::fromUtf8("LoadFile"));

        horizontalLayout_2->addWidget(LoadFile);

        SaveFile = new QPushButton(layoutWidget3);
        SaveFile->setObjectName(QString::fromUtf8("SaveFile"));

        horizontalLayout_2->addWidget(SaveFile);

        horizontalLayout_2->setStretch(0, 1);
        splitter->addWidget(layoutWidget3);

        verticalLayout_4->addWidget(splitter);


        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QWidget *test)
    {
        test->setWindowTitle(QApplication::translate("test", "test", nullptr));
        root->setText(QApplication::translate("test", "Root", nullptr));
        seqLabel->setText(QApplication::translate("test", "Current Seqeunce", nullptr));
        parentInfoLabel->setText(QApplication::translate("test", "TextLabel", nullptr));
        childLabel->setText(QApplication::translate("test", "Current Children", nullptr));
        addSubTree->setText(QApplication::translate("test", "Add Subtree", nullptr));
        addChildButton->setText(QApplication::translate("test", "Addchild", nullptr));
        newFile->setText(QApplication::translate("test", "New File", nullptr));
        LoadFile->setText(QApplication::translate("test", "Load File", nullptr));
        SaveFile->setText(QApplication::translate("test", "Save File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
