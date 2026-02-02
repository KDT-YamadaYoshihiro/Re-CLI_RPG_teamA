#include "GameLoop.h"
#include "System/TextView/TextView.h"
#include "SceneManager/SceneManager.h"
#include "System/KeyInput/KeyInput.h"
#include <iostream>

void GameLoop::Run()
{
	Init();

	while (m_gameloop)
	{
		Update();
		Render();
	}

	End();
}

void GameLoop::Init()
{
	SceneManager::Instance().Init();
}

void GameLoop::Update()
{
	KeyInput::Instance().Update();
	SceneManager::Instance().Update();
}

void GameLoop::Render()
{
	SceneManager::Instance().Render();
}

void GameLoop::End()
{

}
