#pragma once
#include "../ItemBase.h"

// 消費型アイテム
class WastageItem : public ItemBase
{
private:

	// 現状データ以外必要ない

public:

	// コンストラクタ・初期化
	WastageItem(const ItemData& arg_data) : ItemBase(arg_data) {};
	// Itemの効果適用(override)
	virtual void ItemEffect() override;	

};

