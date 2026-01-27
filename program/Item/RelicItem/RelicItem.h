#pragma once
#include "../ItemBase.h"

// 遺物アイテム
class RelicItem : public ItemBase
{
private:

	enum class RelicType
	{
		AttacBuff,
		DefenseBuff
	};

	RelicType m_relicType;

public:

	// コンストラクタ・初期化

	// RelicTypeの識別・設定（ItemIDより）

	// Itemの効果適用(override)
	


};

