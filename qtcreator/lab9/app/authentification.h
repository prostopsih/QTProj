#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QDialog>
#include "registration.h"
#include "QDebug"
namespace Ui {
class authentification;
}

class authentification : public QDialog
{
    Q_OBJECT
    Storage * storage;
    User user;
public:
    explicit authentification(QWidget *parent, Storage* f);
    ~authentification();

private slots:

    void on_loginButton_clicked();
    void on_createButton_clicked();

public:
    User getUser();
private:
    Ui::authentification *ui;
};

#endif // AUTHENTIFICATION_H
