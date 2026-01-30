#include "EnemyDataBase.h"
const std::unordered_map<std::string, EnemyData>
// 敵のデータ置き場
EnemyDataBase::data =
{
  // 基本形
  //{"nameID",{"name",MaxHP,ATK,DEF,INT,MND,speed,dropGold}},
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