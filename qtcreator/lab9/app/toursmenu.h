#ifndef TOURSMENU_H
#define TOURSMENU_H

#include <QDialog>
#include "storage.h"
#include "QMessageBox"
#include "tour_operator.hpp"
#include "tour.hpp"
#include "QListWidgetItem"
#include "QDebug"
#include "cmath"
#include "addtour.h"
#include "vec.h"
namespace Ui {
class toursMenu;
}

class toursMenu : public QDialog
{
    Q_OBJECT

public:
    explicit toursMenu(QWidget *parent, Storage* f, tour_operator t);
    ~toursMenu();

private slots:
    void on_REMOVE_clicked();

    void on_prev_clicked();

    void on_next_clicked();

    void on_ADD_clicked();

    void on_EDIT_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_search_textEdited(const QString &arg1);

    void on_search_2_textEdited(const QString &arg1);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_prev_2_clicked();

    void on_next_2_clicked();

    void on_addlink_clicked();

    void on_EDIT_2_clicked();

    void on_REMOVE_2_clicked();

private:
    Ui::toursMenu *ui;
    Storage* storage;
    tour_operator Tour_operator;
    QListWidgetItem* item_ = nullptr;
    int curr_page = 1;
    int max_page = 1;
    QString search = "";
    QListWidgetItem* item_2 = nullptr;
    int curr_page_2 = 1;
    int max_page_2 = 1;
    QString search_2 = "";
    void clear();
    void clear_2();
    void setPages();
    void setPages_2();
    void disable();
    void enable_Add();
    void enable_Edit();
    void enable_Edit_2();
    void disable_Edit();
    void disable_Edit_2();
};

#endif // TOURSMENU_H
