#pragma once
#include <unordered_map>
#include "EnemyData.h"

class EnemyDataBase
{
public:
	static const EnemyData& Get(const std::string& id);
private:
	static const std::unordered_map<std::string, EnemyData> data;
};