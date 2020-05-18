#ifndef BIDGRID_H
#define BIDGRID_H

#include <QDialog>
#include <node.h>

namespace Ui {
class bidGrid;
}

class bidGrid : public QDialog
{
    Q_OBJECT

public:
    explicit bidGrid(std::vector <Node *> bidSeq,Node *currNode, QWidget *parent = nullptr);
    ~bidGrid();

signals:
    void sendBid(QString str);

private slots:
    void onClicked();

private:
    Ui::bidGrid *ui;

};

#endif // BIDGRID_H
