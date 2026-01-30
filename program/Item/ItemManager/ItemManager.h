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
	std::unordered_map<int, ItemStack> m_items;

public:

	/// <summary>
	/// アイテムの追加
	/// </summary>
	/// <param name="itemID"></param>
	/// <param name="owner"></param>
	void AddItem(int itemID, Character& owner);

	/// <summary>
	/// アイテムの使用
	/// </summary>
	/// <param name="itemID"></param>
	/// <param name="target"></param>
	void UseItem(int itemID, Character& target);

	/// <summary>
	/// 所持しているアイテムすべて
	/// </summary>
	/// <returns></returns>
	const std::unordered_map<int, ItemStack>& GetAllItems();

	/// <summary>
	/// お金の取得
	/// </summary>
	/// <returns></returns>
	int GetGold() const;

	/// <summary>
	/// お金の消費
	/// </summary>
	/// <param name="amount"></param>
	/// <returns></returns>
	bool ConsumeGold(int amount);

	/// <summary>
	/// お金の取得
	/// </summary>
	/// <param name="amount"></param>
	void AddGold(int amount);

};

