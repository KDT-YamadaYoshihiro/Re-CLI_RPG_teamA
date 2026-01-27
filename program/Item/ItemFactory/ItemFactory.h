#pragma once
#include "../ItemBase.h"
#include "../../Singleton/Singleton.h"
#include <unordered_map>

enum class ItemIdType
{
	LowerPotion,  
	IntermediatePotion,
	HighPotion,
	AttackPowerUp,
	DefensePowerUp,
	Relic_AttackPowerUp,
	Relic_DefencePowerUp
};

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
	std::shared_ptr<ItemBase> CreateItem(int itemID)
	{
		auto it = m_itemDataTable.find(itemID);
		if (it != m_itemDataTable.end())
		{
			return std::make_shared<T>(it->second);
		}
		else
		{
			std::cerr << "指定されたIDが存在しませんでした" << itemID << std::endl;
			return nullptr;
		}
	}
};

