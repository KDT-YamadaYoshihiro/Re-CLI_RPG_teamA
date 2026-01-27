#include "ItemBase.h"

void ItemBase::ItemEffect(std::unique_ptr<Character> arg_taget)
{
	switch (itemData.type)
	{
		case ItemType::Potion:
		{
			// HP回復
			arg_taget->HealHP(static_cast<int>(itemData.power));
			std::cout << itemData.name << "を使用した。HPが" << static_cast<int>(itemData.power) << "回復した。" << std::endl;
			break;
		}
		case ItemType::AttackPowerUp:
		{
			// 攻撃力アップ
			arg_taget->BuffAttackPower(itemData.power);
			std::cout << itemData.name << "を使用した。攻撃力が" << itemData.power << "上昇した。" << std::endl;
			break;
		}
		case ItemType::DefensePowerUp:
		{
			// 防御力アップ
			arg_taget->BuffDefensePower(itemData.power);
			std::cout << itemData.name << "を使用した。防御力が" << itemData.power << "上昇した。" << std::endl;
			break;
		}
		case ItemType::Relic_AttackPowerUp:
		{
			// 遺物の効果は別途実装
			arg_taget->BuffAttackPower(itemData.power);
			std::cout << itemData.name << "の効果を発動した。" << std::endl;
			break;
		}
		case ItemType::Relic_DefencePowerUp:
		{
			// 遺物の効果は別途実装
			arg_taget->BuffDefensePower(itemData.power);
			std::cout << itemData.name << "の効果を発動した。" << std::endl;
			break;
		}

	default:
		break;
	}
}
