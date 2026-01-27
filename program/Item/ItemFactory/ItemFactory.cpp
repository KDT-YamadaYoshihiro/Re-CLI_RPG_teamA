#include "ItemFactory.h"
#include "../../Item/ItemBase.h"

void ItemFactory::OnCreate()
{
	//　アイテムデータテーブルの初期化
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::LowerPotion), ItemData{ "低級ポーション", ItemType::Potion, static_cast<int>(ItemIdType::LowerPotion), 20.0, true });
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::IntermediatePotion), ItemData{ "中級ポーション", ItemType::Potion, static_cast<int>(ItemIdType::IntermediatePotion), 100.0, true });
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::HighPotion), ItemData{ "高級ポーション", ItemType::Potion, static_cast<int>(ItemIdType::HighPotion), 200.0, true });
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::AttackPowerUp), ItemData{ "攻撃力強化薬", ItemType::AttackPowerUp, static_cast<int>(ItemIdType::AttackPowerUp), 10.0, true });	
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::DefensePowerUp), ItemData{ "防御力強化薬", ItemType::DefensePowerUp, static_cast<int>(ItemIdType::DefensePowerUp), 10.0, true });
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::Relic_AttackPowerUp), ItemData{ "遺物：攻撃力の護符", ItemType::Relic_AttackPowerUp, static_cast<int>(ItemIdType::Relic_AttackPowerUp), 15.0, false });
	m_itemDataTable.emplace(static_cast<int>(ItemIdType::Relic_DefencePowerUp), ItemData{ "遺物：防御力の護符", ItemType::Relic_DefencePowerUp, static_cast<int>(ItemIdType::Relic_DefencePowerUp), 15.0, false });
}
