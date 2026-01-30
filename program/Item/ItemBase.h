#pragma once
#include <iostream>
#include <string>

// アイテムの種類
enum class ItemType
{
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
	ItemType type;
	int id;					// Item
	int price;				// 売買価格
	int power;			// 使用時または所持時の効果量
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

	const ItemData& GetData() const { return itemData; }

	// 使用時（消費アイテム用）
	virtual void Apply(Character& target) {}

	// 所持時（遺物用）
	virtual void OnAcquire(Character& target) {}
	virtual void OnRemove(Character& target) {}

	bool IsConsumable() const { return itemData.consumables; }
};