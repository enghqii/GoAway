#include "StageSelect.h"
#include "MainGameState.h"

StageSelect::StageSelect()
: SSMusic(NULL),SSChannel(NULL)
{
	SetGameState(GS_STSE);
}

StageSelect::~StageSelect(){
	End();
}

void StageSelect::Init()
{
	printf("INIT Stage select state\n");
	//m_resman->ChangeScript("Resource\\StageSelect.res");
	m_resman = new hgeResourceManager("Resource\\StageSelect.res");

	m_onFadeOut = false;
	m_alpha = 0;

	stage = 1;
	x =  -( 1920 - GetSystemMetrics(SM_CXSCREEN) )/2;
	y =  -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;

	SSMusic = m_resman->GetStream("SSMusic");
	//GetHgeDevice()->Stream_Play(m_resman->GetStream("SSMusic"),false);
}

void StageSelect::End()
{
	SAFE_DELETE(m_resman);
	printf("Stage Select RESMAN DELETED\n");
}

void StageSelect::Render()
{
	hgeSprite* t = m_resman->GetSprite("StaSelBackSpr");
	t->RenderAlpha(x,y,m_alpha);


	m_resman->GetSprite("MissileSpr")->RenderExAlpha( x+758 , y+ 405 + (stage-1) * 200 , 0 , 2 , 2 ,m_alpha);

	//758 405
	//758 605
}

bool StageSelect::Update( float timeDelta )
{
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

	if(GetHgeDevice()->Input_KeyDown(HGEK_UP)){
		if(stage > 1)
			stage--;

	}if(GetHgeDevice()->Input_KeyDown(HGEK_DOWN)){
		if(stage < 2)
			stage++;
	}

	if(GetHgeDevice()->Input_KeyDown(HGEK_ENTER)){
		m_onFadeOut = true;
		GetGSM().PopScene(GS_GAME);
		MainGameState* tempPtr = dynamic_cast<MainGameState*>(GetGSM().GetScene(GS_GAME));
		tempPtr->SetStage(stage);
		GetGSM().EndPopScene();
		GetGSM().SetBeforeScene(this->GetGameState());
		GetGSM().ChangeState(GS_GAME);
	}if(GetHgeDevice()->Input_KeyDown(HGEK_ESCAPE)){
		m_onFadeOut = true;
		GetGSM().SetBeforeScene(this->GetGameState());
		GetGSM().ChangeState(GS_MENU);
	}
	return false;
}

void StageSelect::SetFocus(bool b){
	BaseGameState::SetFocus(b);

	if(b){
		SSChannel = GetHgeDevice()->Stream_Play(SSMusic,false);
	}else{
		GetHgeDevice()->Channel_Stop(SSChannel);
	}
}