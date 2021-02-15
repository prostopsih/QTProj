#include "registration.h"
#include "ui_registration.h"

registration::registration(QWidget *parent, Storage* f) :
    QDialog(parent),storage(f),
    ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}



void registration::on_cancel_clicked()
{
    close();
}

void registration::on_register_2_clicked()
{
    if(ui->password->text() == ui->password_2->text())
    {
       string name = ui->username->text().toStdString();
       string pass = ui->password->text().toStdString();
       if(storage->registerUser(name,pass))
       {
           close();
       }
       else
       {
           ui->info->setText("The username is not free");
       }
    }
    else
    {
        ui->username->setText("");
        ui->password->setText("");
        ui->password_2->setText("");
        ui->info->setText("Try again");
    }
}
