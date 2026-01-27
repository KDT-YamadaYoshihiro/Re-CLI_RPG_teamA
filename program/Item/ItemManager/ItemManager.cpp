#include "ItemManager.h"

void ItemManager::UseItem(int itemID,std::unique_ptr<Character>& atg_chara)
{
	m_itemMap[itemID]->ItemEffect(atg_chara);
}

std::unordered_map<int, std::shared_ptr<ItemBase>> ItemManager::GetAllItemInfo()
{
	return m_itemMap;
}

std::shared_ptr<ItemBase> ItemManager::GetItemInfo(int itemID)
{
	return m_itemMap[itemID];
}
