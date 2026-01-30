#pragma once
#include "../ItemBase.h"
#include "../../Singleton/Singleton.h"
#include <unordered_map>

// アイテムIDの種類
enum class ItemIdType
{
    LowerPotion,            // 低級ポーション
    IntermediatePotion,     // 中級ポーション
    HighPotion,             // 上級ポーション
    AttackPowerUp,          // 攻撃力強化薬
    DefensePowerUp,         // 防御力強化薬
    Relic_AttackPowerUp,    // 遺物：攻撃力の護符
    Relic_DefencePowerUp    // 遺物：防御力の護符
};

class WastageItem; // 前方宣言
class RelicItem;

// アイテム生成クラス
class ItemFactory : public Singleton<ItemFactory>
{
    friend class Singleton<ItemFactory>;
    // データーテーブルを使用してアイテム生成を行うクラス
    std::unordered_map<int, ItemData> m_itemDataTable;

    //　ステータスデータの設定
    void OnCreate();
public:

    // 指定されたIDよりアイテムを生成
    std::shared_ptr<ItemBase> CreateItem(int itemID);

};

