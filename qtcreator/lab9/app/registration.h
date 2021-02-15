#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "storage.h"
#include "QDebug"
namespace Ui {
class registration;
}

class registration : public QDialog
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent, Storage* f);
    ~registration();

private slots:

    void on_cancel_clicked();

    void on_register_2_clicked();

private:
    Storage* storage = nullptr;
    Ui::registration *ui;

};

#endif // REGISTRATION_H
