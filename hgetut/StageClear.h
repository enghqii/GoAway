#pragma once

#include <fstream>
#include <vector>
using namespace std;

#include "Global.h"
#include "GameState.h"
#include "StageSelect.h"

struct RankingInfo{
public:
	RankingInfo(){
		name[0] = ' ';
		name[1] = ' ';
		name[2] = ' ';
		name[3] = NULL;

		score = 0;
	}

	char name[4];
	float score;
};

class StageClear : public BaseGameState{
public:
	//StageClear(int _stage):stage(_stage){ Init(); }
	StageClear()
		:fnt(NULL),SChannel(NULL),SCMusic(NULL)
	{ SetGameState(GS_SCLR);}
	~StageClear(){ End(); }

	virtual void Init();
	virtual void End();
	virtual bool Update(float timeDelta);
	virtual void Render();

	void SetClearInfo(int _stage,float _PlayerTime){
		stage = _stage;
		PlayerTime = _PlayerTime;
	}

	bool RankAvailable();
	void GetRankingInfo();
	void UpdateRankingInfo();

	virtual void SetFocus(bool b);

private:

	HCHANNEL	SChannel;
	HSTREAM		SCMusic;
	
	ifstream RankFile;
	ofstream outRankFile;

	vector<RankingInfo> RI;

	int x;
	int y;

	hgeFont* fnt;

	int stage;
	float PlayerTime;
	bool inRank;
	char name[4];
};