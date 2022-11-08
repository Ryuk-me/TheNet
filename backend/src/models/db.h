#include "user_model.h"
#include "note_model.h"

using namespace sqlite_orm;

class Database : public Users, public Notes
{
public:
    auto create_table()
    {
        auto storage = make_storage("net.sqlite",
                                    make_table("USERS",
                                               make_column("ID", &User::id, primary_key()),
                                               make_column("NAME", &User::name),
                                               make_column("AGE", &User::age),
                                               make_column("ADDRESS", &User::address),
                                               make_column("SALARY", &User::salary)),
                                    make_table("NOTES",
                                               make_column("ID", &Note::id, primary_key()),
                                               make_column("FILENAME", &Note::file_name),
                                               make_column("TIMESTAMP", &Note::timestamp),
                                               make_column("UPLOADED_BY", &Note::uploaded_by),
                                               make_column("SUBJECT_NAME", &Note::subject_name),
                                               make_column("SUBJECT_CODE", &Note::subject_code),
                                               make_column("IS_VERIFIED", &Note::is_verified),
                                               make_column("DATE", &Note::date)));
        storage.sync_schema();
        return storage;
    }
};