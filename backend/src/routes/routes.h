#define CROW_JSON_USE_MAP

#pragma once
#include "crow.h"

class RouteCollection
{
public:
	static void getRoutes(crow::SimpleApp &app);
};
