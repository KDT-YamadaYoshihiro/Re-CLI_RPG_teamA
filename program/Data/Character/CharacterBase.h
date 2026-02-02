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
	int MaxHP=1;
	int hp = MaxHP;

	int ATK;
	int DEF;
	int INT;
	int MND;

	int actionPoint=0;
	int speed;
	int actionValue=0;
};



class Character {
protected:
	Status state;

public:

	Character(Status baseStatas) :state(baseStatas){}
	// 仮想デストラクタ
	virtual ~Character(){}
	

	/// <summary>
	/// ファクションゲッター
	/// </summary>
	/// <returns></returns>
	Faction GetFaction()const { return state.faction; }

	const Status& GetState()const { return state; }
	void SetActionPoint(int arg_point) { state.actionPoint = arg_point; }

	// 生死判定ゲッター
	const bool IsLife()const { return state.isLife; }

	// 体力減算処理
	void TakeDamage(int damage) {
		if (damage < 0)damage = 0;
		state.hp -= damage;
		if (state.hp < 0)
		{
			state.hp = 0;
			state.isLife = false;
		}
	}

	// 回復
	void Heal(int value)
	{
		if (value < 0) { return; }
		state.hp += value;
		if (state.hp > state.MaxHP) {
			state.hp = state.MaxHP;
		}
	}

	// 攻撃力永続バフ
	void BuffAttackPower(int value) 
	{
		state.ATK += value;
	}

	// 防御力永続バフ
	void BuffDefensePower(int value)
	{
		state.DEF += value;
	}
};