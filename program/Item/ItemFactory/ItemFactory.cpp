#include "ItemFactory.h"
#include "Item/ItemBase.h"

#include "Item/RelicItem/RelicItem.h"
#include "Item/WastageItem/WastageItem.h"


void ItemFactory::OnCreate()
{
    //　アイテムデータテーブルの初期化
    // 名前、タイプ、ID、効果量、消耗品か否か
    // お金
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::Gold), ItemData{ "ゴールド", ItemType::Gold, static_cast<int>(ItemIdType::Gold), 1, 0,true });
    // ポーション系
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::LowerPotion), ItemData{ "低級ポーション", ItemType::Potion, static_cast<int>(ItemIdType::LowerPotion), 20, 50, true });
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::MiddlePotion), ItemData{ "中級ポーション", ItemType::Potion, static_cast<int>(ItemIdType::MiddlePotion), 100, 100, true });
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::HighPotion), ItemData{ "高級ポーション", ItemType::Potion, static_cast<int>(ItemIdType::HighPotion), 200, 300, true });
    //  強化薬系
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::AttackPowerUp), ItemData{ "攻撃力強化薬", ItemType::AttackPowerUp, static_cast<int>(ItemIdType::AttackPowerUp), 10, 500, true });
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::DefensePowerUp), ItemData{ "防御力強化薬", ItemType::DefensePowerUp, static_cast<int>(ItemIdType::DefensePowerUp), 10,500, true });
    //  遺物系
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::Relic_AttackPowerUp), ItemData{ "遺物：攻撃力の護符", ItemType::Relic_AttackPowerUp, static_cast<int>(ItemIdType::Relic_AttackPowerUp), 15, 800, false });
    m_itemDataTable.emplace(static_cast<int>(ItemIdType::Relic_DefencePowerUp), ItemData{ "遺物：防御力の護符", ItemType::Relic_DefencePowerUp, static_cast<int>(ItemIdType::Relic_DefencePowerUp), 15, 800, false });
}

std::shared_ptr<ItemBase> ItemFactory::CreateItem(int itemID)
{
    auto it = m_itemDataTable.find(itemID);
    if (it == m_itemDataTable.end())
    {
        return nullptr;
    }

    const ItemData& data = it->second;

    if (data.consumables)
    {
        return std::make_shared<WastageItem>(data);
    }
    else
    {
        return std::make_shared<RelicItem>(data);
    }
}

const std::unordered_map<int, ItemData>& ItemFactory::GetItemDataTable() const
{
    return m_itemDataTable;
}
