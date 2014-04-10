#pragma once

#include "Global.h"

class BackGround{
public:
	BackGround(hgeResourceManager* resman,int stage);
	~BackGround(){}

	void Update(float timeDelta);
	void Draw();

private:
	hgeSprite* spr;
	int stage;
};