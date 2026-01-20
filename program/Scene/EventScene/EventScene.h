#pragma once
#include "../SceneBase/SceneBase.h"

class EventScene : public SceneBase
{

	EventScene(int floor);
	~EventScene();

	bool Init() override;
	void Update() override;
	void Render() override;


};