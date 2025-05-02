#pragma once

class state
{
public:
	virtual void Init() = 0;
	virtual void HadleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;

	virtual void pause() {};
	virtual void resume() {};
};