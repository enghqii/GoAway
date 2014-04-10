#pragma once

#include "Global.h"

class Score
{
public:
	Score(void);
	~Score(void);

	void InitScore();
	float GetNowScore();

	void DrawScore();
	void UpdateScore(float timeDelta);

	void StopCount();
	void StartCount();

private:

	bool Count;

	float time;
	hgeFont* fnt;
};
