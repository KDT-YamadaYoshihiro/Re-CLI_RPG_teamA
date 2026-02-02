#include "ShopSysytem.h"

ShopSystem::ShopSystem(Character& player, ItemManager& itemManager)
    : m_player(player), m_itemManager(itemManager)
{
    GenerateSlots();
}

void ShopSystem::Update()
{
    Render();
    UpdateInput();
   
}

bool ShopSystem::IsExit()
{
    return m_exit;
}


void ShopSystem::GenerateSlots()
{
    m_slots.clear();

    const auto& table = ItemFactory::Instance().GetItemDataTable();

    // 抽選候補
    std::vector<ItemData> pool;
    for (const auto& pair : table)
    {
        const ItemData& data = pair.second;

        // 遺物で禁止されているものは除外
        if (!data.consumables && m_bannedRelics.count(data.id))
        {
            continue;
        }

        pool.push_back(data);
    }

    srand((unsigned int)time(nullptr));

    while (m_slots.size() < 5 && !pool.empty())
    {
        int index = rand() % pool.size();
        const ItemData& data = pool[index];

        // ラインナップ内で遺物重複防止
        bool duplicate = false;
        if (!data.consumables)
        {
            for (const auto& s : m_slots)
            {
                if (s.data.id == data.id)
                {
                    duplicate = true;
                    break;
                }
            }
        }

        if (duplicate)
        {
            pool.erase(pool.begin() + index);
            continue;
        }


        ShopSlot slot;
        slot.data = data;
        slot.sold = false;
        m_slots.push_back(slot);

        // 遺物は一意にするため抽選対象から外す
        if (!data.consumables)
        {
            pool.erase(pool.begin() + index);
        }

    }
}

void ShopSystem::Render()
{

    TextView::Instance().Add("=== ショップ ===\n");
    TextView::Instance().Add("所持金：" + std::to_string(m_itemManager.GetGold()) + " G\n\n");
    
    for (int i = 0; i < m_slots.size(); ++i)
    {
        const auto& slot = m_slots[i];

        std::string line;
        line += (i == m_cursor ? "> " : "  ");
        line += slot.data.name;

        if (slot.sold)
        {
            line += " [SOLD]";
        }

        line += "\n";
        TextView::Instance().Add(line);
    }

    TextView::Instance().Add("\n↑↓ 選択  Enter 購入  ESC 退出\n");
}

void ShopSystem::UpdateInput()
{
    KeyInput::Instance().Update();

    const int slotCount = static_cast<int>(m_slots.size());
    if (slotCount == 0)
    {
        if (KeyInput::Instance().ChechKey(KeyInput::ESC))
        {
            m_exit = true;
        }

        return;
    }

    if (KeyInput::Instance().ChechKey(KeyInput::UP))
    {
        m_cursor = (m_cursor - 1 + slotCount) % slotCount;
    }
    else if (KeyInput::Instance().ChechKey(KeyInput::DOWN))
    {
        m_cursor = (m_cursor + 1) % slotCount;
    }
    else if (KeyInput::Instance().ChechKey(KeyInput::ENTER))
    {
        BuyCurrent();
    }
    else if (KeyInput::Instance().ChechKey(KeyInput::ESC))
    {
        m_exit = true;
    }
}

void ShopSystem::BuyCurrent()
{
    auto& slot = m_slots[m_cursor];

    // 既所持の遺物は購入不可
    if (!slot.data.consumables && m_itemManager.GetAllItems().count(slot.data.id) > 0)
    {
        TextView::Instance().Add("その遺物は既に所持しています。\n");
        return;
    }

    int price = slot.data.price;

    // ゴールドチェック＆消費
    if (!m_itemManager.ConsumeGold(price))
    {
        TextView::Instance().Add("ゴールドが足りない！\n");
        return;
    }

    // アイテム付与
    m_itemManager.AddItem(slot.data.id, m_player);
    slot.sold = true;

    // 遺物は永久排除
    if (!slot.data.consumables)
    {
        m_bannedRelics.insert(slot.data.id);
    }

    TextView::Instance().Add(slot.data.name + "を購入した。\n""残りゴールド：" + std::to_string(m_itemManager.GetGold()) + " G\n");
}
