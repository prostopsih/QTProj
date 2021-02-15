#include "xmlstorage.h"
#include "QDebug"
#include "QtXml/QtXml"
#include "QString"
#include "string"
vector<tour_operator> XmlStorage::loadTour_operators()
{
    students_file_.close();
    students_file_.open(dir_name_ + "xml/tour_operators.xml",ios_base::in);
    string strx = "";
    string temp;
    while(getline(students_file_,temp))
    {
        strx += temp;
    }
    QString str(strx.c_str());
    vector<tour_operator> vec;

    QDomDocument doc;
       QString errorMessage;
       if (!doc.setContent(str, &errorMessage)) {
           qDebug() << "error parsing xml Tour_operator: " << errorMessage;
           exit(1);
       }
       QDomElement rootEl = doc.documentElement();
       QDomNodeList rootElChildren = rootEl.childNodes();
       for (int i = 0; i < rootElChildren.length(); i++) {
             QDomNode studentNode = rootElChildren.at(i);
             QDomElement studentEl = studentNode.toElement();
             tour_operator to = xmlElementToTour_operator(studentEl);
             vec.push_back(to);
       }

    return vec;
}
void XmlStorage::saveTour_operators(vector<tour_operator> &obj)
{
    QDomDocument doc;

       QDomElement rootEl = doc.createElement("tour_operators");
       for (const tour_operator & student: obj) {
             QDomElement studentEl = tour_operatorToXmlElement(doc, student);
             rootEl.appendChild(studentEl);
       }
       doc.appendChild(rootEl);

       QString qStr = doc.toString(-1);
       students_file_.close();
       ofstream fout;
       fout.open(dir_name_ + "xml/tour_operators.xml");
       fout.close();
       students_file_.open(dir_name_ + "xml/tour_operators.xml");
       students_file_ << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
       students_file_ << qStr.toStdString();
       students_file_.flush();
}
int XmlStorage::getNewTour_operatorId()
{
    vector<tour_operator> arr = loadTour_operators();
    return arr[arr.size() - 1].id + 1;
}
vector<ticket> XmlStorage::loadTicket()
{
    courses_file_.close();
    courses_file_.open(dir_name_ + "xml/ticket.xml",ios_base::in);
    string strx = "";
    string temp;
    while(getline(courses_file_,temp))
    {
        strx += temp;
    }
    QString str(strx.c_str());
    vector<ticket> vec;

    QDomDocument doc;
       QString errorMessage;
       if (!doc.setContent(str, &errorMessage)) {
           qDebug() << "error parsing xml: " << errorMessage;
           exit(1);
       }
       QDomElement rootEl = doc.documentElement();
       QDomNodeList rootElChildren = rootEl.childNodes();
       for (int i = 0; i < rootElChildren.length(); i++) {
             QDomNode studentNode = rootElChildren.at(i);
             QDomElement studentEl = studentNode.toElement();
             ticket to = xmlElementToTicket(studentEl);
             vec.push_back(to);
       }
    return vec;
}
void XmlStorage::saveTicket(vector<ticket> &tickets)
{
    QDomDocument doc;

       QDomElement rootEl = doc.createElement("tickets");
       for (const ticket & student: tickets) {
             QDomElement studentEl = ticketToXmlElement(doc, student);
             rootEl.appendChild(studentEl);
       }
       doc.appendChild(rootEl);

       QString qStr = doc.toString(-1);
       courses_file_.close();
       ofstream fout;
       fout.open(dir_name_ + "xml/ticket.xml");
       fout.close();
       courses_file_.open(dir_name_ + "xml/ticket.xml");
       courses_file_ << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
       courses_file_ << qStr.toStdString();
       students_file_.flush();
}
int XmlStorage::getNewTicketId()
{
    vector<ticket> arr = loadTicket();
    return arr[arr.size() - 1].id + 1;
}
bool XmlStorage::open()
{
    students_file_.open(dir_name_ + "xml/tour_operators.xml");
    courses_file_.open(dir_name_ + "xml/ticket.xml");
    return (students_file_.is_open() && courses_file_.is_open());
}
