#include "GameLoop.h"
#include "../System/TextView/TextView.h"
#include "../SceneManager/SceneManager.h"
#include "../System/KeyInput/KeyInput.h"
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
	TextView::Instance().AddText("Game Init");
	SceneManager::Instance().Init();
}

void GameLoop::Update()
{
	KeyInput::Instance().Update();

	TextView::Instance().AddText("Game Update");
	SceneManager::Instance().Update();

	std::cin.get();
}

void GameLoop::Render()
{
	TextView::Instance().AddText("Game Render");
	SceneManager::Instance().Render();
}

void GameLoop::End()
{
	TextView::Instance().AddText("Game End");

}
