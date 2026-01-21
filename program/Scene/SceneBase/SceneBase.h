#pragma once

class SceneBase {

public:

	SceneBase() = default;
	~SceneBase() = default;

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};