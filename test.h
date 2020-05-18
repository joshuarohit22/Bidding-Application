#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <string>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include "node.h"

QT_BEGIN_NAMESPACE
namespace Ui { class test; }
QT_END_NAMESPACE

class test : public QWidget
{
    Q_OBJECT

public:
    test(QWidget *parent = nullptr);
    ~test();    

public slots:
    void showErrorMsg(QString s);

private slots:
    void on_addChildButton_clicked();
    void addChildBid(QString str);
    void addSubTree(Node *subtreeRoot);
    void onSaveBtnClicked();
    void onModifyBtnClicked();
    void onDelBtnClicked();
    void onBidBtnClicked();
    void onSeqBidBtnClicked();

    void on_LoadFile_clicked();

    void on_SaveFile_clicked();

    void on_root_clicked();

    void on_newFile_clicked();

    void on_addSubTree_clicked();

private:
    Ui::test *ui;
    QString chosenBid;
    QHBoxLayout *seqLayout;
    QVBoxLayout *saveLayout;
    Node *root;
    Node *currNode;
    std::vector <Node *> bidSeq;
    QMessageBox error_msg;
    std::string outFileName;
    bool changesSaved;
    void closeEvent(QCloseEvent *event) override;
    void clearLayout(QLayout *layout);
};
#endif // TEST_H
