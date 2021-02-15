#pragma once

#include <string>
#include <vector>
#include "fs.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <optional>
#include <tour_operator.hpp>
#include <functional>
#include <iostream>
#include <tour.hpp>
#include "optional"
#include "user.hpp"
#include "QString"

using namespace std;

class Storage
{
 protected:
   string dir_name_;

 public:
   explicit Storage(const string & dir_name = "") :dir_name_(dir_name) {}
   virtual ~Storage() {}

   void setName(const string & dir_name);
   string name() const;

   virtual bool isOpen() const = 0;
   virtual bool open() = 0;
   virtual void close() = 0;

   // students
   virtual vector<tour_operator> getAllTour_operators(void) = 0;
   virtual optional<tour_operator> getTour_operatorById(int tour_operator_id) = 0;
   virtual bool updateTour_operator(const tour_operator &obj) = 0;
   virtual bool removeTour_operator(int tour_operator_id) = 0;
   virtual int insertTour_operator(const tour_operator &obj) = 0;

   // courses
   virtual vector<tour> getAllTickets(void) = 0;
   virtual optional<tour> getTicketById(int course_id) = 0;
   virtual bool updateTicket(const tour &course) = 0;
   virtual bool removeTicket(int ticket_id) = 0;
   virtual int insertTicket(const tour &course) = 0;


   virtual optional<User> getUserAuth(string & username, string & password) = 0;
      virtual vector<tour_operator> getAllUserTour_operators(int user_id) = 0;


      virtual vector<tour> getAllTour_operatorTours(int tour_operator_id) = 0;
      virtual bool insertTour_operatorTour(int tour_operator_id, int tour_id) = 0;
      virtual bool removeTour_operatorTour(int tour_operator_id, int tour_id) = 0;
   virtual bool registerUser(string & username, string & password) = 0;
   virtual bool updateUser(User* user) = 0;
};

