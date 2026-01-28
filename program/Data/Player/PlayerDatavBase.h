#pragma once
#include <unordered_map>
#include "PlayerData.h"

class PlayerDataBase
{
public:
	static const PlayerData& Get(const std::string& id);
private:
	static const std::unordered_map<std::string, PlayerData> data;
};