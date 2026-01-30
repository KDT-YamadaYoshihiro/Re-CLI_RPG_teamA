#pragma once
#include "../ItemBase.h"
#include "../../Singleton/Singleton.h"
#include <unordered_map>

// アイテムIDの種類
enum class ItemIdType
{
	LowerPotion,			// 低級ポーション
	IntermediatePotion,		// 中級ポーション
	HighPotion,				// 上級ポーション
	AttackPowerUp,			// 攻撃力強化薬
	DefensePowerUp,			// 防御力強化薬
	Relic_AttackPowerUp,    // 遺物：攻撃力の護符
	Relic_DefencePowerUp	// 遺物：防御力の護符
};

class WastageItem; // 前方宣言
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
	template<typename T>
	std::shared_ptr<ItemBase> ItemFactory::CreateItem(int itemID)
	{
		auto it = m_itemDataTable.find(itemID);
		if (it == m_itemDataTable.end())
			return nullptr;

		const ItemData& data = it->second;

		if (data.consumables)
		{
			return std::make_shared<WastageItem>(data);
		}
		else
		{
			return std::make_shared<RelicItem>(data);
		}
	}
};

