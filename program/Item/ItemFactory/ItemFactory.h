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
	std::shared_ptr<ItemBase> CreateItem(int itemID)
	{
		// アイテムデータテーブルから該当IDのデータを探す
		auto it = m_itemDataTable.find(itemID);
		// 見つかったら該当データでアイテム生成、見つからなかったらnullptrを返す
		if (it != m_itemDataTable.end())
		{
			// アイテム生成
			return std::make_shared<T>(it->second);
		}
		// 見つからなかった場合
		else
		{
			// エラーメッセージ出力
			std::cerr << "指定されたIDが存在しませんでした" << itemID << std::endl;
			// nullptrを返す
			return nullptr;
		}
	}
};

