#include "Data/Enemy/EnemyDataBase.h"
#include "Data/Character/CharacterBase.h"
#include "EnemyFactory.h"

std::unique_ptr<Character>
EnemyFactory::CreateEnemy(const std::string& enemyID)
{
	const EnemyData& data = EnemyDataBase::Get(enemyID);

	Status sta;
	
	sta.name = data.name;
	sta.faction = Faction::Enemy;
	sta.isLife = true;

	sta.MaxHP = data.MaxHP;
	sta.hp = data.MaxHP;
	sta.ATK = data.ATK;
	sta.DEF = data.DEF;
	sta.INT = data.INT;
	sta.MND = data.MND;
	sta.speed = data.speed;

	
	return std::make_unique<Character>(sta);
}