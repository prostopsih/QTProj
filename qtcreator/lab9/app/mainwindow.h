#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidgetItem>
#include "adddialog.h"
#include "editdialog.h"
#include "sqlstorage.h"
#include "user.hpp"
#include "authentification.h"
#include "settings.h"
#include "QListWidgetItem"
#include "cmath"
#include "toursmenu.h"
#include <string>
#include "vec.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ADD_clicked();
    void OpenStorage();
    //void NewStorage();



    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_EDIT_clicked();

    void on_REMOVE_clicked();
    void clear();

    void on_listWidget_doubleClicked(const QModelIndex &index);


    void on_settings_clicked();

    void on_prev_clicked();

    void on_next_clicked();

    void on_search_textEdited(const QString &arg1);

private:

    void setPages();
    void check();
    void setNull();
    void disable();
    void disableEdit_remove();
    void enableAdd_Settings();
    void enableEdit_remove();
    Ui::MainWindow *ui;
    Storage* f = nullptr;
    QListWidgetItem* item_ = nullptr;
    User* user = nullptr;
    int curr_page = 1;
    int max_page = 1;
    QString search;
};

#endif // MAINWINDOW_H
