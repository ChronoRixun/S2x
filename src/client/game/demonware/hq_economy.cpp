#include <std_include.hpp>
#include "hq_economy.hpp"

namespace demonware::hq_economy
{
	namespace
	{
		std::mutex state_mutex{};
		state current{};
	}

	state snapshot()
	{
		std::lock_guard lock{state_mutex};
		return current;
	}

	bool transact(const std::function<bool(state&)>& mutation)
	{
		std::lock_guard lock{state_mutex};
		auto next = current;
		if (!mutation(next)) return false;
		++next.revision;
		current = std::move(next);
		return true;
	}

	bool grant(state& data, const reward& value)
	{
		if (value.type == "GRANT_CURRENCY" || value.type == "SET_CURRENCY_BALANCE")
		{
			if (value.id > UINT8_MAX) return false;
			auto& balance = data.currencies[static_cast<std::uint8_t>(value.id)];
			if (value.type == "SET_CURRENCY_BALANCE") balance = value.amount;
			else
			{
				if (value.amount > UINT32_MAX - balance) return false;
				balance += value.amount;
			}
			return true;
		}
		// Only resolved numeric item GUIDs are accepted; product bundles need a catalog.
		if (value.type == "GRANT_PRODUCT" && value.id && value.amount)
		{
			auto& entry = data.inventory[{value.id, 0}];
			if (value.amount > UINT32_MAX - entry.quantity) return false;
			entry.guid = value.id;
			entry.quantity += value.amount;
			entry.modified = static_cast<std::uint32_t>(time(nullptr));
			return true;
		}
		return false;
	}
}
