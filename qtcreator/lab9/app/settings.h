#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "storage.h"
#include <QMessageBox>
#include "QCryptographicHash"
#include "changepassword.h"
#include "changepicture.h"
#include "QFileInfo"
namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent, Storage* f, User* u);
    ~settings();

private slots:
    void on_cancel_clicked();

    void on_logout_clicked();

    void on_save_clicked();

    void on_changePassword_clicked();

    void on_username_textEdited(const QString &arg1);

    void on_changepicture_clicked();

private:

    Storage* storage = nullptr;
    User* user = nullptr;
    Ui::settings *ui;
    bool check = false;
    User tempuser;
};

#endif // SETTINGS_H
