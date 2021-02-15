#include "changepicture.h"
#include "ui_changepicture.h"

ChangePicture::ChangePicture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePicture)
{
    ui->setupUi(this);
}

ChangePicture::~ChangePicture()
{
    delete ui;
}
QString ChangePicture::Data()
{
    return ui->pictureway->text();
}


void ChangePicture::on_OK_clicked()
{
    this->setStatusTip("OK");
    close();
}

void ChangePicture::on_cancel_clicked()
{
    close();
}
