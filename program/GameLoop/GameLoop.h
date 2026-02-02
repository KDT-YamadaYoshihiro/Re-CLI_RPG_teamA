#pragma once
#include "Singleton/Singleton.h"

class GameLoop: public Singleton<GameLoop>
{

	friend class Singleton<GameLoop>;


	GameLoop() = default;
	virtual ~GameLoop() = default;

	// ゲームループ判定
	bool m_gameloop = true;

public:


	// 全体更新
	void Run();

	// ゲームループの終了
	void EndGameLoop() { m_gameloop = false; }

private:

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Render();
	// 終了
	void End();

};

