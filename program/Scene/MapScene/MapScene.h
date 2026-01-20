#pragma once
#include "../SceneBase/SceneBase.h"

class MapScene : public SceneBase
{
public:
	MapScene(int floor);	//　コンストラクタ & int floorで値の受け渡し
	~MapScene();	//　デストラクタ

	bool Init() override;
	void Update() override;
	void Render() override;
};