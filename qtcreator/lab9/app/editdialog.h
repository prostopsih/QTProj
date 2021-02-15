#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include "tour_operator.hpp"
namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(tour_operator t, QWidget *parent = 0);
    ~EditDialog();

    tour_operator data();

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
