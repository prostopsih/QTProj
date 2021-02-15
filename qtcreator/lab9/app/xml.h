#pragma once
#include "tour_operator.h"
#include "ticket.h"
#include "QtXml/QtXml"

QDomElement tour_operatorToXmlElement(QDomDocument & doc, const tour_operator & t);
QDomElement ticketToXmlElement(QDomDocument & doc, const ticket & t);

tour_operator xmlElementToTour_operator(QDomElement &t);
ticket xmlElementToTicket(QDomElement &t);
