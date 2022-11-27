
#define CROW_MAIN
#include "crow.h"
#include "config/ENV.h"
#include <nlohmann/json.hpp>
#include "sqlite_orm/sqlite_orm.h"
#include "routes/user/user_routes.h"
#include <filesystem>
using json = nlohmann::json;

namespace fs = std::filesystem;

int main()
{
	crow::SimpleApp app;
	Database db;

	auto storage = db.create_table();
	UserRoutes::getRoutes(app, storage, db);

// 	CROW_ROUTE(app, "/note").methods(crow::HTTPMethod::POST, crow::HTTPMethod::GET)([&](const crow::request &req)
// 																					{
// 		if (req.method == crow::HTTPMethod::POST)
// 		{
// 			Database::Note n;
// 			auto body = crow::json::load(req.body);
// 			n.file_name = body["file_name"].s();
// 			n.subject_name = body["subject_name"].s();
// 			n.subject_code = body["subject_code"].s();
// 			n.uploaded_by = body["uploaded_by"].s();
// 			n.date = body["date"].s();
// 			n.timestamp = body["timestamp"].s();
// 			n.is_verified = body["is_verified"].b();
// 			int id = db.insert_note(n, storage);
// 			return "note endpoint";
// 		}
// 		else if (req.method == crow::HTTPMethod::GET)
// 		{
// 			return "not implemented yet";
// 		}

// 		return "this method does not exist"; });

// 	CROW_ROUTE(app, "/uploadFiles").methods(crow::HTTPMethod::POST)([&](const crow::request &req)
// 																	{
//     crow::multipart::message msg(req);
//     for (int i = 0; i < msg.parts.size(); ++i) {
// 		std::string name, filename, fileContent = msg.parts[i].body;
//        	for (auto it=msg.parts[i].headers.begin(); it != msg.parts[i].headers.end();++it) {
// 			auto const &key = it->first;
// 			auto const &value = it->second;
// 			for(const auto &[k,v]: value.params){
// 				if (k.compare("filename") == 0){
//             	    filename = v;
// 	              } else if (k.compare("name") == 0){
//     	            name = v;
//         	      } else {
//             	    CROW_LOG_WARNING << "unknown key:" << k << " value:" << v
//                                  << " " << __FILE__ << " " << __func__ << " "
//                                  << __LINE__;
// 				}
//             }

//             if (!fs::is_directory("tmp") || !fs::exists("tmp")) { // Check if tmp folder exists
//                 fs::create_directory("tmp"); // create tmp folder
//             }
//             std::ofstream fd;
//             fd.open("./tmp/" + filename, std::ios::out | std::ios::binary);
//             fd << msg.parts[i].body;
//             fd.close();
// 			std::filesystem::path cwd = std::filesystem::current_path() / "tmp" / filename;
// 			std::cout<<cwd.string();
//        }
//    }
//    return "it works!"; });

	CROW_ROUTE(app, "/test")
	([]
	 {
		crow::json::wvalue x({{"test", "hello"}});
		return crow::response(200, x); });

	app.port(ENV::PORT).multithreaded().run();
}