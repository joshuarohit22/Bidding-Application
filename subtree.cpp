#include "subtree.h"
#include "ui_subtree.h"
#include <QMessageBox>


subtree::subtree(Node *root, std::vector <Node *> bidSeq, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subtree)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("Add Subtree"));

    this->setFixedSize(geometry().width(), geometry().height());

    ui->seqScrollArea->setWidgetResizable(true);
    ui->seqScrollArea->setStyleSheet("background-color:white;");

    ui->childScrollArea->setWidgetResizable(true);
    ui->childScrollArea->setStyleSheet("background-color:white;");


    seqLayout = new QHBoxLayout();
    childrenLayout = new QVBoxLayout();

    ui->seqScrollContents->setLayout(seqLayout);
    ui->childScrollContents->setLayout(childrenLayout);

    this->root = root;
    this->bidSeq = bidSeq;
    currNode = root;

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
        QWidget *childWidget = new QWidget;
        QHBoxLayout *childLayout = new QHBoxLayout();

        //adding bid button to childlayout
        QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
        bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
        QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
//        if (bidSeq.size() > 0 && bidSeq[0] == currNode->children[i])
//            bidBtn->setEnabled(false);
        childLayout->addWidget(bidBtn);

        //adding changes label to childlayout
        QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
        childLayout->addWidget(childText);

        //setting layout to widget and adding to savelayout
        childWidget->setLayout(childLayout);

        childrenLayout->addWidget(childWidget);
    }

    ui->childScrollContents->setLayout(childrenLayout);

}

subtree::~subtree()
{
    delete ui;
}

void subtree::clearLayout(QLayout *layout)
{
    QLayoutItem *item;

    while ((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget())
        {
            delete item->widget();
        }
        delete item;
   }
}


void subtree::onBidBtnClicked()
{
    QPushButton *bidBtn = qobject_cast<QPushButton *>(sender());

    QPushButton *seqBtn = new QPushButton(bidBtn->text());
    QObject::connect(seqBtn, SIGNAL(clicked()), this, SLOT(onSeqBidBtnClicked()));
    seqLayout->addWidget(seqBtn);

    currNode = currNode->getChild(bidBtn->text().toStdString());
    sequence.push_back(currNode);

    clearLayout(childrenLayout);
    delete childrenLayout;
    childrenLayout = new QVBoxLayout();

    unsigned index = 0;
    for (index = 0;index < bidSeq.size();++index)
        if (bidSeq[index] == currNode)
            break;

    for (unsigned i = 0;i < currNode->children.size();++i)
    {

        QWidget *childWidget = new QWidget;
        QHBoxLayout *childLayout = new QHBoxLayout();

        //adding bid button to childlayout
        QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
        bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
        QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
//        if (index < bidSeq.size()-1 && bidSeq[index+1] == currNode->children[i])
//            bidBtn->setEnabled(false);
        childLayout->addWidget(bidBtn);

        //adding changes label to childlayout
        QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
        childLayout->addWidget(childText);

        //setting layout to widget and adding to savelayout
        childWidget->setLayout(childLayout);

        childrenLayout->addWidget(childWidget);
    }

    ui->childScrollContents->setLayout(childrenLayout);


}

void subtree::onSeqBidBtnClicked()
{
    QPushButton *seqBidBtn = qobject_cast<QPushButton *>(sender());

    QList<QPushButton *> allPButtons = ui->seqScrollContents->findChildren<QPushButton *>();


    int i = 0;
    for (;i < allPButtons.size();++i)
    {
        if (allPButtons[i]->text() == seqBidBtn->text())
            break;
    }
    ++i; //to go to the element from which it should be removed
    sequence.erase(sequence.begin() + i, sequence.end());
    for (;i < allPButtons.size();++i)
    {
        seqLayout->removeWidget(allPButtons[i]);
        delete allPButtons[i];
    }

    currNode = sequence[sequence.size()-1];

    clearLayout(childrenLayout);
    delete childrenLayout;
    childrenLayout = new QVBoxLayout();

    unsigned index = 0;
    for (index = 0;index < bidSeq.size();++index)
        if (bidSeq[index] == currNode)
            break;

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
        QWidget *childWidget = new QWidget;
        QHBoxLayout *childLayout = new QHBoxLayout();

        //adding bid button to childlayout
        QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
        bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
        QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
//        if (index < bidSeq.size()-1 && bidSeq[index+1] == currNode->children[i])
//            bidBtn->setEnabled(false);
        childLayout->addWidget(bidBtn);

        //adding changes label to childlayout
        QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
        childLayout->addWidget(childText);

        //setting layout to widget and adding to savelayout
        childWidget->setLayout(childLayout);

        childrenLayout->addWidget(childWidget);
    }

    ui->childScrollContents->setLayout(childrenLayout);

}

void subtree::on_okBtn_clicked()
{
    if (sequence.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("No sequence selected. Selecting root as subtree results in a cycle.");
        msgBox.exec();
        return;
    }

    else if (sequence.size() > 0)
    {
        if (sequence.size() <= bidSeq.size())
        {
            bool flag = true;
            for (unsigned i = 0;i < sequence.size();++i)
            {
                if (sequence[i] != bidSeq[i])
                {
                    flag = false;
                    break;
                }
            }
            if (flag == true)
            {
                QMessageBox msgBox;
                msgBox.setText(QString("Invalid sequence. Results in a cycle. Please Check again"));
                msgBox.exec();
                return;
            }
        }

        emit sendNode(sequence[sequence.size()-1]);
        this->close();
        return;
    }
}

void subtree::on_cancelBtn_clicked()
{
    this->close();
}

void subtree::on_rootBtn_clicked()
{
    QList<QPushButton *> allPButtons = ui->seqScrollContents->findChildren<QPushButton *>();


    for (auto btn : allPButtons)
    {
        seqLayout->removeWidget(btn);
        delete btn;

    }

    sequence.clear();

    currNode = root;

    clearLayout(childrenLayout);
    delete childrenLayout;
    childrenLayout = new QVBoxLayout();


    for (unsigned i = 0;i < currNode->children.size();++i)
    {
        QWidget *childWidget = new QWidget;
        QHBoxLayout *childLayout = new QHBoxLayout();

        //adding bid button to childlayout
        QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
        bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
        QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
//        if (bidSeq.size() > 0 && bidSeq[0] == currNode->children[i])
//            bidBtn->setEnabled(false);
        childLayout->addWidget(bidBtn);

        //adding changes label to childlayout
        QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
        childLayout->addWidget(childText);

        //setting layout to widget and adding to savelayout
        childWidget->setLayout(childLayout);

        childrenLayout->addWidget(childWidget);
    }


    ui->childScrollContents->setLayout(childrenLayout);


}
