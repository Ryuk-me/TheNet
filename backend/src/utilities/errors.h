#pragma once
#include "crow.h"

namespace ERROR
{
    crow::json::wvalue INVALID_BODY({{"message", "Invalid Body"}});
    crow::json::wvalue DETAILS_ADDED({{"message", "Details addded."}});
    crow::json::wvalue MALFORMED_REQUEST({{"message", "Malformed request."}});
    crow::json::wvalue USER_NOT_FOUND({{"message", "User not found."}});
    crow::json::wvalue NOT_VALID_PARAMS({{"message", "Not valid parameter/s."}});
}

namespace CUSTOM_ERROR
{
    auto custom_error(int status, auto string)
    {
        crow::json::wvalue CUSTOM_ERROR_LOG({{"message", string}});
        return crow::response(status, CUSTOM_ERROR_LOG);
    }
}
