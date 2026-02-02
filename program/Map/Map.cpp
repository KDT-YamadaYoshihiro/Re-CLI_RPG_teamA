#include "Map.h"
#include "System/TextView/TextView.h"
#include "System/KeyInput/KeyInput.h"
#include "SceneManager/SceneManager.h"
#include "Scene/EndingScene/EndingScene.h"
#include<iostream>
#include <string>


void Map::DrawInfo(/* Playerと所持金*/)
{

	auto& text = TextView::Instance();

	// クリア済みなら表示をスキップ
	if (m_isCleared) {
		text.Add("=== 全階層踏破！ ===");
		return;
	}

	if (m_currentFloor >= STAGE_MAX) return;

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
	// 現在の階層のデータを取得
	const auto& floor = m_floorTable[m_currentFloor];
	SceneType type = (select == 0) ? floor.Up : floor.Down;

	// 10階層（BOSS）を終えたらクリアフラグを立てる
	if (m_currentFloor >= STAGE_MAX) {
		m_isCleared = true;
	}
	else
	{
		// 階層を進める
		m_currentFloor++;
	}

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

	case SceneType::BOSS:
		nextStr = "ボス";
		return nextStr;

	default:
		return nextStr;
	}
}
