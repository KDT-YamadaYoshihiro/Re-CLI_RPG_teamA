#include "Map.h"
#include "System/TextView/TextView.h"
#include "System/KeyInput/KeyInput.h"
#include<iostream>
#include <string>


void Map::DrawInfo(/* Playerと所持金*/)
{
	//// 描画するテキスト
	//std::string drawText = "";

	//// 左右が何のステージか
	//std::string upStr = ReturnStr(m_floorTable[m_currentFloor].Up);
	//std::string downStr = ReturnStr(m_floorTable[m_currentFloor].Down);


	////所持金: $$$
	////
	////player1 hp : 7 / 15
	////player2 hp : 22 / 40
	////player3 hp : 10 / 10

	//// テキストインスタンス取得
	//auto& text = TextView::Instance();

	//text.Add("次のステージ\n");

	//std::string stageText = std::to_string(SELECT_UP) + " " + upStr + " | " +
	//	std::to_string(SELECT_DOWN) + " " + downStr;
	//text.Add(stageText + "\n");

	auto& text = TextView::Instance();

	std::string upStr = ReturnStr(m_floorTable[m_currentFloor].Up);
	std::string downStr = ReturnStr(m_floorTable[m_currentFloor].Down);

	text.Add("=== STAGE " + std::to_string(m_currentFloor + 1) + " ===");
	text.Add("次の目的地を選択してください：");

	// カーソル位置に応じて表示を変える
	text.Add((m_cursor == 0 ? "> " : "  ") + upStr);
	text.Add((m_cursor == 1 ? "> " : "  ") + downStr);
}

SceneType Map::SelectScene()
{
	//// 入力インスタンス取得
	//auto& input = KeyInput::Instance();
	//// テキストインスタンス取得
	//auto& text = TextView::Instance();

	//int cursor = 0; // 0: UP, 1: DOWN
	//bool selected = false;

	//while (!selected)
	//{
	//	// 入力更新
	//	input.Update();

	//	// カーソル移動
	//	if (input.ChechKey(KeyInput::UP))   cursor = 0;
	//	if (input.ChechKey(KeyInput::DOWN)) cursor = 1;

	//	// 決定
	//	if (input.ChechKey(KeyInput::ENTER)) {
	//		selected = true;
	//		break; // ループを抜ける
	//	}

	//	std::string upStr = ReturnStr(m_floorTable[m_currentFloor].Up);
	//	std::string downStr = ReturnStr(m_floorTable[m_currentFloor].Down);

	//	text.Add("次のステージを選択してください：\n");

	//	// 選択中の方にカーソルを表示
	//	std::string display = (cursor == 0 ? "> " : "  ") + upStr + "\n" +
	//		(cursor == 1 ? "> " : "  ") + downStr + "\n";

	//	text.Add(display);
	//}

	//// 選択されたシーンを返す
	//// 入力させる数字とインデックスを合わせる
	//return ReturnScene(cursor);

	auto& input = KeyInput::Instance();

	// カーソル移動（入力があった時だけ状態更新）
	if (input.ChechKey(KeyInput::UP))   m_cursor = 0;
	if (input.ChechKey(KeyInput::DOWN)) m_cursor = 1;

	// 決定
	if (input.ChechKey(KeyInput::ENTER)) {
		return ReturnScene(m_cursor);
	}

	return SceneType::NONE;

}

SceneType Map::ReturnScene(int select)
{
    const auto& floor = m_floorTable[m_currentFloor];
    
    SceneType type = (select == 0) ? floor.Up : floor.Down;

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
