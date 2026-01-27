#pragma once
#include <string>

enum class Faction {
	Player,
	Enemy
};

struct Status {
	std::string name;

	Faction faction;

	bool isLife = true;

	int ID;
	int MaxHP = 50;
	int hp = MaxHP;

	int ATK;
	int DEF;
	int INT;
	int MND;

	int actionPoint;
	int speed;
	int actionValue;
};



class Character {
protected:
	Status state;

public:

	Character(Status baseStatas) :state(baseStatas){}

	virtual ~Character(){}

	/// <summary>
	/// ファクションゲッター
	/// </summary>
	/// <returns></returns>
	Faction GetFaction()const { return state.faction; }

	const Status& GetState()const { return state; }

	bool IsLife() { return state.isLife; }

	void TakeDamage(int damage) {
		if (damage < 0)damage = 0;
		state.hp -= damage;
		if (state.hp < 0)
		{
			state.hp = 0;
			state.isLife = false;
		}
	}

	void Heal(int value)
	{
		if (value < 0) { return; }
		state.hp += value;
		if (state.hp > state.MaxHP) {
			state.hp = state.MaxHP;
		}
	}
};