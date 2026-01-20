#include "Map.h"
#include<iostream>

void Map::DrawPlayerInfo(/* Player */)
{
	//所持金: $$$
	//
	//player1 hp : 7 / 15
	//player2 hp : 22 / 40
	//player3 hp : 10 / 10

	std::string leftStr = ReturnStr(FloorTable[currentFloor].Left);
	std::string rightStr = ReturnStr(FloorTable[currentFloor].Right);

	std::printf("次のステージ");
	std::printf("1 %s | 2 %s", leftStr, rightStr);
}

SceneType Map::SelectScene()
{
	int select;

	while (true)
	{
		std::cin >> select;

		if (select == 1 || select == 2)
		{
			break;
		}

		std::printf("無効な入力です");
	}

	// 選択されたシーンを返す
	// 入力とインデックスを合わせる
	return ReturnScene(select - 1);
}

SceneType Map::ReturnScene(int select)
{
	const auto& floor = FloorTable[currentFloor];

	SceneType type = SceneType::NONE;

	if (select == 0)
	{
		type = floor.Left;
	}
	else
	{
		type = floor.Right;
	}

	// 階層を増やす
	currentFloor++;

	return type;
}

std::string Map::ReturnStr(SceneType type)
{

	std::string nextStr = "無効なシーン";

	switch (type)
	{
	case SceneType::Battle:
		nextStr = "戦闘";
		return nextStr;

	case SceneType::Shop:
		nextStr = "ショップ";
		return nextStr;

	case SceneType::Event:
		nextStr = "イベント";
		return nextStr;

	case SceneType::Boss:
		nextStr = "ボス";
		return nextStr;

	default:
		return;
	}
}
