#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QWidget>
#include "node.h"

namespace Ui {
class DataInput;
}

class DataInput : public QWidget
{
    Q_OBJECT

public:
    explicit DataInput(Node *currChild, QWidget *parent = nullptr);
    ~DataInput();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::DataInput *ui;
     Node *currChild;
};

#endif // DATAINPUT_H
