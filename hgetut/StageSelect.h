#pragma once

#define STAGE_MAX 2

#include "Global.h"
#include "GameState.h"

class StageSelect : public BaseGameState{
public:
	StageSelect();
	virtual ~StageSelect();

	virtual void Init();
	virtual void  End();              

	virtual void Render();
	virtual bool Update(float timeDelta);

	virtual void SetFocus(bool b);

private:

	HSTREAM		SSMusic;
	HCHANNEL	SSChannel;

	int stage;

	float x;
	float y;
};