#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(tour_operator t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    ui->country->setText(QString::fromStdString(t.name));
    ui->experience->setValue(t.experience);
}
tour_operator EditDialog::data()
{
    tour_operator t;
    t.name = ui->country->text().toStdString();
    t.experience = ui->experience->value();

    return t;
}
EditDialog::~EditDialog()
{
    delete ui;
}
