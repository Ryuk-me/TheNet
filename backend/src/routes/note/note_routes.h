#pragma once
#include "../routes.h"
#include "../../models/db.h"
#include "../../utilities/errors.h"
#include "../../config/ENV.h"
#include <filesystem>
#include "vector"

using crow::status;
namespace fs = std::filesystem;

class NoteRoutes : public RouteCollection
{
public:
  static void getRoutes(crow::SimpleApp &app, auto &storage, Database &db)
  {
    CROW_ROUTE(app, "/addnoteFile")
        .methods(crow::HTTPMethod::POST)([&](const crow::request &req,
                                             crow::response &res)
                                         {

        crow::multipart::message msg(req);
        std::string fbid = req.get_header_value("Authorization");
        bool is_auth = true;
        std::string path;
        if (fbid.size() == 0) {
          is_auth = false;
        } else {
          auto u = db.get_user(fbid);
          if (u.size() == 0) {
            is_auth = false;
          }
        }
        if (!is_auth) {
          res =
            crow::response(status::UNAUTHORIZED, MESSAGE::UNAUTHORIZED_REQUEST);
          res.end();
          return;
        }
        for (int i = 0; i < msg.parts.size(); ++i) {
          std::string name, filename, fileContent = msg.parts[i].body;
          for (auto it = msg.parts[i].headers.begin();
               it != msg.parts[i].headers.end(); ++it) {
            auto const& key = it->first;
            auto const& value = it->second;
            for (const auto & [ k, v ] : value.params) {
              if (k.compare("filename") == 0) {
                filename = v;
              } else if (k.compare("name") == 0) {
                name = v;
              } else {
                CROW_LOG_WARNING << "unknown key:" << k << " value:" << v << " "
                                 << __FILE__ << " " << __func__ << " "
                                 << __LINE__;
              }
            }
          }
          if (filename.size() == 0) {
            res =
              crow::response(status::BAD_REQUEST, MESSAGE::NO_FILE_PROVIDED);
            res.end();
            return;
          }
          std::string folder = "../notes_file/" + fbid;
          if (!fs::is_directory(folder) ||
              !fs::exists(folder)) {      // Check if folder exists
            fs::create_directory(folder); // create folder
          }
          std::ofstream fd;
          fd.open(folder + std::string("/") + filename,
                  std::ios::out | std::ios::binary);
          fd << msg.parts[i].body;
          fd.close();
          path = "C:\\Users\\Ryuk\\Desktop\\TheNet\\backend\\notes_file\\" +
                 fbid + "\\" + std::string(filename);
        }
        res = CUSTOM_MESSAGE::custom_message(status::OK, path);
        res.end();
        return; });

    CROW_ROUTE(app, "/addnoteJson")
        .methods(crow::HTTPMethod::POST)([&](const crow::request &req,
                                             crow::response &res)
                                         {
        std::string fbid = req.get_header_value("Authorization");
        bool is_auth = true;
        if (fbid.size() == 0) {
          is_auth = false;
        } else {
          auto u = db.get_user(fbid);
          if (u.size() == 0) {
            is_auth = false;
          }
        }
        if (!is_auth) {
          res =
            crow::response(status::UNAUTHORIZED, MESSAGE::UNAUTHORIZED_REQUEST);
          res.end();
          return;
        }

        auto body = crow::json::load(req.body);
        if (!body) {
          res = crow::response(status::BAD_REQUEST, MESSAGE::INVALID_BODY);
          res.end();
          return;
        }
        if (body.has("file_name") && body.has("subject_name") &&
            body.has("subject_code") && body.has("uploaded_by") &&
            body.has("date") && body.has("timestamp") &&
            body.has("is_verified") && body.has("file_location") &&
            body.has("firebase_id")) {
          Database::Note n;
          n.file_name = body["file_name"].s();
          n.subject_name = body["subject_name"].s();
          n.subject_code = body["subject_code"].s();
          n.uploaded_by = body["uploaded_by"].s();
          n.date = body["date"].s();
          n.timestamp = body["timestamp"].s();
          n.is_verified = body["is_verified"].b();
          n.file_location = body["file_location"].s();
          n.firebaseId = body["firebase_id"].s();
          try {
            int id = db.insert_note(n, storage);
          } catch (std::system_error& e) {
            res =
              CUSTOM_MESSAGE::custom_message(crow::status::CONFLICT, e.what());
            res.end();
            return;
          }
        } else {
          res = crow::response(status::BAD_REQUEST, MESSAGE::MALFORMED_REQUEST);
          res.end();
          return;
        }
        res = crow::response(status::OK, MESSAGE::FILE_ADDED);
        res.end();
        return; });
    CROW_ROUTE(app, "/note")
        .methods(crow::HTTPMethod::GET)([&](const crow::request &req,
                                            crow::response &res)
                                        {
        std::string fbid = req.get_header_value("Authorization");
        bool is_auth = true;
        if (fbid.size() == 0) {
          is_auth = false;
        } else {
          auto u = db.get_user(fbid);
          if (u.size() == 0) {
            is_auth = false;
          }
        }
        if (!is_auth) {
          res =
            crow::response(status::UNAUTHORIZED, MESSAGE::UNAUTHORIZED_REQUEST);
          res.end();
          return;
        }
        if (req.url_params.get("subject") != nullptr) {
          std::string subject_name = req.url_params.get("subject");
          std::cout << "sub :" << subject_name;
          if (subject_name.size() == 0) {
            res = CUSTOM_MESSAGE::custom_message(status::BAD_REQUEST,
                                                 "subject not provided.");
            res.end();
            return;
          }
          auto note = db.get_note_from_subject_name(subject_name);
          if (note.size() == 0) {
            res = crow::response(status::NOT_FOUND, MESSAGE::NOTES_NOT_FOUND);
            res.end();
            return;
          }
          std::vector<crow::json::wvalue> wv;
          for (auto& n : note) {
            wv.push_back(
              crow::json::wvalue{ { "date", n.date },
                                  { "subject_code", n.subject_code },
                                  { "subject_name", n.subject_name },
                                  { "uploaded_by", n.uploaded_by },
                                  { "is_verified", n.is_verified },
                                  { "file_locatiion", n.file_location },
                                  { "file_name", n.file_name },
                                  { "timestamp", n.timestamp } });
          }
          crow::json::wvalue x{ { "results", wv } };
          res = crow::response(status::OK, x);
          res.end();
          return;
        } else {
          res = crow::response(status::BAD_REQUEST, MESSAGE::NOT_VALID_PARAMS);
          res.end();
          return;
        }
        return; });
  };
};