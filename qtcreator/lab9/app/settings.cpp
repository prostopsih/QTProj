#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent, Storage* f,User* u) :
    QDialog(parent), storage(f), user(u),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->username->setText(QString::fromStdString(user->username));
    tempuser.id = user->id;
    tempuser.password_hash = user->password_hash;
    tempuser.username = user->username;
    tempuser.picture = user->picture;
    if(!user->picture.isNull())
    {
        ui->picture->setPixmap(tempuser.picture);
    }
}

settings::~settings()
{
    delete ui;
}

void settings::on_cancel_clicked()
{
    close();
}

void settings::on_logout_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
    this,
    "Logout",
    "Are you sure?",
    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->setStatusTip("new user");
        close();
    }
}


void settings::on_save_clicked()
{
    if(check)
    {
        ui->picture->setPixmap(tempuser.picture);
        check = false;
    }
    if(storage->updateUser(&tempuser))
    {
        user->id = tempuser.id;
        user->password_hash = tempuser.password_hash;
        user->username = tempuser.username;
        user->picture = tempuser.picture;
    }
}
QString hashP(QString const & pass) {
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}
void settings::on_changePassword_clicked()
{
    changePassword c(this);
    c.exec();
    if(c.statusTip() == "OK")
    {
        tempuser.password_hash = hashP(c.Data()).toStdString();
    }

}

void settings::on_username_textEdited(const QString &arg1)
{
    tempuser.username = arg1.toStdString();
}

void settings::on_changepicture_clicked()
{
    ChangePicture cp(this);
    cp.exec();
    if(cp.statusTip() == "OK" && QFileInfo::exists(cp.Data()))
    {
        tempuser.picture.load(cp.Data());
        check = true;
    }
    else
    {
        check = false;
    }
}
