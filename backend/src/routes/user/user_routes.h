#pragma once
#include "../routes.h"
#include "../../models/db.h"

class UserRoutes : public RouteCollection
{
public:
    static void getRoutes(crow::SimpleApp &app, auto &storage, Database &db)
    {
        CROW_ROUTE(app, "/user").methods(crow::HTTPMethod::POST, crow::HTTPMethod::PUT, crow::HTTPMethod::GET)([&](const crow::request &req, crow::response &res)
                                                                                                               {
        if (req.method == crow::HTTPMethod::POST){
            crow::json::rvalue body;
            try{
                body = crow::json::load(req.body);
            }catch(...){
                res = crow::response(400, "probably json syntax error");
                res.end();
                return;

            }
            if(body.has("name") && body.has("course_name") && body.has("firebase_id") && body.has("email")){
                Database::User u;
                u.name = body["name"].s();
                u.courseName = body["course_name"].s();
                u.firebaseId = body["firebase_id"].s();
                u.email = body["email"].s();
                int id = db.insert_user(u,storage);
                std::cout << "ID : " << id << std::endl;
                
                res = crow::response(200,"Details Added Successfully");
                res.end();
                return;
            }
            else{
                res = crow::response(400, "malformed request");
                res.end();
                return;
            }
        }
        if(req.method == crow::HTTPMethod::GET){
            std::cout<<"Heelo\n";
            if (req.url_params.get("id") != nullptr){
                std::string fbid = req.url_params.get("id");
                std::cout<<fbid;
                db.get_user(fbid);
                res = crow::response(200,"id retured");
                res.end();
                return;
            }else{
                res = crow::response(400, "not valid params");
                res.end();
                return;
            }
            
        } });
    };
};
