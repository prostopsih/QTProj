#include "vec.h"

void Vec::findNeeded(vector<tour_operator>& arr, QString& str)
{
    for(auto i = arr.begin();i!=arr.end();i++)
    {
        if(i->name.find(str.toStdString()) == string::npos)
        {
            arr.erase(i);
            i--;
        }
    }
}
void Vec::findNeeded(vector<tour>& arr, QString& str)
{
    for(auto i = arr.begin();i!=arr.end();i++)
    {
        if((i->place_of_departure + " - " + i->place_of_arrival).find(str.toStdString()) == string::npos)
        {
            arr.erase(i);
            i--;
        }
    }
}
