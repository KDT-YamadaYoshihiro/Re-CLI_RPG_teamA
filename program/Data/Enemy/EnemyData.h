#pragma once
#include "../Character/CharacterBase.h"

struct EnemyState :public Status {
	int dropGold;
};

struct EnemyData
{
	EnemyState enemyState;
	int dropGold;
};