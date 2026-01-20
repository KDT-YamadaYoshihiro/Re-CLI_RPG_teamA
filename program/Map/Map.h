#pragma once
#include <array>
#include <string>

enum class SceneType
{
	Battle,
	Shop,
	Event,
	Boss,
	NONE,
};

struct FloorChoice
{
	SceneType Left;
	SceneType Right;
};

class Map
{
	/// <summary>
	/// プレイヤーの情報を出力
	/// </summary>
	void DrawPlayerInfo();

	/// <summary>
	/// 次のシーンを選択
	/// </summary>
	SceneType SelectScene();

	/// <summary>
	/// 次のシーンを返す
	/// </summary>
	/// <returns>次のシーンのタイプ</returns>
	SceneType ReturnScene(int select);

private:

	std::string ReturnStr(SceneType type);

	// 現在の階層
	int currentFloor = 0;

	// 最大ステージ数
	static constexpr int STAGE_MAX = 10;

	std::array<FloorChoice, STAGE_MAX> FloorTable = { {
	{ SceneType::Battle, SceneType::Shop },		// 1階
	{ SceneType::Battle, SceneType::Battle },	// 2階
	{ SceneType::Battle, SceneType::Event },	// 3階
	{ SceneType::Shop,   SceneType::Event },	// 4階
	{ SceneType::Battle, SceneType::Battle },	// 5階
	{ SceneType::Event,  SceneType::Shop },		// 6階
	{ SceneType::Battle, SceneType::Event },	// 7階
	{ SceneType::Battle, SceneType::Battle },	// 8階
	{ SceneType::Shop,   SceneType::Event },	// 9階
	{ SceneType::Boss,   SceneType::Boss },		// 10階
}   };
};