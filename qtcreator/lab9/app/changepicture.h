#ifndef CHANGEPICTURE_H
#define CHANGEPICTURE_H

#include <QDialog>

namespace Ui {
class ChangePicture;
}

class ChangePicture : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePicture(QWidget *parent = 0);
    ~ChangePicture();
    QString Data();
private slots:

    void on_OK_clicked();

    void on_cancel_clicked();

private:
    Ui::ChangePicture *ui;
};

#endif // CHANGEPICTURE_H
