#include "EnemyDataBase.h"
#include <iostream>
#include <stdexcept>

const std::unordered_map<std::string, EnemyData>
// 敵のデータ置き場
EnemyDataBase::data =
{
  // 基本形
  //{"nameID",{"name",MaxHP,ATK,DEF,INT,MND,speed,dropGold}},
	{"slime",{"slime",50,10,5,0,5,10}},
	{"goblin",{"goblin",55,15,8,0,5,30}},
	{"bat",{"bat",70,20,12,0,8,40}},
	{"boss",{"wolf",80,25,15,0,10,55}},
};


const EnemyData& EnemyDataBase::Get(const std::string& id)
{
	auto it = data.find(id);
	if (it == data.end()) {
		// エラーログを出してデフォルトデータを返す、あるいはアサーション
		throw std::runtime_error("Unknown Enemy ID: " + id);
	}
	return it->second;
}