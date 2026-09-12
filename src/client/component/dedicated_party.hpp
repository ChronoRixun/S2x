#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dedicated_party
{
	// The dedicated frontend owner is party member 0 but never a player. The
	// native party and session capacity must reserve its slot on top of the
	// advertised player limit, otherwise the last player cannot join.
	constexpr int host_member_slots = 1;

	constexpr int party_capacity(const int max_players)
	{
		return max_players + host_member_slots;
	}

	struct dedicated_match_t
	{
		std::string map_name{};
		std::string gametype{};
		int map_index{};
	};

	struct connect_info
	{
		std::string host_address{};
		std::string key{};
		std::string session_id{};
		std::string map_name{};
		std::string gametype{};
		std::uint64_t match_sequence{};
		int member_count{};
		int max_members{};
		bool match_running{};
	};

	void start();
	bool is_active();
	std::string get_current_gametype();
	bool set_rotation(std::vector<dedicated_match_t> rotation);
	bool rotate();
	bool set_next_match(const std::string& map_name, const std::string& gametype, int map_index);
	bool get_connect_info(connect_info& info);
}
