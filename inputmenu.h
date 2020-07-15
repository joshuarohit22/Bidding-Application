#ifndef LENGTHMENU_H
#define LENGTHMENU_H

#include <QDialog>
#include <node.h>

namespace Ui {
class LengthMenu;
}

class InputMenu : public QDialog
{
    Q_OBJECT

public:
    explicit InputMenu(Node *currChild, QWidget *parent = nullptr);
    ~InputMenu();

private slots:

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Node *currChild;
    Ui::LengthMenu *ui;
};

#endif // LENGTHMENU_H
