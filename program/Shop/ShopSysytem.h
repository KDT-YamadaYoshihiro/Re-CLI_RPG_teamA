#pragma once
#include <vector>
#include <unordered_set>

#include "../Item/ItemManager/ItemManager.h"
#include "../System/KeyInput/KeyInput.h"
#include "../System/TextView/TextView.h"
#include "../Item/ItemFactory/ItemFactory.h"
#include "../Data/Character/CharacterBase.h"

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
    std::unordered_set<int> m_bannedRelics; // w“üÏE”rœÏˆâ•¨

    int m_cursor = 0;
    bool m_exit = false;

public:

    /// <summary>
    /// ‰Šú‰»
    /// </summary>
    /// <param name="player"></param>
    /// <param name="itemManager"></param>
    ShopSystem(Character& player, ItemManager& itemManager);

    /// <summary>
    /// XV
    /// </summary>
    void Update();


private:

    /// <summary>
    /// w“ü‰Â”\˜g‚Ì’Š‘I
    /// </summary>
    void GenerateSlots();
    /// <summary>
    /// •`‰æ
    /// </summary>
    void Render();
    /// <summary>
    /// “ü—Í
    /// </summary>
    void UpdateInput();
    /// <summary>
    /// w“üˆ—
    /// </summary>
    void BuyCurrent();
};
