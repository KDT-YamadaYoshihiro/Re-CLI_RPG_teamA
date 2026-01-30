#include "ItemManager.h"
#include "../ItemFactory/ItemFactory.h"

void ItemManager::AddItem(int itemID, Character& owner)
{
    auto item = ItemFactory::Instance().CreateItem(itemID);
    if (!item)
    {
        return;
    }

    // 消費型
    if (item->IsConsumable())
    {
        auto& stack = m_items[itemID];

        if (stack.count == 0)
        {
            stack.item = item;
        }

        stack.count++;
        return;
    }

    // 遺物 
    // すでに所持しているなら追加しない
    if (m_items.find(itemID) != m_items.end())
    {
        return;
    }


    ItemStack stack;
    stack.item = item;
    stack.count = 1;

    m_items.emplace(itemID, stack);

    // 遺物は取得時に即効果
    item->OnAcquire(owner);
}

void ItemManager::UseItem(int itemID, Character& target)
{
	auto it = m_items.find(itemID);
	if (it == m_items.end())
	{
		return;
	}

	auto& stack = it->second;
	// 消費型の判定
	if (!stack.item->IsConsumable())
	{
		return;
	}

    // アイテムの使用
	stack.item->Apply(target);
    // 所持数-1
	stack.count--;

    // 所持数0なら要素削除
	if (stack.count <= 0)
	{
		m_items.erase(it);
	}
}


const std::unordered_map<int, ItemStack>& ItemManager::GetAllItems()
{
	return m_items;
}
