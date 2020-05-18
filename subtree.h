#ifndef SUBTREE_H
#define SUBTREE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <node.h>

namespace Ui {
class subtree;
}

class subtree : public QWidget
{
    Q_OBJECT

public:
    explicit subtree(Node *root, std::vector <Node *> bidSeq, QWidget *parent = nullptr);
    ~subtree();

signals:
    void sendNode(Node *subtreeRoot);

private slots:

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_rootBtn_clicked();

    void onBidBtnClicked();

    void onSeqBidBtnClicked();

private:
    Ui::subtree *ui;
    QHBoxLayout *seqLayout;
    QVBoxLayout *childrenLayout;
    Node *currNode;
    Node *root;
    std::vector <Node *> sequence;
    std::vector <Node *> bidSeq;

    void clearLayout(QLayout *layout);


};

#endif // SUBTREE_H
