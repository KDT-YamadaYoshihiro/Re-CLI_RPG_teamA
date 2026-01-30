#include "PlayerDataBase.h"


const std::unordered_map<std::string, PlayerData>
// プライヤーキャラデータ
PlayerDataBase::data =
{
  //{"nameID",{"name",MaxHP,ATK,DEF,INT,MND,speed}},
	{"nameID",{"name",50,10,5,0,5,100}},
	{"b",{"b",50,10,5,0,5,100}},
	{"c",{"c",50,10,5,0,5,100}},
	{"d",{"d",50,10,5,0,5,100}},
};


const PlayerData& PlayerDataBase::Get(const std::string& id)
{
	return data.at(id);
}