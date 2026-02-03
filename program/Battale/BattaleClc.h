#pragma once

// ここではバトルで使う計算系の処理のみ
class BattaleClc {

private:

#define ActionBase 10000

public:

	// 物理攻撃の計算
	int ClcDamage(int arg_ATK, int arg_DEF) {

		// 計算後の攻撃力
		int After_ATK = arg_ATK / 2;

		// 計算後の防御力
		int After_DEF = arg_DEF / 4;

		int Dmage_AD = After_ATK - After_DEF;

		if( Dmage_AD < 1) {
			Dmage_AD = 1;
		}
		return Dmage_AD;
	}

	// 魔法攻撃の計算
	int ClcMGCDamage(int arg_INT, int arg_MND) {

		// 計算後の魔法攻撃力
		int After_INT = arg_INT / 2;

		// 計算後の魔法攻撃力
		int After_MND = arg_MND / 4;

		int Dmage_AP = After_INT - After_MND;

		if ( Dmage_AP < 1) {
			Dmage_AP = 1;
		}
		return Dmage_AP;
	}

	//// 速度計算
	//void AddSpeed(int& ActionPoint,int arg_speed,int ActionValue) {

	//	// キャラクターの行動ポイントを増やす
	//	ActionPoint = ActionPoint + arg_speed;

	//	// 行動値を出す
	//	ActionValue = (ActionBase - ActionPoint) / arg_speed;
	//}

	int AddSpeed(int actionPoint, int arg_speed)
	{
		return actionPoint += arg_speed;
	}
};