#pragma once
#include "../routes.h"
#include "../../models/db.h"
#include "../../utilities/utility.h"
#include "../../config/ENV.h"

using crow::status;

class UserRoutes : public RouteCollection
{
public:
    static void getRoutes(crow::SimpleApp &app, auto &storage, Database &db)
    {
        app.route_dynamic(std::string("/") + ENV::BASE_API_V1 +
                          std::string("/user"))
            .methods(crow::HTTPMethod::POST, crow::HTTPMethod::PUT,
                     crow::HTTPMethod::GET)([&storage, &db](
                                                const crow::request &req, crow::response &res)
                                            {
          if (req.method == crow::HTTPMethod::POST) {
            auto body = crow::json::load(req.body);
            if (!body) {
              res = crow::response(status::BAD_REQUEST, MESSAGE::INVALID_BODY);
              res.end();
              return;
            }
            if (body.has("name") && body.has("course_name") &&
                body.has("firebase_id") && body.has("email")) {
              Database::User u;
              u.name = body["name"].s();
              u.courseName = body["course_name"].s();
              u.firebaseId = body["firebase_id"].s();
              u.email = body["email"].s();
              try {
                int id = db.insert_user(u, storage);
              } catch (std::system_error &e) {
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
            std::string fbid = req.get_header_value("Authorization");
            std::string path;
            if (fbid.size() == 0) {
              res = crow::response(status::UNAUTHORIZED,
                                   MESSAGE::UNAUTHORIZED_REQUEST);
              res.end();
              return;
            } else {
              auto u = db.get_user(fbid);
              if (u.size() == 0) {
                res = crow::response(status::UNAUTHORIZED,
                                     MESSAGE::UNAUTHORIZED_REQUEST);
                res.end();
                return;
              } else {
                crow::json::wvalue wv;
                for (auto &user : u) {
                  wv["id"] = user.id;
                  wv["name"] = user.name;
                  wv["firebase_id"] = user.firebaseId;
                  wv["course_name"] = user.courseName;
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
