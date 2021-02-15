#pragma once
#include "fs.hpp"
#include <csvlab.h>
#include <string>
#include <vector>
#include <fstream>
#include <optional>
#include <tour_operator.h>
#include <functional>
#include <iostream>
#include <ticket.h>

using namespace std;

class Storage
{

protected:
  string dir_name_;
  fstream students_file_;
  fstream courses_file_;
  virtual vector<tour_operator> loadTour_operators() = 0;
  virtual void saveTour_operators(vector<tour_operator> &obj) = 0;
  virtual int getNewTour_operatorId() = 0;

  virtual vector<ticket> loadTicket() = 0;
  virtual void saveTicket(vector<ticket> &tickets) = 0;
  virtual int getNewTicketId() = 0;

public:
  explicit FileStorage(const string &dir_name = "") :dir_name_(dir_name) {}
  virtual ~FileStorage() {}


  void setName(const string &dir_name);
  string name() const;

  bool isOpen() const;
  virtual bool open() = 0;
  void close();

  vector<tour_operator> getAllTour_operators(void);
  optional<tour_operator> getTour_operatorById(int tour_operator_id);
  bool updateTour_operator(const tour_operator &obj);
  bool removeTour_operator(int tour_operator_id);
  int insertTour_operator(const tour_operator &obj);


  vector<ticket> getAllTickets(void);
  optional<ticket> getTicketById(int course_id);
  bool updateTicket(const ticket &course);
  bool removeTicket(int ticket_id);
  int insertTicket(const ticket &course);
};
