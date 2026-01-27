#pragma 
#include <iostream>
#include <string>

// アイテムデータ項目
struct ItemData
{
	std::string name;		// 名前
	ItemType type;
	int id;					// Item
	double power;			// 使用時または所持時の効果量
	bool consumables;		// 消耗品か
};

// アイテムの種類
enum class ItemType
{
	Potion,
	AttackPowerUp,
	DefensePowerUp,
	Relic,
};

// アイテム基底
class ItemBase
{
protected:

	// データの保持

public:

	// コンストラクタ・初期化
	// 引数はItemデータ参照

	// Itemの効果適用(virtual)
	

};