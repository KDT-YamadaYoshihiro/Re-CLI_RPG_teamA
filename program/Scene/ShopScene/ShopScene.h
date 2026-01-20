#pragma once
#include "../SceneBase/SceneBase.h"

class ShopScene : public SceneBase
{
public:
	ShopScene(int floor);
	~ShopScene();

	bool Init() override;
	void Update() override;
	void Render() override;
};