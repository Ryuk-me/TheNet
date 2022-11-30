#pragma once
#include "sqlite_orm/sqlite_orm.h"

class Notes
{

public:
    struct Note
    {
        int id = -1;
        std::string file_name;
        std::string timestamp;
        std::string uploaded_by;
        std::string subject_name;
        std::string subject_code;
        std::string firebaseId;
        std::string date;
        std::string file_location;
        bool is_verified = false;
    };

    int insert_note(Note n, auto storage)
    {
        int id = storage.insert(n);
        return id;
    }

};