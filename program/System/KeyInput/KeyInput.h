#pragma once
#include <conio.h>

class KeyInput : public Singleton<KeyInput>
{
	friend class Singleton<KeyInput>;

	KeyInput() = default;
	virtual ~KeyInput() = default;

public:

	enum KeyType{
		NONE,
		UP,DOWN,LEFT,RIGHT,
		ENTER,ESC,SPACE
	};

	void Update() {
		currentKey = NONE;
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 0 or ch == 224) {
				ch = _getch();
				switch (ch){
				// 方向キー
				case 72: currentKey =  UP  ; break;
				case 80: currentKey = DOWN ; break;
				case 75: currentKey = LEFT ; break;
				case 77: currentKey = RIGHT; break;
				// 選択用のキー
				case 13: currentKey = ENTER; break; 
				case 27: currentKey = ESC;   break;
				case 32: currentKey = SPACE; break;
				}
			}
		}
	}

	KeyType GetKey() { return currentKey; }
	bool ChechKey(KeyType key)
	{
		if (key == currentKey)
		{
			return true;
		}
		return false;
	}

private:

	KeyType currentKey = KeyType::NONE;
};