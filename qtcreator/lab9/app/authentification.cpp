#include "authentification.h"
#include "ui_authentification.h"

authentification::authentification(QWidget *parent, Storage* f) :
    QDialog(parent), storage(f),
    ui(new Ui::authentification)
{
    ui->setupUi(this);
}

authentification::~authentification()
{
    delete ui;
}



void authentification::on_loginButton_clicked()
{
    string name = ui->username->text().toStdString();
    string pass = ui->password->text().toStdString();
    optional<User> user = storage->getUserAuth(name , pass);
    if(user.has_value())
    {
        qDebug() << "LOGIN" << endl;
        this->user = user.value();
        this->setStatusTip("OK");
        close();
    }
    else
    {
        ui->info->setText("wrong information");
    }
}
User authentification::getUser()
{
     return user;
}

void authentification::on_createButton_clicked()
{
    registration reg(this, storage);
    reg.exec();
    ui->info->setText("");
}
