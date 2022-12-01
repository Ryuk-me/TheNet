#pragma once
#include "../routes.h"
#include "../../models/db.h"
#include "../../utilities/utility.h"
#include "../../config/ENV.h"

using crow::status;

class UserRoutes : public RouteCollection
{
public:
  static void getRoutes(crow::App<crow::CORSHandler> &app, auto &storage, Database &db)
  {
    app.route_dynamic(std::string("/") + ENV::BASE_API_V1 +
                      std::string("/user"))
        .methods(crow::HTTPMethod::POST, crow::HTTPMethod::PUT,
                 crow::HTTPMethod::GET)([&storage, &db](
                                            const crow::request &req, crow::response &res)
                                        {
          if (req.method == crow::HTTPMethod::POST) {
            // POST METHOD WILL ADD A NEW USER TO DB
            auto body = crow::json::load(req.body);
            if (!body) {
              res = crow::response(status::BAD_REQUEST, MESSAGE::INVALID_BODY);
              res.end();
              return;
            }
            if (body.has("name") &&
                body.has("firebase_id") && body.has("email")) { // it will check if all the required keys are passed in request body
              Database::User u;
              u.name = body["name"].s();
              u.firebaseId = body["firebase_id"].s();
              u.email = body["email"].s();
              try {
                int id = db.insert_user(u, storage);
              } catch (std::system_error &e) {
                // if user already exist this error message will be sent back with a status code as 409(CONFLICT) with error message
                res = CUSTOM_MESSAGE::custom_message(crow::status::CONFLICT,
                                                     e.what());
                res.end();
                return;
              }
              res =
                  crow::response(crow::status::CREATED, MESSAGE::DETAILS_ADDED);
              res.end();
              return;
            } else {
              res = crow::response(status::BAD_REQUEST,
                                   MESSAGE::MALFORMED_REQUEST);
              res.end();
              return;
            }
          }
          if (req.method == crow::HTTPMethod::GET) {
            // POST METHOD WILL GET THE CURRENT USER DETAILS FROM DATABASE USING USER'S firebasePid which will be passed as Authorization header
            std::string fbid = req.get_header_value("Authorization");
            std::string path;
            if (fbid.size() == 0) {
              res = crow::response(status::UNAUTHORIZED,
                                   MESSAGE::UNAUTHORIZED_REQUEST);
              res.end();
              return;
            } else {
              auto u = db.get_user(fbid);
              if (u.size() == 0) { // this will check if user exist or not
                res = crow::response(status::UNAUTHORIZED,
                                     MESSAGE::UNAUTHORIZED_REQUEST);
                res.end();
                return;
              } else {
                crow::json::wvalue wv;
                // It will return user data in a json format
                for (auto &user : u) {
                  wv["id"] = user.id;
                  wv["name"] = user.name;
                  wv["firebase_id"] = user.firebaseId;
                  wv["email"] = user.email;
                  res = crow::response(status::OK, wv);
                  res.end();
                  return;
                }
              }
            }
          } });
  };
};
