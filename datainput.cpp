#include "datainput.h"
#include "ui_datainput.h"
#include <QComboBox>
#include <QLabel>
#include <string>
#include <iostream>


DataInput::DataInput(Node *currChild, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);


    this->currChild = currChild;

    std::cout << currChild->bid.getBid() << std::endl;

    this->setWindowTitle(QString::fromStdString(currChild->bid.getBid()));

    char suits[] = {'C', 'D', 'H', 'S'};

    for (int i = 0;i < 4;++i)
    {
        QLabel *suitLabel = new QLabel(QString(suits[i]));
        ui->gridLayout->addWidget(suitLabel, i, 0);

        QComboBox *lowerBox = new QComboBox;
        QComboBox *upperBox = new QComboBox;
        for (int j = 0;j < 14;++j)
        {
            lowerBox->addItem(QString::number(j));
            upperBox->addItem(QString::number(j));
        }

        lowerBox->setCurrentIndex(currChild->currInfo.length[suits[i]].lower);
        upperBox->setCurrentIndex(currChild->currInfo.length[suits[i]].upper);
        ui->gridLayout->addWidget(lowerBox, i, 1);
        ui->gridLayout->addWidget(upperBox, i, 2);
    }

    QLabel *hcpLabel = new QLabel(QString("HCP"));
    ui->gridLayout->addWidget(hcpLabel, 4, 0);

    QComboBox *lowerBox = new QComboBox;
    QComboBox *upperBox = new QComboBox;
    for (int j = 0;j < 38;++j)
    {
        lowerBox->addItem(QString::number(j));
        upperBox->addItem(QString::number(j));
    }

    lowerBox->setCurrentIndex(currChild->currInfo.hcp.lower);
    upperBox->setCurrentIndex(currChild->currInfo.hcp.upper);
    ui->gridLayout->addWidget(lowerBox, 4, 1);
    ui->gridLayout->addWidget(upperBox, 4, 2);

    QLabel *typeLabel = new QLabel(QString("Bid Type"));
    ui->gridLayout->addWidget(typeLabel, 0, 3);
    QComboBox *typeBox = new QComboBox;
    std::vector <std::string> types{"NULL", "ASKING", "FORCING", "INVITATIONAL", "OPENING", "OVERCALL", "LEAD DIRECTING", "DESCRIPTIVE"
                                   "SIGN-OFF", "PREEMPTIVE", "TRANSFER", "CUE BID", "RESPONSE"};
    int index = -1;
    for (unsigned j = 0;j < types.size(); ++j)
    {
        typeBox->addItem(QString::fromStdString(types[j]));
        if (types[j] == currChild->bid_type)
            index = j;
    }
    std::cout << "datainput index bid type: " << index << std::endl;
    typeBox->setCurrentIndex(index);
    ui->gridLayout->addWidget(typeBox, 0, 4);

    QLabel *infoLabel = new QLabel(QString("Bid Info"));
    ui->gridLayout->addWidget(infoLabel, 1, 3);
    QComboBox *infoBox = new QComboBox;
    std::vector <std::string> info{"NULL", "JACOBY", "STAYMAN", "SMOLEN", "INVERTED MINORS", "BERGEN", "JACOBY 2NT", "DRURY", "WEAK 2", "BLACKWOOD ACE"};
    index = -1;
    for (unsigned j = 0;j < info.size(); ++j)
    {
        infoBox->addItem(QString::fromStdString(info[j]));
        if (info[j] == currChild->bid_info)
            index = j;
    }
    std::cout << "datainput index bid info: " << index << std::endl;
    infoBox->setCurrentIndex(index);
    ui->gridLayout->addWidget(infoBox, 1, 4);

    ui->lineEdit->setText(QString::fromStdString(currChild->comments));

}

DataInput::~DataInput()
{
    delete ui;
}

void DataInput::on_okBtn_clicked()
{
    QLayoutItem *item;
    QWidget *widget;
    QLabel *label;
    QComboBox *lowerBox;
    QComboBox *upperBox;
    QComboBox *bidTypeBox;
    QComboBox *bidInfoBox;
    char suit;
    int lower;
    int upper;

    for (int i = 0;i < 4; ++i)
    {
        item = ui->gridLayout->itemAtPosition(i, 0);
        widget = item->widget();
        label = dynamic_cast<QLabel*>(widget);
//        std::cout << label->text().toStdString() << " ";
        suit = label->text().toStdString()[0];

        item = ui->gridLayout->itemAtPosition(i, 1);
        widget = item->widget();
        lowerBox = dynamic_cast<QComboBox*>(widget);
//        std::cout << lowerBox->currentText().toStdString() << " ";
        lower = stoi(lowerBox->currentText().toStdString());

        item = ui->gridLayout->itemAtPosition(i, 2);
        widget = item->widget();
        upperBox = dynamic_cast<QComboBox*>(widget);
//        std::cout << upperBox->currentText().toStdString() << std::endl;
        upper = stoi(upperBox->currentText().toStdString());

        currChild->currInfo.setLength(suit, lower, upper);

        std::cout << suit << " " << currChild->currInfo.length[suit].lower << " " << currChild->currInfo.length[suit].upper << std::endl;
    }

    item = ui->gridLayout->itemAtPosition(4, 1);
    widget = item->widget();
    lowerBox = dynamic_cast<QComboBox*>(widget);
//        std::cout << lowerBox->currentText().toStdString() << " ";
    lower = stoi(lowerBox->currentText().toStdString());

    item = ui->gridLayout->itemAtPosition(4, 2);
    widget = item->widget();
    upperBox = dynamic_cast<QComboBox*>(widget);
//        std::cout << upperBox->currentText().toStdString() << std::endl;
    upper = stoi(upperBox->currentText().toStdString());

    currChild->currInfo.setHcp(lower, upper);


    item = ui->gridLayout->itemAtPosition(0, 4);
    widget = item->widget();
    bidTypeBox = dynamic_cast<QComboBox*>(widget);
//        std::cout << bidTypeBox->currentText().toStdString() << std::endl;
    currChild->bid_type = bidTypeBox->currentText().toStdString();


    item = ui->gridLayout->itemAtPosition(1, 4);
    widget = item->widget();
    bidInfoBox = dynamic_cast<QComboBox*>(widget);
//        std::cout << bidInfoBox->currentText().toStdString() << std::endl;
    currChild->bid_info = bidInfoBox->currentText().toStdString();

    currChild->comments = ui->lineEdit->text().toStdString();

    std::cout << currChild->currInfo.hcp.lower << " " << currChild->currInfo.hcp.upper << std::endl;

    this->close();
}

void DataInput::on_cancelBtn_clicked()
{
    this->close();
}
