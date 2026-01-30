#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "../ItemBase.h"

// アイテムスタック構造体
struct ItemStack
{
	std::shared_ptr<ItemBase> item;
	int count = 0;
};

// 所持アイテム管理
class ItemManager
{
private:

	// Item所持管理をunordered_mapで行う
	std::unordered_map<int, std::shared_ptr<ItemBase>> m_itemMap;

public:
	void AddItem(int itemID, Character& owner);
	void UseItem(int itemID, Character& target);
};

