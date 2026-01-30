#include "WastageItem.h"  
#include "../../Data/Character/CharacterBase.h" // Character クラスの完全な定義を含むヘッダーをインクルード  
#include "../../System/TextView/TextView.h"

WastageItem::WastageItem(const ItemData& arg_data) : ItemBase(arg_data) 
{

}

void WastageItem::Apply(Character& target)  
{  
   switch (itemData.type)  
   {  
   case ItemType::Potion:  
       target.Heal(itemData.power);  
       TextView::Instance().Add(itemData.name + "を使用した。\n" + target.GetState().name + "のHPが" + std::to_string(itemData.power) + "回復した。\n");
       TextView::Instance().Add(std::to_string(target.GetState().hp) + "/" + std::to_string(target.GetState().MaxHP) + "\n");
       break;  

   case ItemType::AttackPowerUp:  
       target.BuffAttackPower(itemData.power);  
       TextView::Instance().Add(itemData.name + "を使用した。\n" + target.GetState().name + "の攻撃力が" + std::to_string(itemData.power) + "上昇した。\n");
       TextView::Instance().Add(std::to_string(target.GetState().ATK) + "\n");
       break;  

   case ItemType::DefensePowerUp:  
       target.BuffDefensePower(itemData.power); 
       TextView::Instance().Add(itemData.name + "を使用した。\n" + target.GetState().name + "の防御力が" + std::to_string(itemData.power) + "上昇した。\n");
       TextView::Instance().Add(std::to_string(target.GetState().DEF) + "\n");
       break;  
   }  
}