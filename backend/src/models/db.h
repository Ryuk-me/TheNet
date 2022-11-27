#include "user_model.h"
#include "note_model.h"

using namespace sqlite_orm;

class Database : public Users, public Notes
{
public:
    auto create_table()
    {
        auto storage = make_storage("net.sqlite",
                                    make_table("users",
                                               make_column("id", &User::id, primary_key()),
                                               make_column("name", &User::name),
                                               make_column("firebase_id", &User::firebaseId),
                                               make_column("course_name", &User::courseName),
                                               make_column("email", &User::email)),
                                    make_table("notes",
                                               make_column("ID", &Note::id, primary_key()),
                                               make_column("FILENAME", &Note::file_name),
                                               make_column("TIMESTAMP", &Note::timestamp),
                                               make_column("UPLOADED_BY", &Note::uploaded_by),
                                               make_column("SUBJECT_NAME", &Note::subject_name),
                                               make_column("SUBJECT_CODE", &Note::subject_code),
                                               make_column("FILE_LOCATION", &Note::file_location),
                                               make_column("IS_VERIFIED", &Note::is_verified),
                                               make_column("DATE", &Note::date)));
        storage.sync_schema();
        return storage;
    }

    void get_user(std::string id)
    {
        auto storage = create_table();
        auto idLesserThan10 = storage.get_all<User>(where(c(&User::firebaseId) == id));
        std::cout << "idLesserThan10 count = " << idLesserThan10.size() << std::endl;
        for (auto &user : idLesserThan10)
        {
            std::cout << storage.dump(user) << std::endl;
        }
    }
};