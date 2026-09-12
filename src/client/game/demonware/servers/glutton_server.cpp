#include <std_include.hpp>
#include "glutton_server.hpp"
#include "../achievement_engine.hpp"

namespace demonware
{
	void glutton_server::handle_request(const http_request& request)
	{
		rapidjson::Document response{rapidjson::kObjectType};
		if (request.target.find("/secureingest/") == std::string::npos)
		{
			const auto json = achievement_engine::dispatch(request.body);
			response.Parse(json.data(), json.size());
		}
		send_json(response);
	}
}
