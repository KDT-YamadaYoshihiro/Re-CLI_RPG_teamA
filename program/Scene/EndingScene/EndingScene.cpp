#include "EndingScene.h"
#include "System/TextView/TextView.h"
#include "System/KeyInput/KeyInput.h"
#include "SceneManager/SceneManager.h"
#include "Scene/TitleScene/TitleScene.h"

EndingScene::EndingScene()
{
}

EndingScene::~EndingScene()
{

}

bool EndingScene::Init()
{
	return true;
}

void EndingScene::Update()
{

	// タイトルへ戻る
	if (KeyInput::Instance().ChechKey(KeyInput::ENTER))
	{
		SceneManager::Instance().ChangeScene<TitleScene>();
	}
}

void EndingScene::Render()
{
	TextView::Instance().Add("=== ダンジョン踏破！===");
	TextView::Instance().Add("==== ゲームクリア！====\n");
	TextView::Instance().Add("～ Enterでタイトルへ ～");

	TextView::Instance().RenderFrame();
}