#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "../ItemBase.h"

/*
* 
* #include ""	消耗Item
* #include ""	遺物
*
*/

// 所持アイテム管理
class ItemManager
{
private:

	// Item所持管理をunordered_mapで行う
	std::unordered_map<int, std::shared_ptr<ItemBase>> m_itemMap;

public:

	// Itemの破棄（使用）
	void UseItem(int itemID);
	// 全所持Item情報の取得（*n単位表示で）
	void GetAllItemInfo();
	// 指定Item情報の取得
	std::shared_ptr<ItemBase> GetItemInfo(int itemID);	//　参照渡し（itemBaseのポインタ）
};

