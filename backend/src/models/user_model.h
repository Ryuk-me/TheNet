#pragma once
#include "string"
using namespace sqlite_orm;

class Users
{
public:
    // User Schema for db
    struct User
    {
        int id = -1;
        std::string firebaseId;
        std::string email;
        std::string name;
    };

    // Insert a new user to database
    int insert_user(User u, auto &storage)
    {
        int id = storage.insert(u);
        return id;
    }
};