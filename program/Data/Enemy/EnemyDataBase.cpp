#include "EnemyDataBase.h"

const std::unordered_map<std::string, EnemyData>




EnemyDataBase::data =
{
	
};

const EnemyData& EnemyDataBase::Get(const std::string& id)
{
	return data.at(id);
}


