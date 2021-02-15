#include "toursmenu.h"
#include "ui_toursmenu.h"

toursMenu::toursMenu(QWidget *parent, Storage *f, tour_operator t) :
    QDialog(parent),storage(f),Tour_operator(t),
    ui(new Ui::toursMenu)
{
    ui->setupUi(this);
    clear();
    clear_2();
    disable_Edit();
    disable_Edit_2();
    enable_Add();
}

toursMenu::~toursMenu()
{
    delete ui;
}

void toursMenu::on_REMOVE_clicked()
{
        QList<QListWidgetItem* > items = ui->listWidget->selectedItems();
        if(items.count()!=0)
        {
                QMessageBox::StandardButton reply;
           reply = QMessageBox::question(
           this,
           "On delete",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {
              int index = ui->listWidget->row(item_);
              index += ((curr_page-1)*7);
              vector<tour> arr = storage->getAllTour_operatorTours(Tour_operator.id);
              Vec::findNeeded(arr, search);
              if(storage->removeTour_operatorTour(Tour_operator.id, arr[index].id))
              {
                  clear();
              }
           }
           else {
              qDebug() << "Yes was *not* clicked";
           }
        }
}
void toursMenu::clear()
{
    ui->place_of_arrival->setText("");
    ui->place_of_departure->setText("");
    ui->flight_length->setText("");
    ui->listWidget->clear();
    vector<tour> arr = storage->getAllTour_operatorTours(Tour_operator.id);
    Vec::findNeeded(arr,search);
    if(arr.size() != 0)
    {
        max_page = ceil(arr.size()/7.0);
        if(max_page < curr_page)
        {
            curr_page = max_page;
        }
        ui->prev->setEnabled(true);
        ui->next->setEnabled(true);
        ui->search->setEnabled(true);
        setPages();
    }
    else
    {
        ui->prev->setDisabled(true);
        ui->next->setDisabled(true);
        ui->search->setDisabled(true);
        ui->pageInfo->setText("empty");
    }
    for(int i = (curr_page-1)*7;i < arr.size() && i < curr_page * 7;i++)
    {
       ui->listWidget->addItem(QString::fromStdString(arr[i].place_of_departure + " - " + arr[i].place_of_arrival));
    }

    disable_Edit();
}
void toursMenu::clear_2()
{
    ui->place_of_arrival_2->setText("");
    ui->place_of_departure_2->setText("");
    ui->flight_length_2->setText("");
    ui->listWidget_2->clear();
    vector<tour> arr = storage->getAllTickets();
    Vec::findNeeded(arr,search_2);
    if(arr.size() != 0)
    {
        max_page_2 = ceil(arr.size()/7.0);
        if(max_page_2 < curr_page_2)
        {
            curr_page_2 = max_page_2;
        }
        ui->prev_2->setEnabled(true);
        ui->next_2->setEnabled(true);
        ui->search_2->setEnabled(true);
        setPages_2();
    }
    else
    {
        ui->prev_2->setDisabled(true);
        ui->next_2->setDisabled(true);
        ui->search_2->setDisabled(true);
        ui->pageInfo_2->setText("empty");
    }
    for(int i = (curr_page_2-1)*7;i < arr.size() && i < curr_page_2 * 7;i++)
    {
       ui->listWidget_2->addItem(QString::fromStdString(arr[i].place_of_departure + " - " + arr[i].place_of_arrival));
    }

    disable_Edit_2();
}
void toursMenu::setPages()
{
    QString s = QString::fromStdString(to_string(curr_page)) + " of " + QString::fromStdString(to_string(max_page));
    ui->pageInfo->setText(s);
}
void toursMenu::setPages_2()
{
    QString s = QString::fromStdString(to_string(curr_page_2)) + " of " + QString::fromStdString(to_string(max_page_2));
    ui->pageInfo_2->setText(s);
}

void toursMenu::on_prev_clicked()
{
    if(curr_page != 1)
    {
        curr_page--;
        clear();
    }
}

void toursMenu::on_next_clicked()
{
    if(curr_page != max_page)
    {
        curr_page++;
        clear();
    }
}

void toursMenu::on_ADD_clicked()
{
    tour temp;
    temp.flight_duration = 0;
    temp.place_of_arrival = "";
    temp.place_of_departure = "";
    addTour addDialog(temp, this);
    addDialog.exec();
    if(addDialog.statusTip() == "OK")
    {
        tour t = addDialog.data();
        storage->insertTicket(t);
        clear_2();
    }
}

void toursMenu::on_EDIT_clicked()
{
    QList<QListWidgetItem* > items = ui->listWidget->selectedItems();
    if(items.count() != 0)
    {
        int index = ui->listWidget->row(item_);
        index += ((curr_page-1)*7);
        auto arr = storage->getAllTour_operatorTours(Tour_operator.id);
        Vec::findNeeded(arr, search);
        tour temp = arr[index];
        addTour editDialog(temp,this);
        editDialog.exec();
        if(editDialog.statusTip() == "OK")
        {
            tour t = editDialog.data();
            t.id = temp.id;
            storage->updateTicket(t);
            clear();
            clear_2();
        }
    }
}

void toursMenu::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int index = ui->listWidget->row(item);
    index += ((curr_page-1)*7);
    vector<tour> arr = storage->getAllTour_operatorTours(Tour_operator.id);
    Vec::findNeeded(arr,search);
    ui->place_of_arrival->setText(QString::fromStdString(arr[index].place_of_arrival));
    ui->place_of_departure->setText(QString::fromStdString(arr[index].place_of_departure));
    ui->flight_length->setText(QString::fromStdString(to_string(arr[index].flight_duration)));
    item_=item;
    enable_Edit();
}

void toursMenu::on_search_textEdited(const QString &arg1)
{
    search = arg1;
    clear();
}
void toursMenu::disable()
{
    ui->search->setDisabled(true);
    ui->ADD->setDisabled(true);
    ui->EDIT->setDisabled(true);
    ui->REMOVE->setDisabled(true);
    ui->next->setDisabled(true);
    ui->prev->setDisabled(true);
    ui->next_2->setDisabled(true);
    ui->prev_2->setDisabled(true);
    ui->addlink->setDisabled(true);
}
void toursMenu::enable_Add()
{
    ui->search->setEnabled(true);
    ui->ADD->setEnabled(true);
    ui->next->setEnabled(true);
    ui->prev->setEnabled(true);
    ui->next_2->setEnabled(true);
    ui->prev_2->setEnabled(true);
}
void toursMenu::enable_Edit()
{
    ui->REMOVE->setEnabled(true);
    ui->EDIT->setEnabled(true);
}
void toursMenu::enable_Edit_2()
{
    ui->REMOVE_2->setEnabled(true);
    ui->EDIT_2->setEnabled(true);
    ui->addlink->setEnabled(true);
}
void toursMenu::disable_Edit()
{
    ui->REMOVE->setDisabled(true);
    ui->EDIT->setDisabled(true);
}
void toursMenu::disable_Edit_2()
{
    ui->REMOVE_2->setDisabled(true);
    ui->EDIT_2->setDisabled(true);
    ui->addlink->setDisabled(true);
}

void toursMenu::on_search_2_textEdited(const QString &arg1)
{
    search_2 = arg1;
    clear_2();
}

void toursMenu::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    int index = ui->listWidget_2->row(item);
    index += ((curr_page_2-1)*7);
    vector<tour> arr = storage->getAllTickets();
    Vec::findNeeded(arr,search_2);
    ui->place_of_arrival_2->setText(QString::fromStdString(arr[index].place_of_arrival));
    ui->place_of_departure_2->setText(QString::fromStdString(arr[index].place_of_departure));
    ui->flight_length_2->setText(QString::fromStdString(to_string(arr[index].flight_duration)));
    item_2=item;
    enable_Edit_2();
}

void toursMenu::on_prev_2_clicked()
{
    if(curr_page_2 != 1)
    {
        curr_page_2--;
        clear_2();
    }
}

void toursMenu::on_next_2_clicked()
{
    if(curr_page_2 != max_page_2)
    {
        curr_page_2++;
        clear_2();
    }
}

void toursMenu::on_addlink_clicked()
{
    int index = ui->listWidget_2->row(item_2);
    index += ((curr_page_2-1)*7);
    vector<tour> arr = storage->getAllTickets();
    Vec::findNeeded(arr, search_2);
    if(storage->insertTour_operatorTour(Tour_operator.id, arr[index].id))
    {
        clear();
    }
}

void toursMenu::on_EDIT_2_clicked()
{
    QList<QListWidgetItem* > items = ui->listWidget_2->selectedItems();
    if(items.count() != 0)
    {
        int index = ui->listWidget_2->row(item_2);
        index += ((curr_page_2-1)*7);
        auto arr = storage->getAllTickets();
        Vec::findNeeded(arr,search_2);
        tour temp = arr[index];
        addTour editDialog(temp,this);
        editDialog.exec();
        if(editDialog.statusTip() == "OK")
        {
            tour t = editDialog.data();
            t.id = temp.id;
            storage->updateTicket(t);
            clear_2();
            clear();
        }
    }
}

void toursMenu::on_REMOVE_2_clicked()
{
    QList<QListWidgetItem* > items = ui->listWidget_2->selectedItems();
    if(items.count()!=0)
    {
            QMessageBox::StandardButton reply;
       reply = QMessageBox::question(
       this,
       "On delete",
       "Are you sure?",
       QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {
          int index = ui->listWidget_2->row(item_2);
          index += ((curr_page_2 - 1)*7);
          vector<tour> arr = storage->getAllTickets();
          Vec::findNeeded(arr,search_2);
          storage->removeTicket(arr[index].id);
          storage->removeTour_operatorTour(Tour_operator.id, arr[index].id);
          clear_2();
          clear();
       }
       else {
          qDebug() << "Yes was *not* clicked";
       }
    }
}
