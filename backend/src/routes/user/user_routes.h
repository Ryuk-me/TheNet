#pragma once
#include "../routes.h"

class UserRoutes : public RouteCollection
{
public:
    static void getRoutes(crow::SimpleApp &app);
};