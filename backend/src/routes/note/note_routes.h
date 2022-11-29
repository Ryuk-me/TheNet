#pragma once
#include "../routes.h"
#include "../../models/db.h"
#include "../../utilities/errors.h"
#include "../../config/ENV.h"
#include <filesystem>

using crow::status;
namespace fs = std::filesystem;

class NoteRoutes : public RouteCollection
{
public:
    static void getRoutes(crow::SimpleApp &app, auto &storage, Database &db)
    {

    CROW_ROUTE(app, "/addnote").methods(crow::HTTPMethod::POST)([&](const crow::request &req)
                                                                        {
    
    crow::multipart::message msg(req);
    for (int i = 0; i < msg.parts.size(); ++i) {
		std::string name, filename, fileContent = msg.parts[i].body;
       	for (auto it=msg.parts[i].headers.begin(); it != msg.parts[i].headers.end();++it) {
			auto const &key = it->first;
			auto const &value = it->second;
			for(const auto &[k,v]: value.params){
				if (k.compare("filename") == 0){
            	    filename = v;
	              } else if (k.compare("name") == 0){
    	            name = v;
        	      } else {
            	    CROW_LOG_WARNING << "unknown key:" << k << " value:" << v
                                 << " " << __FILE__ << " " << __func__ << " "
                                 << __LINE__;
				}
            }

            if (!fs::is_directory("../notes_file") || !fs::exists("../notes_file")) { // Check if folder exists
                fs::create_directory("../notes_file"); // create folder
            }
            std::ofstream fd;
            fd.open("../notes_file/" + filename, std::ios::out | std::ios::binary);
            fd << msg.parts[i].body;
            fd.close();
       }
       std::string path = "C:\\Users\\Ryuk\\Desktop\\TheNet\\backend\\notes_file\\" + std::string(filename);
       std::cout<<path<<std::endl;
   }
    return "it works!"; });
    };
};
