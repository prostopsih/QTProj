#include "addtour.h"
#include "ui_addtour.h"

addTour::addTour(tour t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTour)
{
    ui->setupUi(this);
    ui->flight_duration->setValue(t.flight_duration);
    ui->place_of_arrival->setText(QString::fromStdString(t.place_of_arrival));
    ui->place_of_departure->setText(QString::fromStdString(t.place_of_departure));
}

addTour::~addTour()
{
    delete ui;
}

tour addTour::data()
{
    tour t;
    t.place_of_arrival = ui->place_of_arrival->text().toStdString();
    t.place_of_departure = ui->place_of_departure->text().toStdString();
    t.flight_duration = ui->flight_duration->value();
    return t;
}

void addTour::on_buttonBox_accepted()
{
    this->setStatusTip("OK");
    close();
}

void addTour::on_buttonBox_rejected()
{
    close();
}
