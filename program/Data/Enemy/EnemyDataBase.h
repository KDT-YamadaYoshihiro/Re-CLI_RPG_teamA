#pragma once
#include  <string>
#include "EnemyData.h"
#include <unordered_map>

class EnemyDataBase {
public:
	static const EnemyData& Get(const std::string& Id);

private:
	static const std::unordered_map<std::string, EnemyData> data;
};