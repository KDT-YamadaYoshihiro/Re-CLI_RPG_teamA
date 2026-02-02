#pragma once
#include <iostream>
#include <string>

// アイテムの種類
enum class ItemType
{
	Gold,					// お金
	Potion,					// 回復アイテム
	AttackPowerUp,			// 攻撃力強化薬
	DefensePowerUp,			// 防御力強化薬
	Relic_AttackPowerUp,	// 遺物：攻撃力の護符
	Relic_DefencePowerUp	// 遺物：防御力の護符
};

// アイテムデータ項目
struct ItemData
{
	std::string name;		// 名前
	ItemType type;			// 種類
	int id;					// Item
	int price;				// 売買価格
	int power;				// 使用時または所持時の効果量
	bool consumables;		// 消耗品か  true or false
};

class Character; // 前方宣言
// アイテム基底
class ItemBase
{
protected:
	ItemData itemData;

public:
	virtual ~ItemBase() = default;

	ItemBase(const ItemData& data)
		: itemData(data) {
	}


	// 使用時（消費アイテム用）
	virtual void Apply(Character& target) = 0;

	// 所持時（遺物用）
	virtual void OnAcquire(Character& target) = 0;
	virtual void OnRemove(Character & target) = 0;

	/// <summary>
	/// データの取得
	/// </summary>
	/// <returns></returns>
	const ItemData& GetData() const { return itemData; }

	/// <summary>
	/// 消費型かの判定
	/// </summary>
	/// <returns></returns>
	bool IsConsumable() const { return itemData.consumables; }
};