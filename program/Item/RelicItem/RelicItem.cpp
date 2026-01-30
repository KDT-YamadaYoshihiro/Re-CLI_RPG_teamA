#include "RelicItem.h"
#include "../../Data/Character/CharacterBase.h"
#include "../../System/TextView/TextView.h"

void RelicItem::OnAcquire(Character& target)
{
	switch (itemData.type)
	{
	case ItemType::Relic_AttackPowerUp:
		target.BuffAttackPower(itemData.power);
		TextView::Instance().Add(itemData.name + "‚ÌŒø‰Ê”­“®\n" + target.GetState().name + "‚ÌUŒ‚—Í‚ª" + std::to_string(itemData.power) + "ã¸‚µ‚½B\n");
		TextView::Instance().Add(std::to_string(target.GetState().ATK) + "\n");
		break;

	case ItemType::Relic_DefencePowerUp:
		target.BuffDefensePower(itemData.power);
		TextView::Instance().Add(itemData.name + "‚ÌŒø‰Ê”­“®B\n" + target.GetState().name + "‚Ì–hŒä—Í‚ª" + std::to_string(itemData.power) + "ã¸‚µ‚½B\n");
		TextView::Instance().Add(std::to_string(target.GetState().DEF) + "\n");

		break;
	}
}

void RelicItem::OnRemove(Character& target)
{
	switch (itemData.type)
	{
	case ItemType::Relic_AttackPowerUp:
		target.BuffAttackPower(-itemData.power);
		TextView::Instance().Add(itemData.name + "‚ÌŒø‰Ê‰ğœ\n" + target.GetState().name + "‚ÌUŒ‚—Í‚ª" + std::to_string(itemData.power) + "Œ¸­‚µ‚½B\n");
		TextView::Instance().Add(std::to_string(target.GetState().ATK) + "\n");

		break;

	case ItemType::Relic_DefencePowerUp:
		target.BuffDefensePower(-itemData.power);
		TextView::Instance().Add(itemData.name + "‚ÌŒø‰Ê‰ğœ\n" + target.GetState().name + "‚Ì–hŒä—Í‚ª" + std::to_string(itemData.power) + "Œ¸­‚µ‚½B\n");
		TextView::Instance().Add(std::to_string(target.GetState().DEF) + "\n");

		break;
	}
}