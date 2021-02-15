#ifndef VEC_H
#define VEC_H

#include <QString>
#include <vector>
#include "tour.hpp"
#include "tour_operator.hpp"
using namespace std;

class Vec
{
public:
    static void findNeeded(vector<tour_operator>& arr, QString& str);
    static void findNeeded(vector<tour>& arr, QString& str);
};

#endif // VEC_H
