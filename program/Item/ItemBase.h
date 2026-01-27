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
	double power;			// 使用時または所持時の効果量
	bool consumables;		// 消耗品か  true or false
};

class Character; // 前方宣言
// アイテム基底
class ItemBase
{
	// 保持データ
protected:

	// データの保持
	ItemData itemData;

public:
	
	// 仮想デストラクタ
	virtual ~ItemBase() = default;
	// コンストラクタ・初期化
	ItemBase(const ItemData& arg_data) : itemData(arg_data) {};
	// 引数はItemデータ参照

	// Itemの効果適用(virtual)-
	void ItemEffect(std::unique_ptr<Character>& arg_taget);


};