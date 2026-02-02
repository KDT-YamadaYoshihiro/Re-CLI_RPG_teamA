#pragma once
#include <conio.h>
#include "Singleton/Singleton.h"

class KeyInput : public Singleton<KeyInput>
{
	friend class Singleton<KeyInput>;

	template <typename U> friend class Singleton;

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
			if (ch == 0 || ch == 224) {
				ch = _getch(); // 2バイト目を読み込む
				switch (ch) {
				case 72: currentKey = UP;    break;
				case 80: currentKey = DOWN;  break;
				case 75: currentKey = LEFT;  break;
				case 77: currentKey = RIGHT; break;
				}
			}
			// 2. 特殊キーでない通常のキーを判定
			else {
				switch (ch) {
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