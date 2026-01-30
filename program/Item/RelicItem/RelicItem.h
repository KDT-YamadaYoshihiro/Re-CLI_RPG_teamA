#pragma once
#include "../ItemBase.h"

// 遺物アイテム
class RelicItem : public ItemBase
{
public:

	// コンストラクタ・初期化
	RelicItem(const ItemData& arg_data) : ItemBase(arg_data) {};
	void Apply(Character& target) override{};

	void OnAcquire(Character& target) override;
	void OnRemove(Character& target) override;
};

