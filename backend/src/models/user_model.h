#include "sqlite_orm/sqlite_orm.h"

class Users
{
public:
    struct User
    {
        int id = -1;
        std::string name;
        int age;
        std::string address;
        double salary;
    };

    // public:
    int insert_user(User u, auto storage)
    {
        int id = storage.insert(u);
        return id;
    }
};