#pragma once

#include "Global.h"
#include "BoxList.h"

class MiniMap
{
public:
	MiniMap();
	~MiniMap(void);

	void Update(float timeDelta);
	void Draw(hgeResourceManager* resman,BoxList DrawList,hgeVector CharPos);

private:
	hgeVector Position; // 미니맵의 절대적인 좌표
	float width;
	float height;
};
