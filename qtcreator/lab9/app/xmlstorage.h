#pragma once
#include "filestorage.hpp"
#include "xml.h"
class XmlStorage: public FileStorage
{
private:
    virtual vector<tour_operator> loadTour_operators();
    virtual void saveTour_operators(vector<tour_operator> &obj);
    virtual int getNewTour_operatorId();

    virtual vector<ticket> loadTicket();
    virtual void saveTicket(vector<ticket> &tickets);
    virtual int getNewTicketId();
public:
    virtual bool open();
    explicit XmlStorage(const string & dir_name = ""): FileStorage(dir_name) {}
};
