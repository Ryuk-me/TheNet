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
        std::string date;
        bool is_verified = false;
    };
    // int insert
};