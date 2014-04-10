#pragma once

#include "Global.h"
#include "GameState.h"

#include <fstream>
using namespace std;

class RankingState : public BaseGameState{
public:
	RankingState(): NameF(NULL) , ScoreF(NULL) , RankMusic(NULL) , RankChannel(NULL)
	{ 
		SetGameState(GS_RANK);
	};
	virtual ~RankingState(){ End(); };

	virtual void Init();
	virtual void  End();

	virtual void Render();
	virtual bool Update(float timeDelta);

	virtual void SetFocus(bool b);

private:

	HSTREAM  RankMusic;
	HCHANNEL RankChannel;

	ifstream RankFile1;
	ifstream RankFile2;
	float x;
	float y;

	hgeFont* NameF;
	hgeFont* ScoreF;
};