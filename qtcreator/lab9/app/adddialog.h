#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "tour_operator.hpp"
namespace Ui {
class ADDDialog;
}

class ADDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ADDDialog(QWidget *parent = 0);
    ~ADDDialog();

    tour_operator data();

private:
    Ui::ADDDialog *ui;
};

#endif // ADDDIALOG_H
