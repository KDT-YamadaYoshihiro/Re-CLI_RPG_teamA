#include "ItemManager.h"

void ItemManager::AddItem(int itemID, Character& owner)
{
	auto item = ItemFactory::GetInstance().CreateItem(itemID);
	if (!item) return;

	auto& stack = m_items[itemID];
	if (stack.count == 0)
	{
		stack.item = item;

		// ˆâ•¨‚È‚ç‘¦Œø‰Ê
		if (!item->IsConsumable())
			item->OnAcquire(owner);
	}
	stack.count++;
}

void ItemManager::UseItem(int itemID, Character& target)
{
	uto it = m_items.find(itemID);
	if (it == m_items.end()) return;

	auto& stack = it->second;
	if (!stack.item->IsConsumable()) return;

	stack.item->Apply(target);
	stack.count--;

	if (stack.count <= 0)
		m_items.erase(it);
}

const std::unordered_map<int, ItemStack>& GetAllItems()
{
	return m_items;
}