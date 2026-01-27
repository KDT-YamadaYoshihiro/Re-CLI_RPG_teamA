#pragma once
#include <memory>
#include "../Scene/SceneBase/SceneBase.h"
#include "../Singleton/Singleton.h"

// シーン管理するクラス
// シングルトンを継承してシングルトンにしてます。
class SceneManager : public Singleton<SceneManager> {
	// 継承してする場合 friend class にすることで
	// private や protectedメンバ変数にアクセスできるようにする
	friend class Singleton<SceneManager>;
private:
	std::unique_ptr<SceneBase> m_currentScene;	// 現在のシーン
	std::unique_ptr<SceneBase> m_nextScene;		// 次のシーン
public:
	SceneManager();
	~SceneManager();
	// シーンの変更
	template <typename T, typename... Args>
	void ChangeScene(Args&&... args) {
		// std::forward テンプレート関数の引数を元の値カテゴリを保ったまま別の関数に渡す
		m_nextScene = std::make_unique<T>(std::forward<Args>(args)...);
	}
	bool Init();
	void Update();
	void Render();
};


