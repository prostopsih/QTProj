#ifndef ADDTOUR_H
#define ADDTOUR_H

#include <QDialog>
#include "tour.hpp"
#include "QDebug"
namespace Ui {
class addTour;
}

class addTour : public QDialog
{
    Q_OBJECT

public:
    explicit addTour(tour t, QWidget *parent = 0);
    ~addTour();
    tour data();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addTour *ui;
};

#endif // ADDTOUR_H
