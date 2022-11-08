#define CROW_MAIN
#include "crow.h"
#include "config/ENV.h"
#include <nlohmann/json.hpp>
// #include "sqlite_orm/sqlite_orm.h"
#include "routes/user/user_routes.h"

using json = nlohmann::json;
// UserRoutes::getRoutes("app")

int main()
{
    crow::SimpleApp app; // define your crow application
    UserRoutes::getRoutes(app, '1');
    // define your endpoint at the root directory
    // UserRoutes::getRoutes(app);

    // app.route_dynamic(("/" + ENV::BASE_API_V1).c_str())(
    //     []()
    //     {
    //         return "xd";
    //     });

    // CROW_ROUTE(app, "/")
    // ([]()
    //  { return "Hello world"; });

    // UserRoutes::getRoutes(app, '1');

    // set the port, set the app to run on multiple threads, and run the app
    app.port(ENV::PORT).multithreaded().run();
}