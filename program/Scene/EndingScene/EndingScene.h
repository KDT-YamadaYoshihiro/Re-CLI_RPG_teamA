#pragma once
#include "../SceneBase/SceneBase.h"

class EndingScene : public SceneBase
{
public:
	EndingScene(int floor);
	~EndingScene();

	bool Init() override;
    void Update() override;
	void Render() override;
};

