#include "Map.h"
#include "../TextView/TextView.h"
#include<iostream>

void Map::DrawInfo(/* Playerと所持金*/)
{
	auto text = &TextView::GetInstance();
	
	// 描画するテキスト
	std::string drawText = "";

	// 左右が何のステージか
	std::string leftStr = ReturnStr(m_floorTable[ m_currentFloor].Left);
	std::string rightStr = ReturnStr(m_floorTable[m_currentFloor].Right);


	//所持金: $$$
	//
	//player1 hp : 7 / 15
	//player2 hp : 22 / 40
	//player3 hp : 10 / 10


	drawText = "次のステージ";
	text->AddText(drawText);

	drawText = "1 %s | 2 %s", leftStr.c_str(), rightStr.c_str();
	text->AddText(drawText);
}

SceneType Map::SelectScene()
{
	auto text = &TextView::GetInstance();


	int select;

	while (true)
	{
		std::cin >> select;

		if (select == 1 || select == 2)
		{
			break;
		}

		text->AddText("無効な入力です");
	}

	// 選択されたシーンを返す
	// 入力とインデックスを合わせる
	return ReturnScene(select - 1);
}

SceneType Map::ReturnScene(int select)
{
	const auto& floor = m_floorTable[m_currentFloor];

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
	m_currentFloor++;

	return type;
}

std::string Map::ReturnStr(SceneType type)
{

	std::string nextStr = "無効なシーン";

	switch (type)
	{
	case SceneType::BATTLE:
		nextStr = "戦闘";
		return nextStr;

	case SceneType::SHOP:
		nextStr = "ショップ";
		return nextStr;

	case SceneType::EVENT:
		nextStr = "イベント";
		return nextStr;

	case SceneType::BOSS:
		nextStr = "ボス";
		return nextStr;

	default:
		return nextStr;
	}
}
