#include "adddialog.h"
#include "ui_adddialog.h"

ADDDialog::ADDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADDDialog)
{
    ui->setupUi(this);
}

ADDDialog::~ADDDialog()
{
    delete ui;
}

tour_operator ADDDialog::data()
{
    tour_operator t;
    t.name = ui->country->text().toStdString();
    t.experience = ui->experience->value();
    return t;
}
