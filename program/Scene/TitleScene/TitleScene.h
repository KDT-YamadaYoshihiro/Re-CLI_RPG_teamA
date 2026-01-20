#pragma once
#include "../SceneBase/SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene(int floor);	//　コンストラクタ & int floorで値の受け渡し
	~TitleScene();	//　デストラクタ

	bool Init() override;
	void Update() override;
	void Render() override;
};