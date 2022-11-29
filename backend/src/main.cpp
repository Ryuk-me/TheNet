
#define CROW_MAIN
#include "crow.h"
#include "config/ENV.h"
#include "sqlite_orm/sqlite_orm.h"
#include "routes/user/user_routes.h"
#include "routes/note/note_routes.h"

namespace fs = std::filesystem;

int main()
{
	crow::SimpleApp app;
	Database db;

	auto storage = db.create_table();
	UserRoutes::getRoutes(app, storage, db);
	NoteRoutes::getRoutes(app, storage, db);

	app.port(ENV::PORT).multithreaded().run();
}