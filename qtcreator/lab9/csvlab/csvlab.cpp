#include "csvlab.h"
class Counter
{
 int count = 0;
public:
 Counter() {}
 bool isOk()
 {
  if (count == 0 || count % 2 == 0)
  {
   return true;
  }
  return false;
 }
 Counter& operator++()
 {
  count++;
  return *this;
 }
};
vector<string> parser(string& str)
{
 Counter c;
 vector<string> strS;
 int k = 0;
 for (int i = 0; i < str.length() + 1; i++)
 {
  if ((str[i] == ',' || str[i] == '\0') && c.isOk())
  {
   strS.push_back(str.substr(k, i - k));
   k = i + 1;
  }
  if (str[i] == '\"')
  {
   ++c;
  }
 }
 return strS;
}
vector<tour_operator> EntityFromString(vector<string>& arr)
{

    vector<tour_operator> vec;
    tour_operator token;
    vector<string> temp;
    for (size_t i = 0; i < arr.size(); i++)
    {
        temp = parser(arr[i]);
        token.id = stoi(temp[0]);
        token.country = temp[1];
        token.cost = stod(temp[2]);
        token.length = temp[3];
        vec.push_back(token);
    }
    return vec;
}
vector<string> StringFromEntity(vector<tour_operator>& arr)
{
    vector<string> vec;
    string temp;
    for (int i = 0; i < arr.size(); i++)
    {
        temp = to_string(arr[i].id);
        temp+= (',' + arr[i].country + ',');
        temp+=to_string(arr[i].cost);
        temp+= (',' + arr[i].length);
        vec.push_back(temp);

    }
    return vec;

}
vector<ticket> TicketsFromString(vector<string>& arr)
{
    vector<ticket> vec;
    ticket token;
    vector<string> temp;
    for (size_t i = 0; i < arr.size(); i++)
    {
        temp = parser(arr[i]);
        token.id = stoi(temp[0]);
        token.place_of_departure = temp[1];
        token.place_of_arrival = temp[2];
        token.flight_duration = stod(temp[3]);
        vec.push_back(token);
    }
    return vec;
}
vector<string> StringFromTickets(vector<ticket>& arr)
{
    vector<string> vec;
    string temp;
    for (int i = 0; i < arr.size(); i++)
    {
        temp = to_string(arr[i].id);
        temp+= (',' + arr[i].place_of_departure + ',');
        temp+=arr[i].place_of_arrival;
        temp+= (',' + to_string(arr[i].flight_duration));
        vec.push_back(temp);
    }
    return vec;
}
