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

    root = new Node("", "");
    currNode = root;
    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid + "\n Parent Info : " + currNode->changes));
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
    chosenBid = str;

    Node *newnode = new Node(str.toStdString(), "");
    currNode->addNode(newnode);

    QWidget *childWidget = new QWidget;
    QHBoxLayout *childLayout = new QHBoxLayout();

    //adding bidlabel to childlayout
    QLabel *bidLabel = new QLabel(chosenBid);
    bidLabel->setObjectName(chosenBid);
    childLayout->addWidget(bidLabel);

    //adding line edit to childlayout
    childLayout->addWidget(new QLineEdit());

    //adding save Btn to childlayout
    QPushButton *saveBtn = new QPushButton("Save");
    saveBtn->setObjectName("Save");
    QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
    childLayout->addWidget(saveBtn);

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

    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid + "\n Parent Info : " + currNode->changes));


    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
        if (currNode->children[i]->saved == true)
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);

            //adding changes label to childlayout
            QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
            childLayout->addWidget(childText);

            //adding modify Btn to childlayout
            QPushButton *modifyBtn = new QPushButton("Modify");
            modifyBtn->setObjectName("Modify");
            QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));
            childLayout->addWidget(modifyBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
        }
        else
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid label to childlayout
            QLabel *bidLabel = new QLabel(QString::fromStdString(currNode->children[i]->bid));
            childLayout->addWidget(bidLabel);

            //adding changes label to childlayout
            QLineEdit *childText = new QLineEdit(QString::fromStdString(currNode->children[i]->changes));
            childLayout->addWidget(childText);

            //adding save Btn to childlayout
            QPushButton *saveBtn = new QPushButton("Save");
            saveBtn->setObjectName("Save");
            QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
            childLayout->addWidget(saveBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);

        }
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

    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid + "\n Parent Info : " + currNode->changes));

    clearLayout(saveLayout);
    delete saveLayout;
    saveLayout = new QVBoxLayout();

    for (unsigned i = 0;i < currNode->children.size();++i)
    {
        if (currNode->children[i]->saved == true)
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);

            //adding changes label to childlayout
            QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
            childLayout->addWidget(childText);

            //adding modify Btn to childlayout
            QPushButton *modifyBtn = new QPushButton("Modify");
            modifyBtn->setObjectName("Modify");
            QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));
            childLayout->addWidget(modifyBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
        }
        else
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid label to childlayout
            QLabel *bidLabel = new QLabel(QString::fromStdString(currNode->children[i]->bid));
            childLayout->addWidget(bidLabel);

            //adding changes line edit to childlayout
            QLineEdit *childText = new QLineEdit(QString::fromStdString(currNode->children[i]->changes));
            childLayout->addWidget(childText);

            //adding save Btn to childlayout
            QPushButton *saveBtn = new QPushButton("Save");
            saveBtn->setObjectName("Save");
            QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
            childLayout->addWidget(saveBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);

        }
    }

    ui->saveScrollContents->setLayout(saveLayout);
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
    int response = newnode->saveChanges(inpText.toStdString());
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


void test::onDelBtnClicked()
{
    QPushButton *delBtn = qobject_cast<QPushButton *>(sender());

    QWidget *parWidget = delBtn->parentWidget();

    QPushButton *modifyBtn = nullptr, *bidBtn = nullptr, *saveBtn = nullptr;
    QList<QPushButton *> allPButtons = parWidget->findChildren<QPushButton *>();
    QPushButton *btn;
    foreach (btn, allPButtons)
    {
        if (btn->text() == QString("Modify"))
        {
            modifyBtn = btn;
        }
        else if (btn->text() == QString("Save"))
        {
            saveBtn = btn;
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

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Bidding tree"), "",tr("Bidding Tree (*.bt);;All Files (*)"));

    std::string fname = fileName.toStdString();
    outFileName = fname;
    std::ifstream fin;
    fin.open(fname);
    std::string line = "";

    int n;

    std::vector <std::string> tree;

    Node **data;
    if (fin.is_open())
    {

        getline(fin, line);
        n = stoi(line);
        std::cout << "n = " << n << std::endl;

        data = (Node **)malloc(n*sizeof(Node *));

        std::string bid, changes, index;
        bool saved;

        while (getline(fin, line))
        {
            line.erase(std::remove(line.begin(),line.end(), '\n'), line.end());
            if (line == "")
                break;
            tree.push_back(line);
        }

        while (getline(fin, line))
        {

            line.erase(std::remove(line.begin(),line.end(), '\n'), line.end());
            std::string toErase = "Node: ";
            line.erase(0, toErase.length());
            index = line;


            getline(fin, line);
            line.erase(std::remove(line.begin(),line.end(), '\n'), line.end());
            toErase = "bid: ";
            line.erase(0, toErase.length());
            bid = line;

            getline(fin, line);
            line.erase(std::remove(line.begin(),line.end(), '\n'), line.end());
            toErase = "saved: ";
            line.erase(0, toErase.length());
            saved = (line == "1");

            getline(fin, line);
            line.erase(std::remove(line.begin(),line.end(), '\n'), line.end());
            toErase = "changes: ";
            line.erase(0, toErase.length());
            changes = line;

            Node *newnode = new Node(bid, changes);
            newnode->saved = saved;

            data[stoi(index)] = newnode;

            getline(fin, line);

        }

        std::vector <int> out;
        for (auto s : tree)
        {
            out = getint(s);


            for (unsigned i = 1; i < out.size(); ++i)
                data[out[0]]->children.push_back(data[out[i]]);
        }

        root = data[0];
        currNode = root;

        ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid + ".\n Parent Info : " + currNode->changes + "."));

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
            if (currNode->children[i]->saved == true)
            {
                QWidget *childWidget = new QWidget;
                QHBoxLayout *childLayout = new QHBoxLayout();

                //adding bid button to childlayout
                QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
                bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
                QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
                childLayout->addWidget(bidBtn);

                //adding changes label to childlayout
                QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
                childLayout->addWidget(childText);

                //adding modify Btn to childlayout
                QPushButton *modifyBtn = new QPushButton("Modify");
                modifyBtn->setObjectName("Modify");
                QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));
                childLayout->addWidget(modifyBtn);

                //adding delete Btn to childlayout
                QPushButton *delBtn = new QPushButton("Delete");
                delBtn->setObjectName("Delete");
                QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
                childLayout->addWidget(delBtn);


                //setting layout to widget and adding to savelayout
                childWidget->setLayout(childLayout);

                saveLayout->addWidget(childWidget);
            }
            else
            {
                QWidget *childWidget = new QWidget;
                QHBoxLayout *childLayout = new QHBoxLayout();

                //adding bid label to childlayout
                QLabel *bidLabel = new QLabel(QString::fromStdString(currNode->children[i]->bid));
                childLayout->addWidget(bidLabel);

                //adding changes line edit to childlayout
                QLineEdit *childText = new QLineEdit(QString::fromStdString(currNode->children[i]->changes));
                childLayout->addWidget(childText);

                //adding save Btn to childlayout
                QPushButton *saveBtn = new QPushButton("Save");
                saveBtn->setObjectName("Save");
                QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
                childLayout->addWidget(saveBtn);

                //adding delete Btn to childlayout
                QPushButton *delBtn = new QPushButton("Delete");
                delBtn->setObjectName("Delete");
                QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
                childLayout->addWidget(delBtn);


                //setting layout to widget and adding to savelayout
                childWidget->setLayout(childLayout);

                saveLayout->addWidget(childWidget);

            }
        }

        ui->saveScrollContents->setLayout(saveLayout);

        changesSaved = true;

        fin.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;

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
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save Bidding tree"), "",tr("Bidding Tree (*.bt);;All Files (*)"));
        fname = fileName.toStdString();
    }
    else
    {
        fname = outFileName;
    }
    std::ofstream fout;
    fout.open(fname, std::ofstream::out | std::ofstream::trunc);

    if (fout.is_open())
    {
        changesSaved = true;

        int currIndex = 0;

        removeColors(root);
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

        fout << currIndex << "\n";

        removeColors(root);
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
                    fout << cnode->index << " ";
                    for (auto n : cnode->children)
                    {
                        fout << n->index << " ";
                        q.push(n);
                    }
                    fout << "\n";
                }
            }
        }

        fout << "\n";

        removeColors(root);
        q.push(root);
        while (!q.empty())
        {
            cnode = q.front();
            q.pop();
            if (cnode->color == false)
            {
                cnode->color = true;
                fout << "Node: " << cnode->index << "\n";
                fout << "bid: " << cnode->bid << "\n";
                fout << "saved: " << cnode->saved << "\n";
                fout << "changes: " << cnode->changes << "\n\n";

                for (auto n : cnode->children)
                    q.push(n);
            }
        }

        fout.close();

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
        if (currNode->children[i]->saved == true)
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid button to childlayout
            QPushButton *bidBtn = new QPushButton(QString::fromStdString(currNode->children[i]->bid));
            bidBtn->setObjectName(QString::fromStdString(currNode->children[i]->bid));
            QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
            childLayout->addWidget(bidBtn);

            //adding changes label to childlayout
            QLabel *childText = new QLabel(QString::fromStdString(currNode->children[i]->changes));
            childLayout->addWidget(childText);

            //adding modify Btn to childlayout
            QPushButton *modifyBtn = new QPushButton("Modify");
            modifyBtn->setObjectName("Modify");
            QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));
            childLayout->addWidget(modifyBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);
        }
        else
        {
            QWidget *childWidget = new QWidget;
            QHBoxLayout *childLayout = new QHBoxLayout();

            //adding bid label to childlayout
            QLabel *bidLabel = new QLabel(QString::fromStdString(currNode->children[i]->bid));
            childLayout->addWidget(bidLabel);

            //adding changes label to childlayout
            QLineEdit *childText = new QLineEdit(QString::fromStdString(currNode->children[i]->changes));
            childLayout->addWidget(childText);

            //adding save Btn to childlayout
            QPushButton *saveBtn = new QPushButton("Save");
            saveBtn->setObjectName("Save");
            QObject::connect(saveBtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
            childLayout->addWidget(saveBtn);

            //adding delete Btn to childlayout
            QPushButton *delBtn = new QPushButton("Delete");
            delBtn->setObjectName("Delete");
            QObject::connect(delBtn, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));
            childLayout->addWidget(delBtn);


            //setting layout to widget and adding to savelayout
            childWidget->setLayout(childLayout);

            saveLayout->addWidget(childWidget);

        }
    }


    ui->saveScrollContents->setLayout(saveLayout);

    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid + "\n Parent Info : " + currNode->changes));


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

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Bidding tree"), "",tr("Bidding Tree (*.bt);;All Files (*)"));
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

    root = new Node("", "");
    currNode = root;
    ui->parentInfoLabel->setText(QString::fromStdString("Parent Bid : " + currNode->bid + "\n Parent Info : " + currNode->changes));

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
    QPushButton *bidBtn = new QPushButton(QString::fromStdString(subtreeNode->bid));
    bidBtn->setObjectName(QString::fromStdString(subtreeNode->bid));
    QObject::connect(bidBtn, SIGNAL(clicked()), this, SLOT(onBidBtnClicked()));
    childLayout->addWidget(bidBtn);

    //adding label to childlayout
    QLabel *childText = new QLabel(QString::fromStdString(subtreeNode->changes));
    childLayout->addWidget(childText);

    //adding modify Btn to childlayout
    QPushButton *modifyBtn = new QPushButton("Modify");
    modifyBtn->setObjectName("Modify");
    QObject::connect(modifyBtn, SIGNAL(clicked()), this, SLOT(onModifyBtnClicked()));
    childLayout->addWidget(modifyBtn);

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
