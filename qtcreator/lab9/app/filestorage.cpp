#include "filestorage.hpp"




bool FileStorage::isOpen() const
{
    return students_file_.is_open();
}

void FileStorage::close()
{
    students_file_.close();
}
vector<tour_operator> FileStorage::getAllTour_operators(void)
{
    return loadTour_operators();
}
optional<tour_operator> FileStorage::getTour_operatorById(int tour_operator_id)
{
    vector<tour_operator> arr = loadTour_operators();
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].id == tour_operator_id)
        {
            return arr[i];
            break;
        }
    }
    optional<tour_operator> op;
    op.reset();
    return op;
}
bool FileStorage::updateTour_operator(const tour_operator &obj)
{
    vector<tour_operator> arr = loadTour_operators();
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].id == obj.id)
        {
            arr[i] = obj;
            saveTour_operators(arr);
            return true;
        }
    }
    return false;
}
bool FileStorage::removeTour_operator(int tour_operator_id)
{
    vector<tour_operator> arr = loadTour_operators();
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].id == tour_operator_id)
        {
            arr.erase(arr.begin() + i);
            saveTour_operators(arr);
            return true;
        }
    }
    return false;
}
int FileStorage::insertTour_operator(const tour_operator &obj)
{
    int id = getNewTour_operatorId();
    tour_operator temp = obj;
    temp.id = id;
    vector<tour_operator> arr = loadTour_operators();
    arr.push_back(temp);
    saveTour_operators(arr);
    return id;
}


vector<ticket> FileStorage::getAllTickets(void)
{
    return loadTicket();
}
optional<ticket> FileStorage::getTicketById(int course_id)
{
    vector<ticket> arr = loadTicket();
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].id == course_id)
        {
            return arr[i];
            break;
        }
    }
    optional<ticket> op;
    op.reset();
    return op;
}
bool FileStorage::updateTicket(const ticket &course)
{
    vector<ticket> arr = loadTicket();
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].id == course.id)
        {
            arr[i] = course;
            saveTicket(arr);
            return true;
        }
    }
    return false;
}
bool FileStorage::removeTicket(int ticket_id)
{
    vector<ticket> arr = loadTicket();
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].id == ticket_id)
        {
            arr.erase(arr.begin() + i);
            saveTicket(arr);
            return true;
        }
    }
    return false;
}
int FileStorage::insertTicket(const ticket &course)
{
    int id = getNewTicketId();
    ticket temp = course;
    temp.id = id;
    vector<ticket> arr = loadTicket();
    arr.push_back(temp);
    saveTicket(arr);
    return id;
}
