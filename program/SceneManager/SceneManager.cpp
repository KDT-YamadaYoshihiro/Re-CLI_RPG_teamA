#include "SceneManager.h"
#include "../Scene/TitleScene/TitleScene.h"

SceneManager::SceneManager()
{
    //ChangeScene<TitleScene>();
}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init()
{

    // 初期シーンがあれば初期化
    if (m_currentScene) {
        return m_currentScene->Init();
    }
    return true;
}

void SceneManager::Update()
{
    // シーン切り替え処理
    if (m_nextScene) {
        m_currentScene = std::move(m_nextScene);
        m_nextScene = nullptr;
        if (m_currentScene) {
            m_currentScene->Init();
        }
    }

    // 現在のシーンを更新
    if (m_currentScene) {
        m_currentScene->Update();
    }
}

void SceneManager::Render()
{
    // 現在のシーンを描画
    if (m_currentScene) {
        m_currentScene->Render();
    }
}