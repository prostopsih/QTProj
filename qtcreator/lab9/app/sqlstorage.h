#pragma once

#include <string>
#include <vector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QFileInfo>
#include <QDebug>
#include <QSqlError>
#include <QCryptographicHash>
#include "optional"
#include "storage.h"
#include "QByteArray"
#include "QBuffer"

using namespace std;

class SqliteStorage : public Storage
{
     protected:
       QSqlDatabase database_;

     public:
       SqliteStorage(const string & dir_name = "") : Storage(dir_name) {}
       virtual ~SqliteStorage() {}
       bool isOpen() const;
       bool open();
       void close();

       vector<tour_operator> getAllTour_operators(void);
       optional<tour_operator> getTour_operatorById(int tour_operator_id);
       bool updateTour_operator(const tour_operator &obj);
       bool removeTour_operator(int tour_operator_id);
       int insertTour_operator(const tour_operator &obj);

       // courses
       vector<tour> getAllTickets(void);
       optional<tour> getTicketById(int course_id);
       bool updateTicket(const tour &course);
       bool removeTicket(int ticket_id);
       int insertTicket(const tour &course);

       virtual optional<User> getUserAuth(string & username, string & password);
          virtual vector<tour_operator> getAllUserTour_operators(int user_id);


          virtual vector<tour> getAllTour_operatorTours(int tour_operator_id);
          virtual bool insertTour_operatorTour(int tour_operator_id, int tour_id);
          virtual bool removeTour_operatorTour(int tour_operator_id, int tour_id);
       virtual bool registerUser(string & username, string & password);
       virtual bool updateUser(User* user);
};


