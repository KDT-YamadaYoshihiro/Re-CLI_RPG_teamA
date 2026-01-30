#include "PlayerFactory.h"
#include "../../Character/CharacterBase.h"
#include "../PlayerDataBase.h"

std::unique_ptr<Character>
PlayerFactory::CreatePlayer(const std::string& playerID)
{
	const PlayerData& data = PlayerDataBase::Get(playerID);

	Status sta;

	sta.name = data.name;
	sta.faction = Faction::Player;
	sta.isLife = true;

	sta.MaxHP = data.MaxHP;
	sta.hp = data.MaxHP;
	sta.ATK = data.ATK;
	sta.DEF = data.DEF;
	sta.INT = data.INT;
	sta.MND = data.MND;
	sta.speed = data.speed;


	return std::make_unique<Character>(
		sta
	);
}