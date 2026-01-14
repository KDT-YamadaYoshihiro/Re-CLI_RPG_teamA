#pragma once

class GameLoop
{

	// ゲームループ判定
	bool m_gameloop = true;

	GameLoop() = default;
	virtual ~GameLoop() = default;

public:

	GameLoop(const GameLoop&) = delete;
	GameLoop& operator = (const GameLoop&) = delete;

	static GameLoop& GetInstance()
	{
		static GameLoop instance;
		return instance;
	}

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

