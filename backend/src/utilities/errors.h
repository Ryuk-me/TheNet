#pragma once
#include "crow.h"

namespace MESSAGE
{
    crow::json::wvalue INVALID_BODY({{"message", "Invalid Body"}});
    crow::json::wvalue DETAILS_ADDED({{"message", "Details addded."}});
    crow::json::wvalue MALFORMED_REQUEST({{"message", "Malformed request."}});
    crow::json::wvalue USER_NOT_FOUND({{"message", "User not found."}});
    crow::json::wvalue NOT_VALID_PARAMS({{"message", "Not valid parameter/s."}});
    crow::json::wvalue NO_FILE_PROVIDED({{"message", "No file provided."}});
    crow::json::wvalue UNAUTHORIZED_REQUEST({{"message", "Unauthorized request."}});
    crow::json::wvalue FILE_ADDED({{"message", "Note added."}});
    crow::json::wvalue FILE_ALREADY_EXIST({{"message", "This file already exist."}});
    crow::json::wvalue NOTES_NOT_FOUND({{"message", "Notes not found"}});
}

namespace CUSTOM_MESSAGE
{
    auto custom_message(int status, auto string)
    {
        crow::json::wvalue CUSTOM_MESSAGE_LOG({{"message", string}});
        return crow::response(status, CUSTOM_MESSAGE_LOG);
    }
}
