#include "sqlstorage.h"

bool SqliteStorage::isOpen() const
{
    return database_.isOpen();
}
bool SqliteStorage::open()
{
    QString path = QString::fromStdString(dir_name_);
    if (!QFileInfo::exists(path))
    {
       qDebug() << "Database does not exist:" << path;
       return false;
    }
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    database_.setDatabaseName(path);    // set sqlite database file path
    bool connected = database_.open();  // open db connection
    if (!connected) {
       qDebug() << "open database error:"
                << database_.lastError();
       return false;
    }
    return true;
}
void SqliteStorage::close()
{
    if(database_.isOpen())
    database_.close();
}

tour_operator getTourOperatorFromQuery(QSqlQuery &query)
{
    int name = query.record().indexOf("name");
    int experience = query.record().indexOf("experience");
    int user_id = query.record().indexOf("user_id");
    tour_operator t;
   t.name = query.value(name).toString().toStdString();
   t.experience = query.value(experience).toInt();
   t.user_id = query.value(user_id).toInt();
   t.id = query.value("id").toInt();
   return t;
}
vector<tour_operator> SqliteStorage::getAllTour_operators(void)
{
    vector<tour_operator> arr;
    QSqlQuery query("SELECT * FROM tour_operators");
    while (query.next())
    {
        tour_operator t = getTourOperatorFromQuery(query);
       arr.push_back(t);
    }
    return arr;
}
optional<tour_operator> SqliteStorage::getTour_operatorById(int tour_operator_id)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM tour_operators WHERE id = :id"))
    {
       qDebug() << "get person query prepare error:" << query.lastError();
       return nullopt;
    }
    query.bindValue(":id", tour_operator_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get person query exec error:" << query.lastError();
       return nullopt;
    }


    if (query.next()) {
       tour_operator t = getTourOperatorFromQuery(query);
       return t;
    } else {
       qDebug() << " not found ";
       return nullopt;
    }
}
bool SqliteStorage::updateTour_operator(const tour_operator &obj)
{
    QSqlQuery query;
    if (!query.prepare("UPDATE tour_operators SET name = :name, experience = :experience, user_id = :user_id WHERE id = :id")){
        qDebug() << "updatePerson query prepare error:" << query.lastError();
        // return or throw or do smth else
    }
    query.bindValue(":name", QString::fromStdString(obj.name));
    query.bindValue(":experience", obj.experience);
    query.bindValue(":user_id", obj.user_id);
    query.bindValue(":id", obj.id);
    if (!query.exec()){
        qDebug() << "updatePerson query exec error:" << query.lastError();
        return false;
    }
    return true;
}
bool SqliteStorage::removeTour_operator(int tour_operator_id)
{
    QSqlQuery query;
    if (!query.prepare("DELETE FROM tour_operators WHERE id = :id")){
        qDebug() << "deletePerson query prepare error:" << query.lastError();
        return false;
    }
    query.bindValue(":id", tour_operator_id);
    if (!query.exec()){
        qDebug() << "deletePerson query exec error:" << query.lastError();
        return false;
    }

    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}
int SqliteStorage::insertTour_operator(const tour_operator &obj)
{
    QSqlQuery query;
    if (!query.prepare("INSERT INTO tour_operators (name, experience, user_id) VALUES (:name, :experience, :user_id)"))
    {
       qDebug() << "addPerson query prepare error:"
                << query.lastError();
       return 0;
    }
    query.bindValue(":experience", obj.experience);
    query.bindValue(":name", QString::fromStdString(obj.name));
    query.bindValue(":user_id", obj.user_id);
    if (!query.exec())
    {
       qDebug() << "addPerson query exec error:"
                << query.lastError();
       return 0;
    }
    QVariant id = query.lastInsertId();
       return id.toInt();

}

// courses
optional<string> getCityFromId(int city_id)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM cities WHERE id = :id"))
    {
       qDebug() << "get person query prepare error:" << query.lastError();
       return nullopt;
    }
    query.bindValue(":id", city_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get person query exec error:" << query.lastError();
       return nullopt;
    }


    if (query.next()) {
       string city = query.value("CityName").toString().toStdString();
       return city;
    } else {
       qDebug() << " not found ";
       return nullopt;
    }
}
int getCityIdFromName(string name)
{
    QSqlQuery query;
    if(!query.prepare("Select * FROM cities where CityName = :name"))
    {
        qDebug() << "get person query prepare error:" << query.lastError();
        return -1;
    }
    query.bindValue(":name",QString::fromStdString(name));
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get person query exec error:" << query.lastError();
       return -1;
    }


    if (query.next()) {
       return query.value("id").toInt();
    } else {
        QSqlQuery query1;
        if (!query1.prepare("INSERT INTO cities (CityName) VALUES (:CityName)"))
        {
           qDebug() << "addPerson query prepare error:"
                    << query1.lastError();
           return -1;
        }
        query1.bindValue(":CityName", QString::fromStdString(name));
        if (!query1.exec())
        {
           qDebug() << "addPerson query exec error:"
                    << query1.lastError();
           return -1;
        }
        QVariant id = query1.lastInsertId();
           return id.toInt();
    }
}
tour getTicketFromQuery(QSqlQuery &query)
{
    int place_of_departure = query.record().indexOf("place_of_departure_id");
    int place_of_arrival = query.record().indexOf("place_of_arrival_id");
    int flight_duration = query.record().indexOf("flight_duration");
    tour t;
   t.place_of_departure = getCityFromId(query.value(place_of_departure).toInt()).value();
   t.place_of_arrival = getCityFromId(query.value(place_of_arrival).toInt()).value();
   t.flight_duration = query.value(flight_duration).toInt();
   t.id = query.value("id").toInt();
   return t;
}
vector<tour> SqliteStorage::getAllTickets(void)
{
    vector<tour> arr;
    QSqlQuery query("SELECT * FROM tours");

    while (query.next())
    {
        tour t = getTicketFromQuery(query);
       arr.push_back(t);
    }
    return arr;
}
optional<tour> SqliteStorage::getTicketById(int course_id)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM tours WHERE id = :id"))
    {
       qDebug() << "get person query prepare error:" << query.lastError();
       return nullopt;
    }
    query.bindValue(":id", course_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
       qDebug() << "get person query exec error:" << query.lastError();
       return nullopt;
    }


    if (query.next()) {
       tour t = getTicketFromQuery(query);
       return t;
    } else {
       qDebug() << " not found ";
       return nullopt;
    }
}
bool SqliteStorage::updateTicket(const tour &course)
{
    QSqlQuery query;
    if (!query.prepare("UPDATE tours SET place_of_departure_id = :place_of_departure, place_of_arrival_id = :place_of_arrival, flight_duration = :flight_duration WHERE id = :id")){
        qDebug() << "updatePerson query prepare error:" << query.lastError();
        // return or throw or do smth else
    }
    query.bindValue(":place_of_departure", getCityIdFromName(course.place_of_departure));
    query.bindValue(":flight_duration", course.flight_duration);
    query.bindValue(":place_of_arrival", getCityIdFromName(course.place_of_arrival));
    query.bindValue(":id", course.id);
    if (!query.exec()){
        qDebug() << "updatePerson query exec error:" << query.lastError();
        return false;
    }
    return true;
}
bool SqliteStorage::removeTicket(int ticket_id)
{
    QSqlQuery query;
    if (!query.prepare("DELETE FROM tours WHERE id = :id")){
        qDebug() << "deletePerson query prepare error:" << query.lastError();
        return false;
    }
    query.bindValue(":id", ticket_id);
    if (!query.exec()){
        qDebug() << "deletePerson query exec error:" << query.lastError();
        return false;
    }

    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}
int SqliteStorage::insertTicket(const tour &course)
{
    QSqlQuery query;
    if (!query.prepare("INSERT INTO tours (place_of_departure_id, place_of_arrival_id, flight_duration) VALUES (:place_of_departure, :place_of_arrival, :flight_duration)"))
    {
       qDebug() << "addPerson query prepare error:"
                << query.lastError();
       return 0;
    }
    query.bindValue(":flight_duration", course.flight_duration);
    query.bindValue(":place_of_arrival", getCityIdFromName(course.place_of_arrival));
    query.bindValue(":place_of_departure", getCityIdFromName(course.place_of_departure));
    if (!query.exec())
    {
       qDebug() << "addPerson query exec error:"
                << query.lastError();
       return 0;
    }
    QVariant id = query.lastInsertId();
       return id.toInt();
}

QString hashPassword(QString const & pass) {
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}



optional<User> SqliteStorage::getUserAuth(string & username, string & password)
{
    QSqlQuery query;
    if(!query.prepare("select * from users where username = :username"))
    {
        qDebug() << "addPerson query prepare error:"
                 << query.lastError();
        return nullopt;
    }
    query.bindValue(":username", QString::fromStdString(username));


    if (!query.exec()){
        qDebug() << "deletePerson query exec error:" << query.lastError();
        return nullopt;
    }
    if(!query.next())
    {
        return nullopt;
    }
    User user;
    user.id = query.value("id").toInt();
    user.password_hash = query.value("password").toString().toStdString();
    user.username = username;
    //
    QByteArray ba = query.value("picture").toByteArray();
    QImage qi = QImage::fromData(ba);
    user.picture = QPixmap::fromImage(qi);
    //
    if(hashPassword(QString::fromStdString(password)).toStdString() != user.password_hash)
    {
        qDebug() << "wrong password" << endl;
        return nullopt;
    }
    return user;
}
vector<tour_operator> SqliteStorage::getAllUserTour_operators(int user_id)
{
    vector<tour_operator> arr;
    QSqlQuery query;
    if(!query.prepare("SELECT * FROM tour_operators where user_id = :user_id"))
    {
        qDebug() << "Prepare ERROR";
    }
    query.bindValue(":user_id", user_id);
    if(!query.exec())
    {
        qDebug() << "EXEC error";
    }
    while (query.next())
    {
        tour_operator t = getTourOperatorFromQuery(query);
        arr.push_back(t);
    }
    return arr;
}


vector<tour> SqliteStorage::getAllTour_operatorTours(int tour_operator_id)
{
    vector<tour> arr;
    QSqlQuery query;
    query.prepare("select * from links where tour_operator_id = :tour_operator_id");
    query.bindValue(":tour_operator_id", tour_operator_id);
    query.exec();
    while(query.next())
    {
        int id = query.value("tour_id").toInt();
        tour t = getTicketById(id).value();
        arr.push_back(t);
    }
    return arr;
}
bool SqliteStorage::insertTour_operatorTour(int tour_operator_id, int tour_id)
{
    bool check = true;
    QSqlQuery q;
    q.prepare("select * from links");
    q.exec();
    while(q.next())
    {
        if(q.value("tour_id").toInt() == tour_id && q.value("tour_operator_id").toInt() == tour_operator_id)
        {
            check = false;
        }
    }
    if(check)
    {
        QSqlQuery query;
        if(!query.prepare("INSERT INTO links (tour_operator_id, tour_id) VALUES (:tour_operator_id, :tour_id)"))
        {
            qDebug() << "Prepare ERROR" << query.lastError().text();
            return false;
        }
        query.bindValue(":tour_operator_id", tour_operator_id);
        query.bindValue(":tour_id", tour_id);
        if(!query.exec())
        {
             qDebug() << "Exec ERROR " << query.lastError().text();
            return false;
        }
        return true;
    }
}
bool SqliteStorage::removeTour_operatorTour(int tour_operator_id, int tour_id)
{
    QSqlQuery query;
    query.prepare("DELETE from links where tour_operator_id = :tour_operator_id and tour_id = :tour_id");
    query.bindValue(":tour_operator_id",tour_operator_id);
    query.bindValue(":tour_id",tour_id);
    if(!query.exec())
    {
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}
bool SqliteStorage::registerUser(string & username, string & password)
{
    QSqlQuery query;
    if (!query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)"))
    {
       qDebug() << "addPerson query prepare error:"
                << query.lastError();
       return false;
    }
    query.bindValue(":password", hashPassword(QString::fromStdString(password)));
    query.bindValue(":username", QString::fromStdString(username));
    if (!query.exec())
    {
       qDebug() << "addPerson query exec error:"
                << query.lastError();
       return false;
    }
    return true;
}
bool SqliteStorage::updateUser(User* user)
{
    QSqlQuery query;
    if (!query.prepare("UPDATE users SET username = :username, password = :password, picture = :picture WHERE id = :id")){
        qDebug() << "updatePerson query prepare error:" << query.lastError();
        return false;
    }
    query.bindValue(":username", QString::fromStdString(user->username));
    query.bindValue(":password", QString::fromStdString(user->password_hash));
    //
    QPixmap pixmap = user->picture;
    // Preparation of our QPixmap
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
    query.bindValue(":picture",bArray);
    //
    query.bindValue(":id", user->id);
    if (!query.exec()){
        qDebug() << "updatePerson query exec error:" << query.lastError();
        return false;
    }
    return true;
}


