#include "storage.h"

void Storage::setName(const string & dir_name)
{
    if(!isOpen())
    dir_name_ = dir_name;
}
string Storage::name() const
{
    return dir_name_;
}
