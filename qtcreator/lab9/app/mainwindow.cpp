#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), f(nullptr)
{
    ui->setupUi(this);
    //connect(ui->actionNew_Storage, &QAction::triggered,this,&MainWindow::NewStorage);
    connect(ui->actionOpen_Storage, &QAction::triggered,this,&MainWindow::OpenStorage);
    disable();
}
void MainWindow::disable()
{
    ui->search->setDisabled(true);
    ui->ADD->setDisabled(true);
    ui->EDIT->setDisabled(true);
    ui->REMOVE->setDisabled(true);
    ui->settings->setDisabled(true);
    ui->prev->setDisabled(true);
    ui->next->setDisabled(true);
}
void MainWindow::disableEdit_remove()
{
    ui->EDIT->setDisabled(true);
    ui->REMOVE->setDisabled(true);
}
void MainWindow::enableAdd_Settings()
{
    ui->search->setEnabled(true);
    ui->ADD->setEnabled(true);
    ui->settings->setEnabled(true);
    ui->prev->setEnabled(true);
    ui->next->setEnabled(true);
}
void MainWindow::enableEdit_remove()
{
    ui->EDIT->setEnabled(true);
    ui->REMOVE->setEnabled(true);
}
MainWindow::~MainWindow()
{
    delete ui;
    if(f!=nullptr)
    delete f;
    if(item_!=nullptr)
    {
        delete item_;
    }
    if(user!=nullptr)
    {
        delete user;

    }
}

void MainWindow::on_ADD_clicked()
{
    if(f!= nullptr && f->isOpen() && user != nullptr)
    {
        ADDDialog addDialog(this);
        int status = addDialog.exec();
        if(status == 1)
        {
            tour_operator t = addDialog.data();
            t.user_id = user->id;
            f->insertTour_operator(t);
            clear();
        }

    }
}
void MainWindow::OpenStorage()
{
    QString fileName = QFileDialog::getOpenFileName(
                   this,              // parent
                   "Dialog Caption",  // caption
                   "../../../data/sqlite",                // directory to start with
                   "SQLITE (*.sqlite);;All Files (*)");  // file name filter
       if (!QFileInfo::exists(fileName))
       {
          qDebug() << "Database does not exist:" << fileName;
          return ;
       }
       if(f == nullptr)
       {
           f = new SqliteStorage();
       }
       if(f->isOpen())
       {
           f->close();
       }
       f->setName(fileName.toStdString());
       f->open();
       check();
}
/*void MainWindow::NewStorage()
{
    if(f == nullptr)
    {
        f = new SqliteStorage();
    }
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString current_dir = QDir::currentPath();
    QString default_name = "new_storage";
    QString folder_path = dialog.getSaveFileName(
         this,
         "Select New Storage Folder",
         current_dir + "/" + default_name,
         "Folders");

  qDebug() << folder_path;
  if(f->isOpen())
  {
      f->close();
  }
  f->setName(folder_path.toStdString() + "/");
  qDebug() << QString::fromStdString(f->name());
  f->open();
  clear();
}*/



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
        int index = ui->listWidget->row(item);
        index += ((curr_page-1)*7);
        vector<tour_operator> arr = f->getAllTour_operators();
        Vec::findNeeded(arr, search);
        ui->country->setText(QString::fromStdString(arr[index].name));
        ui->cost->setText(QString::fromStdString(to_string(arr[index].experience)));
        item_=item;
        enableEdit_remove();
}

void MainWindow::on_EDIT_clicked()
{
    if(f!= nullptr && f->isOpen() && user != nullptr)
    {
        QList<QListWidgetItem* > items = ui->listWidget->selectedItems();
        if(items.count() != 0)
        {
            int index = ui->listWidget->row(item_);
            index += ((curr_page-1)*7);
            auto arr = f->getAllUserTour_operators(user->id);
            Vec::findNeeded(arr, search);
            tour_operator temp = arr[index];
            EditDialog editDialog(temp,this);
            int status = editDialog.exec();
            if(status == 1)
            {
                tour_operator t = editDialog.data();
                t.id = temp.id;
                t.user_id = user->id;
                f->updateTour_operator(t);
                clear();
            }
        }

    }
}

void MainWindow::on_REMOVE_clicked()
{
    if(f!= nullptr && f->isOpen() && user != nullptr)
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
              vector<tour_operator> arr = f->getAllUserTour_operators(user->id);
              Vec::findNeeded(arr, search);
              f->removeTour_operator(arr[index].id);
              clear();
           }
           else {
              qDebug() << "Yes was *not* clicked";
           }
        }
    }
}


void MainWindow::clear()
{

    ui->cost->setText("");
    ui->country->setText("");
    ui->listWidget->clear();
    vector<tour_operator> arr = f->getAllUserTour_operators(user->id);
    Vec::findNeeded(arr, search);
    if(arr.size() != 0)
    {
        max_page = ceil(arr.size()/7.0);
        if(max_page < curr_page)
        {
            curr_page = max_page;
        }
        ui->prev->setEnabled(true);
        ui->next->setEnabled(true);
        setPages();
    }
    else
    {
        ui->prev->setDisabled(true);
        ui->next->setDisabled(true);
        ui->pageInfo->setText("empty");
    }
    for(int i = (curr_page-1)*7;i < arr.size() && i < curr_page * 7;i++)
    {
       ui->listWidget->addItem(QString::fromStdString(arr[i].name));
    }
    disableEdit_remove();
}
void MainWindow::setPages()
{
    QString s = QString::fromStdString(to_string(curr_page)) + " of " + QString::fromStdString(to_string(max_page));
    ui->pageInfo->setText(s);
}
void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    vector<tour_operator> arr = f->getAllUserTour_operators(user->id);
    Vec::findNeeded(arr,search);
    int i = index.row();
    i += ((curr_page-1)*7);
    toursMenu tM(this, f,arr[i]);
    tM.exec();
}




void MainWindow::on_settings_clicked()
{
    if(f!= nullptr && f->isOpen() && user != nullptr)
    {
        settings sett(this, f, user);
        sett.exec();
        if(sett.statusTip() == "new user")
        {
            check();
        }
    }
}
void MainWindow::setNull()
{
    ui->listWidget->clear();
    ui->country->clear();
    ui->cost->clear();
    ui->pageInfo->clear();
}
void MainWindow::check()
{
    setNull();
    if(user != nullptr)
    {
        delete user;
        user = nullptr;
    }
    authentification auth(this,f);
    auth.exec();
    if(auth.statusTip() == "OK")
    {
        user = new User(auth.getUser());
        clear();
        enableAdd_Settings();
    }
    else
    {
        disable();
    }
}
void MainWindow::on_prev_clicked()
{
    if(curr_page != 1)
    {
        curr_page--;
        clear();
    }
}

void MainWindow::on_next_clicked()
{
    if(curr_page != max_page)
    {
        curr_page++;
        clear();
    }
}

void MainWindow::on_search_textEdited(const QString &arg1)
{
    search = arg1;
    clear();
}
