#pragma once

#include "hq_economy.hpp"

namespace demonware::achievement_engine
{
	// Catalog values are copied on the main thread; transports never access game assets.
	void set_catalog(std::vector<hq_economy::achievement> catalog);
	std::string dispatch(std::string_view request);
}
