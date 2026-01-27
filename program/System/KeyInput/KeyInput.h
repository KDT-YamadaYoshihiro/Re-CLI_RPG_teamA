#pragma once
#include <conio.h>

class KeyInput {


public:

	enum KeyType{
		NONE,
		UP,DOWN,LEFT,RIGHT,
		ENTER,ESC,SPACE
	};

	void Update() {
		curentKey = NONE;
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 0 or ch == 224) {
				ch = _getch();
				switch (ch){
				// 方向キー
				case 72: curentKey =  UP  ; break;
				case 80: curentKey = DOWN ; break;
				case 75: curentKey = LEFT ; break;
				case 77: curentKey = RIGHT; break;
				// 選択用のキー
				case 13: curentKey = ENTER; break; 
				case 27: curentKey = ESC;   break;
				case 32: curentkey = SPACE; break;
				}
			}
		}
	}

	KeyType GetKey() { return curentKey; }
	bool ChechKey(KeyType key)
	{
		if (key == curentKey)
		{
			return true;
		}
		return false;
	}

private:

	KeyType curentKey = KeyType::NONE;
};