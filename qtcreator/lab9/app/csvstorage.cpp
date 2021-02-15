#include "csvstorage.hpp"

vector<tour_operator> CsvStorage::loadTour_operators()
{
    students_file_.close();
    students_file_.open(dir_name_ + "csv/tour_operators.csv");
    vector<string> arr = readCSV(students_file_);
    vector<tour_operator> vec = EntityFromString(arr);
    return vec;
}
void CsvStorage::saveTour_operators(vector<tour_operator> & obj)
{
    vector<string> arr = StringFromEntity(obj);
    students_file_.close();
    ofstream fout;
    fout.open(dir_name_ + "csv/tour_operators.csv");
    fout.close();
    students_file_.open(dir_name_ + "csv/tour_operators.csv");
    write(students_file_,arr);
}
int CsvStorage::getNewTour_operatorId()
{
    vector<tour_operator> arr = loadTour_operators();
    return arr[arr.size() - 1].id + 1;
}



vector<ticket> CsvStorage::loadTicket()
{
    courses_file_.close();
    courses_file_.open(dir_name_ + "csv/ticket.csv");
    vector<string> arr = readCSV(courses_file_);
    vector<ticket> vec = TicketsFromString(arr);
    return vec;
}
void CsvStorage::saveTicket(vector<ticket> &tickets)
{
    vector<string> arr = StringFromTickets(tickets);
    courses_file_.close();
    ofstream fout;
    fout.open(dir_name_ + "csv/ticket.csv");
    fout.close();
    courses_file_.open(dir_name_ + "csv/ticket.csv");
    write(courses_file_,arr);
}
int CsvStorage::getNewTicketId()
{
    vector<ticket> arr = loadTicket();
    return arr[arr.size() - 1].id + 1;
}
bool CsvStorage::open()
{
    students_file_.open(dir_name_ + "csv/tour_operators.csv");
    courses_file_.open(dir_name_ + "csv/ticket.csv");
    return (students_file_.is_open() && courses_file_.is_open());
}
