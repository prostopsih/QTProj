#include "changepassword.h"
#include "ui_changepassword.h"

changePassword::changePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassword)
{
    ui->setupUi(this);
}

changePassword::~changePassword()
{
    delete ui;
}
QString changePassword::Data()
{
    return ui->password->text();
}

void changePassword::on_pushButton_2_clicked()
{
    close();
}

void changePassword::on_pushButton_clicked()
{
    if(ui->password->text() == ui->password_2->text())
    {
        this->setStatusTip("OK");
        close();
    }
    else
    {
        qDebug() << "password can't be changed";
    }
}
