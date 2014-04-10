#include "RankingState.h"

#define NegativeToZero(a) (((a)>0)?(a):0) 

void RankingState::Init(){

	//m_resman->ChangeScript("Resource\\Rank.res");
	m_resman = new hgeResourceManager("Resource\\Rank.res");

	m_onFadeOut = false;
	m_alpha = 0;

	RankFile1.open("Resource\\Rank\\Rank1.txt");
	RankFile2.open("Resource\\Rank\\Rank2.txt");

	if( !RankFile1 || !RankFile2){
		return;
	}

	x =  -( 1920 - GetSystemMetrics(SM_CXSCREEN) )/2;
	y =  -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;

	NameF = new hgeFont("Resource\\Font\\RF.fnt");
	ScoreF = new hgeFont("Resource\\Font\\PF.fnt");

	RankMusic = m_resman->GetStream("RankMusic");
}

void RankingState::End(){
	RankFile1.close();
	RankFile2.close();
	SAFE_DELETE(NameF);
	SAFE_DELETE(ScoreF);
	SAFE_DELETE(m_resman);
}

bool RankingState::Update(float timeDelta){

	if(m_alpha == 0 && m_onFadeOut == true)
		return true;

	if(m_onFadeOut == false){
		m_alpha += FADING_SPEED;
		if(m_alpha > 255){
			m_alpha = 255;
		}
	}else if(m_onFadeOut == true){
		m_alpha -= FADING_SPEED;
		if(m_alpha < 0){
			m_alpha = 0;
		}
	}

	if(GetHgeDevice()->Input_KeyDown(HGEK_ENTER)){
		m_onFadeOut = true;
		GetGSM().SetBeforeScene(this->GetGameState());
		GetGSM().ChangeState(GS_MENU);
	}
	return false;
}

void RankingState::Render(){
	m_resman->GetSprite("RankBackSpr")->RenderAlpha(x,y,m_alpha);

	char name[4] = "   ";
	int score = 0;

	RankFile1.clear();
	RankFile1.seekg(0,ios::beg);

	RankFile2.clear();
	RankFile2.seekg(0,ios::beg);

	NameF->SetColor(ARGB(NegativeToZero(m_alpha-40),0,0,0));
	ScoreF->SetColor(ARGB(NegativeToZero(m_alpha-40),0,0,0));

	for(int i=0;i<4;i++){
		RankFile1>>name>>score;
		NameF->printf(x+600,y+210+i*130,HGEK_RIGHT,"%s",name);
		ScoreF->printf(x+750,y+200+i*130,HGEK_RIGHT,"%.3f",(float)score/1000.0f);


		RankFile2>>name>>score;
		NameF->printf(x+1150,y+210+i*130,HGEK_RIGHT,"%s",name);
		ScoreF->printf(x+1300,y+200+i*130,HGEK_RIGHT,"%.3f",(float)score/1000.0f);
	}
}

void RankingState::SetFocus(bool b){
	BaseGameState::SetFocus(b);

	if(b){
		RankChannel = GetHgeDevice()->Stream_Play(RankMusic,false);
	}else{
		GetHgeDevice()->Channel_Stop(RankChannel);
	}
}