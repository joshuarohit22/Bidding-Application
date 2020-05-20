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

const char *getSuit(int j)
{
    switch(j)
    {
        case 0:
            return "C";
        case 1:
            return "D";
        case 2:
            return "H";
        case 3:
            return "S";
        case 4:
            return "NT";
    }
    return "";
}

int getSuitNumber(std::string currBid)
{
    currBid.erase(currBid.begin());

    if (currBid == "C")
        return 0;
    else if (currBid == "D")
        return 1;
    else if (currBid == "H")
        return 2;
    else if (currBid == "S")
        return 3;
    else if (currBid == "NT")
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
        if (bidSeq[i]->bid == "Pass" || bidSeq[i]->bid == "Dbl" || bidSeq[i]->bid == "RDbl")
        {
            i = i - 1;
            continue;
        }
        else
            break;
    }

    std::string currBid;
    if (i < 0)
    {
        currBid = "0C";
    }
    else
    {
        currBid = bidSeq[i]->bid;
    }

    std::vector <Node *> currChildren = currNode->children;
    bool isChild;


    int suitLevel = getSuitNumber(currBid);
    int currLevel = getCurrLevel(currBid);

    for (int i = 0;i < 7;i++)
    {
        for (int j = 0;j < 5;j++)
        {
            int level = i + 1;
            const char *suit = getSuit(j);
            QString name = QStringLiteral("%1%2").arg(level).arg(suit);
            QPushButton *panelButton = new QPushButton(name);
            panelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            connect(panelButton, &QPushButton::clicked, this, &bidGrid::onClicked);

            isChild = false;
            for (auto it = currChildren.begin(); it != currChildren.end();++it)
            {
                if ((*it)->bid == name.toStdString())
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
        if ((*it)->bid == "Pass")
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
    if (bidSeq.size() == 0 || (bidSeq.size() != 0 && bidSeq[bidSeq.size()-1]->bid == "Dbl"))
    {
        dblBtn->setEnabled(false);
    }
    ui->gridLayout->addWidget(dblBtn, 7, 1);

    QPushButton *rdblBtn = new QPushButton(QString("RDbl"));
    connect(rdblBtn, &QPushButton::clicked, this, &bidGrid::onClicked);
    if (bidSeq.size() == 0 || (bidSeq.size() != 0 && bidSeq[bidSeq.size()-1]->bid != "Dbl"))
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

















