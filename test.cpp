#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QHBoxLayout>
#include <iostream>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QToolBar>
#include <assert.h>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "test.h"
#include "ui_test.h"
#include "bidgrid.h"
#include "subtree.h"
#include "inputmenu.h"
#include "datainput.h"


test::test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::test)
{

    ui->setupUi(this);

    ui->seqScrollArea->setWidgetResizable(true);
    ui->seqScrollArea->setStyleSheet("background-color:white;");

    ui->saveScrollArea->setWidgetResizable(true);
    ui->saveScrollArea->setStyleSheet("background-color:white;");


    seqLayout = new QHBoxLayout();
    saveLayout = new QVBoxLayout();

    ui->seqScrollContents->setLayout(seqLayout);
    ui->saveScrollContents->setLayout(saveLayout);

    outFileName = "";
    changesSaved = true;

    root = new Node(Bid());
    currNode = root;
    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : Root\n Parent Info : "));
}

test::~test()
{
    delete ui;        
}

//recursive function to clear layout completely
void test::clearLayout(QLayout *layout)
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

void test::addChildBid(QString str)
{
    changesSaved = false;
    chosenBid = str;

    Node *newnode = new Node(Bid(str.toStdString()));
    currNode->addNode(newnode);

    QWidget *childWidget = new QWidget;
    QHBoxLayout *childLayout = new QHBoxLayout();

    QPushButton *bidBtn = new QPushButton(chosenBid);
    bidBtn->setObjectName(chosenBid);
    QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
    childLayout->addWidget(bidBtn);

    //adding data btn to childlayout
    QPushButton *dataBtn = new QPushButton("Data");
    dataBtn->setObjectName("Data");
    QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
    childLayout->addWidget(dataBtn);

    //adding delete Btn to childlayout
    QPushButton *delBtn = new QPushButton("Delete");
    delBtn->setObjectName("Delete");
    QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
    childLayout->addWidget(delBtn);

    //setting layout to widget and adding to savelayout
    childWidget->setLayout(childLayout);
    saveLayout->addWidget(childWidget);
    ui->saveScrollContents->setLayout(saveLayout);
}

void test::onDataBtnClicked()
{

    changesSaved = false;

    QPushButton *dataBtn = qobject_cast<QPushButton *>(sender());
    QPushButton *bidBtn = nullptr , *delBtn = nullptr;
    QList<QPushButton *> allPButtons = dataBtn->parentWidget()->findChildren<QPushButton *>();
    QPushButton *btn;
    foreach (btn, allPButtons)
    {
        if (btn->text() == QString("Delete"))
        {
            delBtn = btn;
        }
        else if (btn->text() == QString("Data"))
        {
            continue;
        }
        else
        {
            bidBtn = btn;
        }
    }


    Node *currChild = currNode->getChild(bidBtn->text().toStdString());
    DataInput *newWindow = new DataInput(currChild);
    newWindow->show();

}

//void test::addOppPassChildBid(QString str)
//{
//    QPushButton *seqBtn = new QPushButton("Pass");
//    QObject::connect(seqBtn, SIGNAL(clicked()), this, SLOT(onSeqBidBtnClicked()));
//    seqLayout->addWidget(seqBtn);


//    Node *newChildNode = new Node(Bid(str.toStdString()));
//    currNode->addNode(newChildNode);
//    std::cout << currNode->children.size() << std::endl;

//    clearLayout(saveLayout);
//    delete saveLayout;
//    saveLayout = new QVBoxLayout();

//    for (unsigned i = 0;i < currNode->children.size();++i)
//    {
//            QWidget *childWidget = new QWidget;
//            QHBoxLayout *childLayout = new QHBoxLayout();

//            //adding bid button to childlayout
//            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid.getBid()));
//            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid.getBid()));
//            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
//            childLayout->addWidget(bidBtn);


//            //adding line edit to childlayout
//            QPushButton *dataBtn = new QPushButton("Data");
//            dataBtn->setObjectName("Data");
//            QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
//            childLayout->addWidget(dataBtn);


//            //adding delete Btn to childlayout
//            QPushButton *delBtn = new QPushButton("Delete");
//            delBtn->setObjectName("Delete");
//            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
//            childLayout->addWidget(delBtn);


//            //setting layout to widget and adding to savelayout
//            childWidget->setLayout(childLayout);

//            saveLayout->addWidget(childWidget);
//    }
//    ui->saveScrollContents->setLayout(saveLayout);

//}

void test::on_opPassBtn_clicked()
{

    QPushButton *seqBtn = new QPushButton("Pass");
    QObject::connect(seqBtn, SIGNAL(clicked()), this, SLOT(onSeqBidBtnClicked()));
    seqLayout->addWidget(seqBtn);

    Node *passChild = currNode->getChild("Pass");

    if (passChild == nullptr)
    {
        Node *newnode = new Node(Bid("Pass"));
        currNode->addNode(newnode);
        currNode = newnode;
    }
    else
    {
        currNode = passChild;
    }
    bidSeq.push_back(currNode);


    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid.getBid()));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid.getBid()));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);


            //adding line edit to childlayout
            QPushButton *dataBtn = new QPushButton("Data");
            dataBtn->setObjectName("Data");
            QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
            childLayout->addWidget(dataBtn);


            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
    }
    ui->saveScrollContents->setLayout(saveLayout);


    bidGrid *newWindow = new bidGrid(bidSeq, currNode);
    QObject::connect(newWindow, SIGNAL(sendBid(QString)), this, SLOT(addChildBid(QString)));
    newWindow->setModal(true);
    newWindow->exec();

    return;
}


void test::on_addChildButton_clicked()
{
    bidGrid *newWindow = new bidGrid(bidSeq, currNode);
    QObject::connect(newWindow, SIGNAL(sendBid(QString)), this, SLOT(addChildBid(QString)));
    newWindow->setModal(true);
    newWindow->exec();
}

void test::onSeqBidBtnClicked()
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
    bidSeq.erase(bidSeq.begin() + i, bidSeq.end());
    for (;i < allPButtons.size();++i)
    {
        seqLayout->removeWidget(allPButtons[i]);
        delete allPButtons[i];
    }

    currNode = bidSeq[bidSeq.size()-1];

    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid.getBid() + "\n Parent Info : " + currNode->changes));


    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid.getBid()));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid.getBid()));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);


            //adding line edit to childlayout
            QPushButton *dataBtn = new QPushButton("Data");
            dataBtn->setObjectName("Data");
            QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
            childLayout->addWidget(dataBtn);


            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
    }

    ui->saveScrollContents->setLayout(saveLayout);
}

void test::onBidBtnClicked()
{
    QPushButton *bidBtn = qobject_cast<QPushButton *>(sender());

    //adding sequence button with bid text
    QPushButton *seqBtn = new QPushButton(bidBtn->text());
    QObject::connect(seqBtn, SIGNAL(clicked()), this, SLOT(onSeqBidBtnClicked()));
    seqLayout->addWidget(seqBtn);


    currNode = currNode->getChild(bidBtn->text().toStdString());
    bidSeq.push_back(currNode);

    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid.getBid() + "\n Parent Info : " + currNode->changes));

    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid.getBid()));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid.getBid()));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);

            //adding line edit to childlayout
            QPushButton *dataBtn = new QPushButton("Data");
            dataBtn->setObjectName("Data");
            QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
            childLayout->addWidget(dataBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
    }

    ui->saveScrollContents->setLayout(saveLayout);
}



void deleteSubTree(Node *node)
{
    if (node == NULL) return;

    for (auto n : node->children)
    {
        deleteSubTree(n);
    }

    delete node;

    return;
}



void test::onDelBtnClicked()
{
    QPushButton *delBtn = qobject_cast<QPushButton *>(sender());

    QWidget *parWidget = delBtn->parentWidget();

    QPushButton *dataBtn = nullptr, *bidBtn = nullptr;
    QList<QPushButton *> allPButtons = parWidget->findChildren<QPushButton *>();
    QPushButton *btn;
    foreach (btn, allPButtons)
    {
        if (btn->text() == QString("Data"))
        {
            dataBtn = btn;
        }
        else if (btn->text() == QString("Delete"))
        {
            continue;
        }
        else
        {
            bidBtn = btn;
        }
    }



    Node *toDelChild;

    if (bidBtn != nullptr)
        toDelChild = currNode->getChild(bidBtn->text().toStdString());
    else
    {
        QLabel *bidLabel = parWidget->findChild<QLabel *>();
        toDelChild = currNode->getChild(bidLabel->text().toStdString());
    }

    //if the concerned child has non empty subtree
    if (toDelChild->parent.size() > 1)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText(QString("Are you sure you want to remove the subtree from children?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes:
                unsigned index;
                //removing child from parent
                for(index = 0; index < currNode->children.size();++index)
                    if (currNode->children[index] == toDelChild)
                        break;
                currNode->children.erase(currNode->children.begin() + index);

                //removing parent from child
                for(index = 0; index < toDelChild->parent.size();++index)
                    if (toDelChild->parent[index] == currNode)
                        break;
                toDelChild->parent.erase(toDelChild->parent.begin() + index);

                break;

        case QMessageBox::No:
            //dont delete
            return;

        }

    }
    else if (toDelChild->children.size() > 0)
    {
        QMessageBox msgBox;
        std::string msgText = "The following child with bid <b>" + bidBtn->text().toStdString() + "</b> has a non-empty subtree.";
        msgBox.setText(QString::fromStdString(msgText));
        msgBox.setInformativeText(QString("Are you sure you want delete the whole subtree?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes:
            //delete whole subtree
                deleteSubTree(toDelChild);
                unsigned index;
                for(index = 0; index < currNode->children.size();++index)
                    if (currNode->children[index] == toDelChild)
                        break;
                currNode->children.erase(currNode->children.begin() + index);
                break;

        case QMessageBox::No:
            //dont delete
            return;

        }
    }
    //if the concerned child does not have a subtree
    else
    {
        unsigned index;
        for(index = 0; index < currNode->children.size();++index)
            if (currNode->children[index] == toDelChild)
                break;
        currNode->children.erase(currNode->children.begin() + index);

    }

    //frontend remove widget
    changesSaved = false;
    clearLayout(parWidget->layout());
    saveLayout->removeWidget(parWidget);
    delete parWidget;


}


void test::showErrorMsg(QString s)
{
    error_msg.setText(s);
    error_msg.exec();
}

void test::closeEvent(QCloseEvent *event)
{
    if (changesSaved == false)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Do you want to save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                changesSaved = true;
                on_SaveFile_clicked();
                break;
            case QMessageBox::No:
                changesSaved = false;
                break;
            case QMessageBox::Cancel:
                changesSaved = false;
                event->ignore();
                return;
        }
    }
    event->accept();
}

std::vector <int> getint(std::string str)
{
    std::stringstream geek(str);

    int x;

    std::vector <int> out;

    while(geek >> x)
    {
        out.push_back(x);
    }

    return out;
}


void test::on_LoadFile_clicked()
{

    if (changesSaved == false)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Do you want to save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                changesSaved = true;
                on_SaveFile_clicked();
                break;
            case QMessageBox::No:
                changesSaved = false;
                break;
            case QMessageBox::Cancel:
                changesSaved = false;
                return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Bidding Graph"), "",tr("Bidding Graph (*.db);;All Files (*)"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("yjr");
    db.setDatabaseName(fileName);
    db.setUserName("joshua");
    db.setPassword("j");
    bool ok = db.open();
    Node **data;
    if (ok)
    {
        int n;
        QSqlQuery queryStructure;
        QSqlQuery queryNode;

        QSqlQuery query;
        query.exec("Select COUNT(*) from Node;");
        query.next();
        n = query.value(0).toInt();
        std::cout << "Load file n = " << n << std::endl;

        queryStructure.exec("SELECT * from Structure;");
        queryNode.exec("Select * from Node;");



        data = (Node **)malloc(n*sizeof(Node *));

        int index = -1;

        while (queryNode.next())
        {
            index = queryNode.value(0).toInt();
            std::cout << "index = " << index << std::endl;

            std::cout << "comments: " << queryNode.value(13).toString().toStdString() << " Bid: " << queryNode.value(14).toString().toStdString() << std::endl;
            Node *newnode = new Node(Bid(queryNode.value(14).toString().toStdString()));
            data[index] = newnode;

            data[index]->currInfo.setLength('C', queryNode.value(1).toInt(), queryNode.value(2).toInt());
            data[index]->currInfo.setLength('D', queryNode.value(3).toInt(), queryNode.value(4).toInt());
            data[index]->currInfo.setLength('H', queryNode.value(5).toInt(), queryNode.value(6).toInt());
            data[index]->currInfo.setLength('S', queryNode.value(7).toInt(), queryNode.value(8).toInt());
            data[index]->currInfo.setHcp(queryNode.value(9).toInt(), queryNode.value(10).toInt());
            data[index]->bid_type = queryNode.value(11).toString().toStdString();
            data[index]->bid_info = queryNode.value(12).toString().toStdString();
            data[index]->comments = queryNode.value(13).toString().toStdString();
        }

        int parentID, childID;

        while (queryStructure.next())
        {
            parentID = queryStructure.value(0).toInt();
            childID = queryStructure.value(1).toInt();
            std::cout << "parent id: " << parentID << " childID: " << childID << std::endl;

            data[parentID]->children.push_back(data[childID]);
        }

        root = data[0];
        currNode = root;

        ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : Root.\n Parent Info : "));

        //clearing ui
        clearLayout(saveLayout);
        delete saveLayout;
        saveLayout = new QVBoxLayout();

        clearLayout(seqLayout);
        delete seqLayout;
        seqLayout = new QHBoxLayout();
        ui->seqScrollContents->setLayout(seqLayout);

        for (unsigned i = 0;i < currNode->children.size();++i)
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid.getBid()));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid.getBid()));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);

            //adding line edit to childlayout
            QPushButton *dataBtn = new QPushButton("Data");
            dataBtn->setObjectName("Data");
            QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
            childLayout->addWidget(dataBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
        }

        ui->saveScrollContents->setLayout(saveLayout);

        changesSaved = true;


    }




    return;

}

void removeColors(Node *root)
{
    std::queue <Node *> q;
    q.push(root);

    Node *cnode;

    while (!q.empty())
    {
        cnode = q.front();
        q.pop();
        cnode->color = false;

        for (auto n : cnode->children)
            q.push(n);
    }

    return;
}

void test::on_SaveFile_clicked()
{
    std::string fname;

    if (outFileName == "")
    {
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save Bidding Graph"), "",tr("Bidding Graph (*.db);;All Files (*)"));
        fname = fileName.toStdString();
        outFileName = fname;
    }
    else
    {
        fname = outFileName;
    }

    if (fname == "")
        return;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("yjr");
    db.setDatabaseName(QString::fromStdString(fname));
    db.setUserName("joshua");
    db.setPassword("j");
    bool ok = db.open();

    if (ok)
    {
        changesSaved = true;
        std::cout << "db opened " << fname << std::endl;

        QSqlQuery query;

        query.exec("DROP TABLE IF EXISTS Node;");
        query.exec("DROP TABLE IF EXISTS Structure;");

        query.exec("CREATE TABLE IF NOT EXISTS Structure(ParentID INTEGER, ChildID INTEGER);");

        query.exec("CREATE TABLE IF NOT EXISTS Node(NodeID INTEGER, clubs_lower_bound INTEGER, clubs_upper_bound INTEGER,"
                   "diamonds_lower_bound INTEGER, diamonds_upper_bound INTEGER,"
                   "hearts_lower_bound INTEGER, hearts_upper_bound INTEGER,"
                   "spades_lower_bound INTEGER, spades_upper_bound INTEGER,"
                   "hcp_lower_bound INTEGER, hcp_upper_bound INTEGER,"
                   "bid_type TEXT, bid_info TEXT, comments TEXT, bid TEXT);");

        removeColors(root);
        int currIndex = 0;
        std::queue <Node *> q;
        q.push(root);
        Node *cnode;
        while (!q.empty())
        {
            cnode = q.front();
            q.pop();
            if (cnode->color == false)
            {
                cnode->color = true;
                cnode->index = currIndex;
                currIndex++;
                for (auto n : cnode->children)
                    q.push(n);
            }
        }

        removeColors(root);
        int parentID = 0;
        int childID = 0;
        q.push(root);
        while(!q.empty())
        {
            cnode = q.front();
            q.pop();
            if (cnode->color == false)
            {
                cnode->color = true;
                if (cnode->children.size() != 0)
                {
                    parentID = cnode->index;
                    for (auto n : cnode->children)
                    {
                        childID = n->index;
                        std::cout << "saving parentid: " << parentID << " childID: " << childID << std::endl;
                        query.prepare("INSERT INTO Structure(ParentID, ChildID) VALUES(?, ?);");
                        query.addBindValue(parentID);
                        query.addBindValue(childID);
                        query.exec();
                        q.push(n);
                    }
                }
            }
        }

        removeColors(root);
        q.push(root);
        while (!q.empty())
        {
            cnode = q.front();
            q.pop();
            if (cnode->color == false)
            {
                cnode->color = true;
                query.prepare("INSERT INTO Node(NodeID, clubs_lower_bound, clubs_upper_bound,"
                              "diamonds_lower_bound, diamonds_upper_bound,"
                              "hearts_lower_bound, hearts_upper_bound,"
                              "spades_lower_bound, spades_upper_bound,"
                              "hcp_lower_bound, hcp_upper_bound,"
                              "bid_type, bid_info, comments, bid) "
                              "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

                query.addBindValue(cnode->index);
                query.addBindValue(cnode->currInfo.length['C'].lower);
                query.addBindValue(cnode->currInfo.length['C'].upper);
                query.addBindValue(cnode->currInfo.length['D'].lower);
                query.addBindValue(cnode->currInfo.length['D'].upper);
                query.addBindValue(cnode->currInfo.length['H'].lower);
                query.addBindValue(cnode->currInfo.length['H'].upper);
                query.addBindValue(cnode->currInfo.length['S'].lower);
                query.addBindValue(cnode->currInfo.length['S'].upper);
                query.addBindValue(cnode->currInfo.hcp.lower);
                query.addBindValue(cnode->currInfo.hcp.upper);
                query.addBindValue(QString::fromStdString(cnode->bid_type));
                query.addBindValue(QString::fromStdString(cnode->bid_info));
                query.addBindValue(QString::fromStdString(cnode->comments));
                query.addBindValue(QString::fromStdString(cnode->bid.getBid()));
                query.exec();

                for (auto n : cnode->children)
                    q.push(n);
            }
        }
        QSqlQuery queryNode;
        queryNode.exec("Select * from Node;");

        while (queryNode.next())
        {
            std::cout << "Comments: " << queryNode.value(13).toString().toStdString() << " bid:" << queryNode.value(14).toString().toStdString() << std::endl;
        }

    }






    return;
}

void test::on_root_clicked()
{

    QList<QPushButton *> allPButtons = ui->seqScrollContents->findChildren<QPushButton *>();


    for (auto btn : allPButtons)
    {
        seqLayout->removeWidget(btn);
        delete btn;

    }

    bidSeq.clear();

    currNode = root;

    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();


    for (unsigned i = 0;i < currNode->children.size();++i)
    {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid.getBid()));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid.getBid()));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);


            //adding data btn to childlayout
            QPushButton *dataBtn = new QPushButton("Data");
            dataBtn->setObjectName("Data");
            QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
            childLayout->addWidget(dataBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
    }


    ui->saveScrollContents->setLayout(saveLayout);

    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : Root\n Parent Info : "));


    return;
}


void test::on_newFile_clicked()
{

    if (changesSaved == false)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Do you want to save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                changesSaved = true;
                on_SaveFile_clicked();
                break;
            case QMessageBox::No:
                changesSaved = false;
                break;
            case QMessageBox::Cancel:
                changesSaved = false;
                return;
        }
    }

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Bidding Graph"), "",tr("Bidding Graph (*.bd);;All Files (*)"));
    outFileName = fileName.toStdString();

    //clearing ui
    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();
    ui->saveScrollContents->setLayout(saveLayout);

    clearLayout(seqLayout);
    delete seqLayout;
    seqLayout = new QHBoxLayout();
    ui->seqScrollContents->setLayout(seqLayout);

    root = new Node(Bid());
    currNode = root;
    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid.getBid() + "\n Parent Info : " + currNode->changes));

}

void test::on_addSubTree_clicked()
{
    subtree *newWindow = new subtree(root, bidSeq);
    QObject::connect(newWindow, SIGNAL(sendNode(Node *)), this, SLOT(addSubTree(Node *)));
    newWindow->show();
}

void test::addSubTree(Node *subtreeNode)
{
    changesSaved = false;
    currNode->children.push_back(subtreeNode);
    subtreeNode->parent.push_back(currNode);

    QWidget *childWidget = new QWidget;
    QHBoxLayout *childLayout = new QHBoxLayout();

    //adding bidBtn to childlayout
    QPushButton *bidBtn = new QPushButton(QString::fromStdString(subtreeNode->bid.getBid()));
    bidBtn->setObjectName(QString::fromStdString(subtreeNode->bid.getBid()));
    QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
    childLayout->addWidget(bidBtn);

//    //adding label to childlayout
//    QLabel *childText = new QLabel(QString::fromStdString(subtreeNode->changes));
//    childLayout->addWidget(childText);

//    //adding modify Btn to childlayout
//    QPushButton *modifyBtn = new QPushButton("Modify");
//    modifyBtn->setObjectName("Modify");
//    QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));
//    childLayout->addWidget(modifyBtn);

    //adding line edit to childlayout
    QPushButton *dataBtn = new QPushButton("Data");
    dataBtn->setObjectName("Data");
    QObject::connect(dataBtn, SIGNAL(clicked()), this, SLOT(onDataBtnClicked()));
    childLayout->addWidget(dataBtn);


    //adding delete Btn to childlayout
    QPushButton *delBtn = new QPushButton("Delete");
    delBtn->setObjectName("Delete");
    QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
    childLayout->addWidget(delBtn);

    //setting layout to widget and adding to savelayout
    childWidget->setLayout(childLayout);
    saveLayout->addWidget(childWidget);
    ui->saveScrollContents->setLayout(saveLayout);


}



void test::onModifyBtnClicked()
{
    QPushButton *modifyBtn = qobject_cast<QPushButton *>(sender());

    QLabel *viewLabel = modifyBtn->parentWidget()->findChild<QLabel *>();

    //finding delete button and bid button
    QPushButton *delBtn, *bidBtn;
    QList<QPushButton *> allPButtons = modifyBtn->parentWidget()->findChildren<QPushButton *>();
    QPushButton *btn;
    foreach (btn, allPButtons)
    {
        if (btn->text() == QString("Delete"))
        {
            delBtn = btn;
        }
        else if (btn->text() == QString("Modify"))
        {
            continue;
        }
        else
        {
            bidBtn = btn;
        }
    }

    Node *toModChild = currNode->getChild(bidBtn->text().toStdString());

    toModChild->saved = false;

    //replacing bid button with bid label
    changesSaved = false;
    if (bidBtn)
    {
        QLabel *bidLabel = new QLabel(bidBtn->text());
        modifyBtn->parentWidget()->layout()->replaceWidget(bidBtn, bidLabel);
        delete bidBtn;
    }


    //replacing label with lineEdit
    if (viewLabel)
    {
        QLineEdit *lineEdit = new QLineEdit(viewLabel->text());
        modifyBtn->parentWidget()->layout()->replaceWidget(viewLabel, lineEdit);
        delete viewLabel;
    }

    //replacing modify button with save button
    QPushButton *saveBtn = new QPushButton("Save");
    QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
    modifyBtn->parentWidget()->layout()->replaceWidget(modifyBtn, saveBtn);


    delete modifyBtn;

}

void test::onSaveBtnClicked()
{
    QPushButton *saveBtn = qobject_cast<QPushButton *>(sender());
    QList <QPushButton *> allPButtons = saveBtn->parentWidget()->findChildren<QPushButton *>();

    //checking if syntax is correct;
    QLineEdit *lineEdit = saveBtn->parentWidget()->findChild<QLineEdit *>();
    QLabel *bidLabel = saveBtn->parentWidget()->findChild<QLabel *>();
    QString inpText = lineEdit->text();

    Node *newnode = currNode->getChild(bidLabel->text().toStdString());
//    int response = newnode->saveChanges(inpText.toStdString());
    int response = 1;
    std::cout << response << std::endl;
    if (response == 0) //syntax error of inpText
    {
        showErrorMsg(QString("syntax error"));
        return;
    }


    //replacing label of bid with button of bid
    QPushButton *bidBtn = new QPushButton(bidLabel->text());
    saveBtn->parentWidget()->layout()->replaceWidget(bidLabel, bidBtn);
    QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
    delete bidLabel;

    //replacing linedit with label and same text
    if (inpText == QString(""))
    {
        inpText = QString("NIL");
    }
    QLabel *viewLabel = new QLabel(inpText);
    saveBtn->parentWidget()->layout()->replaceWidget(lineEdit, viewLabel);
    delete lineEdit;

    //replacing save button with modify button
    QPushButton *modifyBtn = new QPushButton("Modify");
    modifyBtn->setObjectName("Modify");
    saveBtn->parentWidget()->layout()->replaceWidget(saveBtn, modifyBtn);
    QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));


    changesSaved = false;
    delete saveBtn;

}
