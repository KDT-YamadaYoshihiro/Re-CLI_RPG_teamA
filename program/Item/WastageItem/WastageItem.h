#pragma once
#include "../ItemBase.h"

class Character; // 前方宣言
// 消費型アイテム
class WastageItem : public ItemBase
{
private:

	// 現状データ以外必要ない

public:

	WastageItem(const ItemData& data);

	void Apply(Character& target) override;

	void OnAcquire(Character& target)override {};
	void OnRemove(Character& target)override {};

};

