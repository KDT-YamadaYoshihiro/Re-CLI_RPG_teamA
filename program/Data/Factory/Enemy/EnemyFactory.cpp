#include "EnemyFactory.h"
#include "../../Enemy/EnemyDataBase.h"

std::unique_ptr<Character>
EnemyFactory::CreateEnemy(const std::string& enemyId) {
	const EnemyData& data = EnemyDataBase::Get(enemyId);
	Status sta;

	sta.ID = data.enemyState.ID;
	sta.faction = Faction::Enemy;
	sta.isLife = true;

	sta.MaxHP = data.enemyState.MaxHP;
	sta.hp = data.enemyState.MaxHP;

	sta.ATK = data.enemyState.ATK;
	sta.DEF = data.enemyState.DEF;
	sta.INT = data.enemyState.INT;
	sta.MND = data.enemyState.MND;
	
	return;
}