#ifndef CSVLAB_H
#define CSVLAB_H
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "tour_operator.h"
#include "ticket.h"
vector<string> parser(string& str);

vector<tour_operator> EntityFromString(vector<string>& arr);
vector<string> StringFromEntity(vector<tour_operator>& arr);

vector<ticket> TicketsFromString(vector<string>& arr);
vector<string> StringFromTickets(vector<ticket>& arr);
/*class csvlab
{

public:
    csvlab();
};*/

#endif // CSVLAB_H
