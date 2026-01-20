#pragma once
#include "../SceneBase/SceneBase.h"

class BattleScene : public SceneBase
{
public:
	BattleScene(int floor);
	~BattleScene();

	bool Init() override;
	void Update() override;
	void Render() override;
};