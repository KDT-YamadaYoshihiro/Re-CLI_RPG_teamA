#include "WastageItem.h"  
#include "../../Data/Character/CharacterBase.h" // Character クラスの完全な定義を含むヘッダーをインクルード  

WastageItem::WastageItem(const ItemData& arg_data) : ItemBase(arg_data) 
{

}

void WastageItem::Apply(Character& target)  
{  
   switch (itemData.type)  
   {  
   case ItemType::Potion:  
       target.Heal(itemData.power);  
       break;  

   case ItemType::AttackPowerUp:  
       target.BuffAttackPower(itemData.power);  
       break;  

   case ItemType::DefensePowerUp:  
       target.BuffDefensePower(itemData.power);  
       break;  
   }  
}