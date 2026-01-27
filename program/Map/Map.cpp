#include "Map.h"
#include "../TextView/TextView.h"
#include<iostream>

#include <string>

void Map::DrawInfo(/* Playerと所持金*/)
{

	// 描画するテキスト
	std::string drawText = "";

	// 左右が何のステージか
	std::string leftStr = ReturnStr(m_floorTable[m_currentFloor].Left);
	std::string rightStr = ReturnStr(m_floorTable[m_currentFloor].Right);


	//所持金: $$$
	//
	//player1 hp : 7 / 15
	//player2 hp : 22 / 40
	//player3 hp : 10 / 10

	// テキストインスタンス取得
	auto text = &TextView::GetInstance();

	text->AddText("次のステージ\n");

	std::string stageText = std::to_string(SELECT_LEFT) + " " + leftStr + " | " +
		std::to_string(SELECT_RIGHT) + " " + rightStr;
	text->AddText(stageText + "\n");

	text->TextRender();
	text->ResetText();
}

SceneType Map::SelectScene()
{
	int select;

	// テキストインスタンス取得
	auto text = &TextView::GetInstance();

	while (true)
	{
		std::cin >> select;

		if (select == SELECT_LEFT || select == SELECT_RIGHT)
		{
			break;
		}

		text->AddText("無効な入力です\n");
		text->TextRender();
		text->ResetText();
	}

	// 選択されたシーンを返す
	// 入力させる数字とインデックスを合わせる
	return ReturnScene(select - INDEX_OFFSET);
}

SceneType Map::ReturnScene(int select)
{
	// 現在の階の選択肢を取得
	const auto& floor = m_floorTable[m_currentFloor];

	const int LEFT_INDEX = 0;

	// 選択されたシーンを取得
	SceneType type = (select == LEFT_INDEX) ? floor.Left : floor.Right;

	// 階層を進める
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
