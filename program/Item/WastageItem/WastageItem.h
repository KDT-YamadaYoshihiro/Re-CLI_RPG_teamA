#pragma once
#include "../ItemBase.h"

class Character; // 前方宣言
// 消費型アイテム
class WastageItem : public ItemBase
{
private:

	// 現状データ以外必要ない

public:

	// コンストラクタ・初期化
	WastageItem(const ItemData& arg_data) : ItemBase(arg_data) {};

};

