#include "GameLoop.h"

void GameLoop::Run()
{

	while (m_gameloop)
	{
		Init();
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