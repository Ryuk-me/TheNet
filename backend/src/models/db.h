#pragma once
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
                                               make_column("id", &User::id, autoincrement(), primary_key()),
                                               make_column("name", &User::name),
                                               make_column("firebase_id", &User::firebaseId, unique()),
                                               make_column("course_name", &User::courseName),
                                               make_column("email", &User::email)),
                                    make_table("notes",
                                               make_column("id", &Note::id, autoincrement(), primary_key()),
                                               make_column("filename", &Note::file_name),
                                               make_column("timestamp", &Note::timestamp),
                                               make_column("firebase_id", &Note::firebaseId),
                                               make_column("uploaded_by", &Note::uploaded_by),
                                               make_column("subject_name", &Note::subject_name),
                                               make_column("subject_code", &Note::subject_code),
                                               make_column("file_location", &Note::file_location),
                                               make_column("is_verified", &Note::is_verified),
                                               make_column("date", &Note::date),
                                               foreign_key(&Note::firebaseId).references(&User::firebaseId)));
        storage.sync_schema();
        return storage;
    }

    auto get_user(std::string id)
    {
        auto storage = create_table();
        auto user = storage.get_all<User>(where(c(&User::firebaseId) == id));
        return user;
    }
};