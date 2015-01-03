#pragma once
class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

