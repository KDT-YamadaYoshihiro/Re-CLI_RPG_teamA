#include "RelicItem.h"
#include "../../Data/Character/CharacterBase.h"

void RelicItem::OnAcquire(Character& target)
{
	switch (itemData.type)
	{
	case ItemType::Relic_AttackPowerUp:
		target.BuffAttackPower(itemData.power);
		break;

	case ItemType::Relic_DefencePowerUp:
		target.BuffDefensePower(itemData.power);
		break;
	}
}

void RelicItem::OnRemove(Character& target)
{
	switch (itemData.type)
	{
	case ItemType::Relic_AttackPowerUp:
		target.BuffAttackPower(-itemData.power);
		break;

	case ItemType::Relic_DefencePowerUp:
		target.BuffDefensePower(-itemData.power);
		break;
	}
}