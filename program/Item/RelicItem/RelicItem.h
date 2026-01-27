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
	RelicItem(const ItemData& arg_data) : ItemBase(arg_data) {};
	// RelicTypeの識別・設定（ItemIDより）
	RelicItem::RelicType m_relicType(int itemID);
	// Itemの効果適用(override)
	virtual void ItemBase::ItemEffect() override;


};

