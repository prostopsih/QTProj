#pragma once

#include "storage.h"
using namespace std;

class FileStorage : public Storage
{
protected:
  fstream students_file_;
  fstream courses_file_;
  virtual vector<tour_operator> loadTour_operators() = 0;
  virtual void saveTour_operators(vector<tour_operator> &obj) = 0;
  virtual int getNewTour_operatorId() = 0;

  virtual vector<ticket> loadTicket() = 0;
  virtual void saveTicket(vector<ticket> &tickets) = 0;
  virtual int getNewTicketId() = 0;

public:
  explicit FileStorage(const string &dir_name = "") :Storage(dir_name) {}
  virtual ~FileStorage() {}

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


  virtual optional<User> getUserAuth(string & username, string & password) {}
  virtual vector<tour_operator> getAllUserTour_operators(int user_id) {}


  virtual vector<tour> getAllTour_operatorTours(int tour_operator_id) {}
  virtual bool insertTour_operatorTour(int tour_operator_id, int tour_id) {}
  virtual bool removeTour_operatorTour(int tour_operator_id, int tour_id) {}
};
