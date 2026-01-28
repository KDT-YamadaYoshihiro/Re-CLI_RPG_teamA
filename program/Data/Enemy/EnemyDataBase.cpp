#include "EnemyDataBase.h"
const std::unordered_map<std::string, EnemyData>
EnemyDataBase::data =
{
	{"nameID",{"name",50,10,5,0,5,100,500}},
	{"b",{"b",50,10,5,0,5,100,500}},
	{"c",{"c",50,10,5,0,5,100,500}},
	{"d",{"d",50,10,5,0,5,100,500}},
	{"e",{"e",50,10,5,0,5,100,500}},
	{"f",{"f",50,10,5,0,5,100,500}},
};

const EnemyData& EnemyDataBase::Get(const std::string& id)
{
	return data.at(id);
}