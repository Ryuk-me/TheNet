
#define CROW_MAIN
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "config/ENV.h"
#include "sqlite_orm/sqlite_orm.h"
#include "routes/user/user_routes.h"
#include "routes/note/note_routes.h"

namespace fs = std::filesystem;

int main()
{
	// Enable CORS
	crow::App<crow::CORSHandler> app;
	auto &cors = app.get_middleware<crow::CORSHandler>();
	cors
		.global()
		.origin("*");

	Database db; // creating a database object
	auto storage = db.create_table(); // creating table
	UserRoutes::getRoutes(app, storage, db); // user routes 
	NoteRoutes::getRoutes(app, storage, db); // notes routes

	app.port(ENV::PORT).multithreaded().run();
}