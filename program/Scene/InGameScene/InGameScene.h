#pragma once
#include "../SceneBase/SceneBase.h"

class InGameScene : public SceneBase
{
public:
	InGameScene();
	~InGameScene();

	bool Init() override;
	void Update() override;
	void Render() override;
};