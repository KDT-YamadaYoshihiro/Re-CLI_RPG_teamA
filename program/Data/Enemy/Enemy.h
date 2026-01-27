#pragma once
#include "../Character/CharacterBase.h"

enum class EnemyAction
{
	action1,
	action2,
	action3,
};

class Enemy :public Character {
public:
	Character character;
	
};