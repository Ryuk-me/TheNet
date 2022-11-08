#define CROW_MAIN
#include "crow.h"
#include "config/ENV.h"
#include <nlohmann/json.hpp>
#include "sqlite_orm/sqlite_orm.h"
#include "routes/user/user_routes.h"
#include "models/db.h"

using json = nlohmann::json;

int main()
{
    crow::SimpleApp app;
    UserRoutes::getRoutes(app);
    Database db;
    auto storage = db.create_table();
    CROW_ROUTE(app, "/add").methods(crow::HTTPMethod::POST)([&](const crow::request &req)
                                                            {
        auto body = crow::json::load(req.body);
        Database::User u;
        u.name =  body["name"].s();
        u.age = body["age"].i();
        u.address = body["address"].s();
        u.salary = body["salary"].d();

        int id = db.insert_user(u,storage);
        std::cout<<"ID : "<<id<<std::endl;
        // User::Employee paul{-1, body["name"].s(), body["age"].i(), std::make_unique<std::string>(body["address"].s()), std::make_unique<double>(body["salary"].d())};

        // return crow::response(200, "Blog added"); 
        return crow::json::wvalue(body); });
    app.port(ENV::PORT).multithreaded().run();
}