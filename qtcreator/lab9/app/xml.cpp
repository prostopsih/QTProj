#include "xml.h"

QDomElement tour_operatorToXmlElement(QDomDocument & doc, const tour_operator & t)
{
   QDomElement tour_operatorEl = doc.createElement("tour_operator");
   tour_operatorEl.setAttribute("id", t.id);
   tour_operatorEl.setAttribute("country", QString::fromStdString(t.country));
   tour_operatorEl.setAttribute("cost", t.cost);
   tour_operatorEl.setAttribute("length", QString::fromStdString(t.length));
   return tour_operatorEl;
}
QDomElement ticketToXmlElement(QDomDocument & doc, const ticket & t)
{
    QDomElement ticketEl = doc.createElement("ticket");
    ticketEl.setAttribute("id",t.id);
    ticketEl.setAttribute("place_of_departure",QString::fromStdString(t.place_of_departure));
    ticketEl.setAttribute("place_of_arrival",QString::fromStdString(t.place_of_arrival));
    ticketEl.setAttribute("flight_duration",t.flight_duration);
    return ticketEl;
}
tour_operator xmlElementToTour_operator(QDomElement &t)
{
    tour_operator to;
    to.id = t.attribute("id").toInt();
    to.country = t.attribute("country").toStdString();
    to.cost = t.attribute("cost").toDouble();
    to.length = t.attribute("length").toStdString();
    return to;
}
ticket xmlElementToTicket(QDomElement &t)
{
    ticket to;
    to.id = t.attribute("id").toInt();
    to.place_of_arrival = t.attribute("place_of_arrival").toStdString();
    to.place_of_departure = t.attribute("place_of_departure").toStdString();
    to.flight_duration = t.attribute("flight_duration").toDouble();
    return to;
}
