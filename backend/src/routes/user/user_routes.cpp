#include <string>
#include <iostream>
#include "./user_routes.h"

void UserRoutes::getRoutes(crow::SimpleApp &app, char db)
{
    CROW_ROUTE(app, "/xt")
    ([]()
     { return "1"; });
    // CROW_ROUTE(app, "/user")
    //     .methods("GET"_method, "POST"_method)([](const crow::request &req, crow::response &res)
    //                                           { return "x"; });
}
