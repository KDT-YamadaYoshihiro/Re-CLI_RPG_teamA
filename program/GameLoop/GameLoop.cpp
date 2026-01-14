#include "GameLoop.h"

void GameLoop::Run()
{
	Init();

	while (m_gameloop)
	{
		Update();
		Render();
	}

}

void GameLoop::Init()
{
}

void GameLoop::Update()
{
}

void GameLoop::Render()
{
}