#include <string>
#include "QPixmap"
using namespace std;
#ifndef USER_HPP
#define USER_HPP
struct User
{
    int id;
    string password_hash;
    string username;
    QPixmap picture;
    User()
    {
    }
    User(User& obj)
    {
        id = obj.id;
        password_hash = obj.password_hash;
        username = obj.username;
        picture = obj.picture;
    }
};
#endif // USER_HPP
