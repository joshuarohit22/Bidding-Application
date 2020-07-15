#include "bidgrid.h"
#include "ui_bidgrid.h"
#include <QPushButton>
#include <iostream>
#include <string>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QTextDocument>
#include <sstream>
#include <bid.h>

char getSuit(int j)
{
    switch(j)
    {
        case 0:
            return 'C';
        case 1:
            return 'D';
        case 2:
            return 'H';
        case 3:
            return 'S';
        case 4:
            return 'N';
    }
    return '0';
}

int getSuitNumber(char suit)
{

    if (suit == 'C')
        return 0;
    else if (suit == 'D')
        return 1;
    else if (suit == 'H')
        return 2;
    else if (suit == 'S')
        return 3;
    else if (suit == 'N')
        return 4;

    return 5;
}

int getCurrLevel(std::string currBid)
{
    std::string strLevel = currBid.substr(0,1);
    std::stringstream geek(strLevel);

    int currLevel = 0;
    geek >> currLevel;
    return currLevel;
}

bidGrid::bidGrid(std::vector <Node *> bidSeq, Node *currNode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bidGrid)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Add bid child"));

    int i = bidSeq.size() - 1;

    while (i >= 0)
    {
        if (bidSeq[i]->bid.getBid() == "Pass" || bidSeq[i]->bid.getBid() == "Dbl" || bidSeq[i]->bid.getBid() == "RDbl")
        {
            i = i - 1;
            continue;
        }
        else
            break;
    }

    std::vector <Node *> currChildren = currNode->children;
    bool isChild;
    int suitLevel;
    int currLevel;

    if (i >= 0)
    {
        suitLevel = getSuitNumber(bidSeq[i]->bid.getSuit());
        currLevel = bidSeq[i]->bid.getLevel();
    }
    else
    {
        suitLevel = -1;
        currLevel = -1;
    }
    for (int i = 0;i < 7;i++)
    {
        for (int j = 0;j < 5;j++)
        {
            int level = i + 1;
            char suit = getSuit(j);
            QString name = QStringLiteral("%1%2").arg(level).arg(suit);
            QPushButton *panelButton = new QPushButton(name);
            panelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            connect(panelButton, &QPushButton::clicked, this, &bidGrid::onClicked);

            isChild = false;
            for (auto it = currChildren.begin(); it != currChildren.end();++it)
            {
                if ((*it)->bid.getBid() == name.toStdString())
                {
                    isChild = true;
                    break;
                }
            }
            if (isChild || (level < currLevel) || (level == currLevel && j <= suitLevel))
                panelButton->setEnabled(false);

            ui->gridLayout->addWidget(panelButton, i, j);

        }
    }
    QPushButton *passBtn = new QPushButton(QString("Pass"));
    connect(passBtn, &QPushButton::clicked, this, &bidGrid::onClicked);
    isChild = false;
    for (auto it = currChildren.begin(); it != currChildren.end();++it)
    {
        if ((*it)->bid.getBid() == "Pass")
        {
            isChild = true;
            break;
        }
    }
    if (isChild)
        passBtn->setEnabled(false);
    ui->gridLayout->addWidget(passBtn, 7, 0);

    QPushButton *dblBtn = new QPushButton(QString("Dbl"));
    connect(dblBtn, &QPushButton::clicked, this, &bidGrid::onClicked);
    if (bidSeq.size() == 0 || (bidSeq.size() != 0 && bidSeq[bidSeq.size()-1]->bid.getBid() == "Dbl"))
    {
        dblBtn->setEnabled(false);
    }
    ui->gridLayout->addWidget(dblBtn, 7, 1);

    QPushButton *rdblBtn = new QPushButton(QString("RDbl"));
    connect(rdblBtn, &QPushButton::clicked, this, &bidGrid::onClicked);
    if (bidSeq.size() == 0 || (bidSeq.size() != 0 && bidSeq[bidSeq.size()-1]->bid.getBid() != "Dbl"))
    {
        rdblBtn->setEnabled(false);
    }
    ui->gridLayout->addWidget(rdblBtn, 7, 2);

}

void bidGrid::onClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());

    emit sendBid(btn->text());
    this->close();

}


bidGrid::~bidGrid()
{
    delete ui;
}

















