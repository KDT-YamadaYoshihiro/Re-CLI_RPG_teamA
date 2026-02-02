#pragma once
#include <vector>
#include <unordered_set>

#include "Item/ItemManager/ItemManager.h"
#include "System/KeyInput/KeyInput.h"
#include "System/TextView/TextView.h"
#include "Item/ItemFactory/ItemFactory.h"
#include "Data/Character/CharacterBase.h"

struct ShopSlot
{
    ItemData data;
    bool sold = false;
};

class ShopSystem
{
private:
    Character& m_player;
    ItemManager& m_itemManager;

    std::vector<ShopSlot> m_slots;
    std::unordered_set<int> m_bannedRelics; // 購入済・排除済遺物

    int m_cursor = 0;
    bool m_exit = false;

public:

    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="player"></param>
    /// <param name="itemManager"></param>
    ShopSystem(Character& player, ItemManager& itemManager);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 終了チェック
    /// </summary>
    bool IsExit();

private:

    /// <summary>
    /// 購入可能枠の抽選
    /// </summary>
    void GenerateSlots();
    /// <summary>
    /// 描画
    /// </summary>
    void Render();
    /// <summary>
    /// 入力
    /// </summary>
    void UpdateInput();
    /// <summary>
    /// 購入処理
    /// </summary>
    void BuyCurrent();
};
