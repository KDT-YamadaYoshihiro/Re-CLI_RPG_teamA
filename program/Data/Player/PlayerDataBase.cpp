#include "PlayerDataBase.h"
#include <iostream>
#include <stdexcept>

const std::unordered_map<std::string, PlayerData>
// プライヤーキャラデータ
PlayerDataBase::data =
{
  //{"nameID",{"name",MaxHP,ATK,DEF,INT,MND,speed}},
    {"hero", {"勇者", 100, 30, 20, 30, 15, 50}},
    {"mage", {"魔導士", 60, 5, 8, 55, 25, 40}},
    {"ninja", {"忍者", 75, 25, 12, 20, 10, 85}},
    {"cleric", {"聖職者", 85, 10, 15, 35, 40, 45}},
};


const PlayerData& PlayerDataBase::Get(const std::string& nameId)
{
    // キーが存在するか検索
    auto it = data.find(nameId);
    if (it == data.end()) {
        // エラーログを出してデフォルトデータを返す、あるいはアサーション
        throw std::runtime_error("Unknown Player ID: " + nameId);
    }
    return it->second;
}