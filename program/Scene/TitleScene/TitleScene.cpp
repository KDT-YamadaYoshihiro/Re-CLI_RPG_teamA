#include "TitleScene.h"
#include "SceneManager/SceneManager.h"
#include "System/TextView/TextView.h"
#include "System/KeyInput/KeyInput.h"
#include "Scene/InGameScene/InGameScene.h"
TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

bool TitleScene::Init()
{
	return true;
}

void TitleScene::Update()
{
	KeyInput::Instance().Update();

	if (KeyInput::Instance().ChechKey(KeyInput::ENTER))
	{
		TextView::Instance().Reset();
		SceneManager::Instance().ChangeScene<InGameScene>();
	}

}

void TitleScene::Render()
{
	TextView::Instance().Add(
		"======CLI_RPG!!======\n"
		"===SPACEtoスタート===\n");
	TextView::Instance().RenderFrame();

}