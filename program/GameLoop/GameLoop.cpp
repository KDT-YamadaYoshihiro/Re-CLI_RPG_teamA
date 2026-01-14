#include "GameLoop.h"
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
	std::cout << "Game Init" << std::endl;
}

void GameLoop::Update()
{
	std::cout << "Game Update" << std::endl;
}

void GameLoop::Render()
{
	std::cout << "Game Render" << std::endl;
}

void GameLoop::End()
{
	std::cout << "Game End" << std::endl;
}
