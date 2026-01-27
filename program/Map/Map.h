#pragma once
#include <array>
#include <string>

enum class SceneType
{
	BATTLE,
	SHOP,
	EVENT,
	BOSS,
	NONE,
};

struct FloorChoice
{
	SceneType Up;
	SceneType Down;
};

class Map
{
public:

	/// <summary>
	/// 情報を出力
	/// </summary>
	void DrawInfo(/* Playerと所持金*/);

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
	/// <summary>
	/// ステージを文字列に変更
	/// <summary>
	std::string ReturnStr(SceneType type);

	// 現在の階層
	int m_currentFloor = 0;

	static constexpr int STAGE_MAX = 10;		// 最大ステージ数
	static constexpr int SELECT_UP = 1;			// 入力値：上
	static constexpr int SELECT_DOWN = 2;		// 入力値：下
	static constexpr int INDEX_OFFSET = 1;		// 入力値と配列添字の差分

	std::array<FloorChoice, STAGE_MAX> m_floorTable = { {
	{ SceneType::BATTLE, SceneType::SHOP },		// 1階
	{ SceneType::BATTLE, SceneType::BATTLE },	// 2階
	{ SceneType::BATTLE, SceneType::EVENT },	// 3階
	{ SceneType::SHOP,   SceneType::EVENT },	// 4階
	{ SceneType::BATTLE, SceneType::BATTLE },	// 5階
	{ SceneType::EVENT,  SceneType::SHOP },		// 6階
	{ SceneType::BATTLE, SceneType::EVENT },	// 7階
	{ SceneType::BATTLE, SceneType::BATTLE },	// 8階
	{ SceneType::SHOP,   SceneType::EVENT },	// 9階
	{ SceneType::BOSS,   SceneType::BOSS },		// 10階
}   };
};