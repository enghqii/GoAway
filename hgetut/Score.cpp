#include "Score.h"

Score::Score(void)
{
	InitScore();
	fnt=new hgeFont("Resource\\Font\\PF.fnt");
}

Score::~Score(void)
{
	SAFE_DELETE(fnt);
}

void Score::InitScore(){
	//time = GetTickCount()
	time = 0;
	Count = true;
}

float Score::GetNowScore(){
	//return GetTickCount() - time;
	return time;
}

void Score::DrawScore()
{
	//GetResMan()->GetSprite("TimeSpr")->Render(GetSystemMetrics(SM_CXSCREEN)/2,
	//										  GetSystemMetrics(SM_CYSCREEN)/2-384);
	fnt->SetColor(ARGB(255,0,0,0));
	fnt->printf(GetSystemMetrics(SM_CXSCREEN)/2 - 250 , GetSystemMetrics(SM_CYSCREEN)/2-384 , HGEK_RIGHT , " Time : %.3f " ,time);
}

void Score::UpdateScore(float timeDelta)
{
	// there is nothing to do!
	if(Count)
		time += timeDelta;
}

void Score::StopCount(){
	Count = false;
}

void Score::StartCount(){
	Count = true;
}