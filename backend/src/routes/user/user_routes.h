#pragma once
#include "../routes.h"
#include "../../models/db.h"

class UserRoutes : public RouteCollection
{
public:
    static void getRoutes(crow::SimpleApp &app, auto &storage, Database &db)
    {
        CROW_ROUTE(app, "/user").methods(crow::HTTPMethod::POST, crow::HTTPMethod::PUT, crow::HTTPMethod::GET)([&storage, &db](const crow::request &req, crow::response &res)
                                                                                                               {
        if (req.method == crow::HTTPMethod::POST){
            auto body = crow::json::load(req.body);
            if(!body){
                crow::json::wvalue INVALID_BODY({
                    {"message" , "Invalid Body"}
                });
                res = crow::response(400, INVALID_BODY);
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
                crow::json::wvalue DETAILS_ADDED({
                    {"message" , "Details addded."}
                });
                res = crow::response(200,DETAILS_ADDED);
                res.end();
                return;
            }
            else{
                crow::json::wvalue MALFORMED_REQUEST({
                    {"message" , "Malformed request."}
                });
                res = crow::response(400,MALFORMED_REQUEST);
                res.end();
                return;
            }
        }
        if(req.method == crow::HTTPMethod::GET){
            if (req.url_params.get("id") != nullptr){
                std::string fbid = req.url_params.get("id");
                std::cout<<fbid;
                auto u = db.get_user(fbid);
                if(u.size() == 0){
                    crow::json::wvalue USER_NOT_FOUND({
                    {"message" , "User not found."}
                });
                    res = crow::response(200,USER_NOT_FOUND);
                    res.end();
                    return;
                }
                crow::json::wvalue wv;
                for(auto &user : u) {
                    wv["id"] = user.id;
                    wv["name"]= user.name;
                    wv["firebase_id"] = user.firebaseId;
                    wv["course_name"] = user.courseName;
                    wv["email"] =user.email;
                    res = crow::response(200,wv);
                    res.end();
                    return;
                }
                
            }else{
                crow::json::wvalue NOT_VALID_PARAMS({
                    {"message" , "Not valid parameters."}
                });
                res = crow::response(400, NOT_VALID_PARAMS);
                res.end();
                return;
            }
            
        } });
    };
};
