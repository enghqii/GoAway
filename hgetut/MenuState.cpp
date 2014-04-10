#include "MenuState.h"

void MenuState::Init(){
	printf("INIT Menu state\n");
	SetGameState(GS_MENU);
	//m_resman->ChangeScript("Resource\\Menu.res");
	m_resman = new hgeResourceManager("Resource\\Menu.res");
	NowMenu = 0;

	m_onFadeOut = false;
	m_alpha = 0;

	x =  -( 1920 - GetSystemMetrics(SM_CXSCREEN) )/2;
	y =  -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;

	MMusic = m_resman->GetStream("MMusic");	
}

void MenuState::End(){
	printf(" Menu State end start\n");
	SAFE_DELETE(m_resman);
	printf(" Menu RESMAN DELETED\n");
}

void MenuState::Render(){
	m_resman->GetSprite("MenuSpr")->RenderAlpha( x , y , m_alpha );

	switch(NowMenu){
			case 0:
				m_resman->GetSprite("MissileSpr")->RenderExAlpha( x + 1020 , y + 274 , 0 , 2 , 2 ,m_alpha);
				break;
			case 1:
				m_resman->GetSprite("MissileSpr")->RenderExAlpha( x + 1020 , y + 370 , 0 , 2 , 2 ,m_alpha);
				break;
			case 2:
				m_resman->GetSprite("MissileSpr")->RenderExAlpha( x + 1020 , y + 500 , 0 , 2 , 2 ,m_alpha);
				break;
	}
}

bool MenuState::Update(float timeDelta){

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
		if(NowMenu == 0){
			GetGSM().ChangeState(GS_STSE);
		}else if(NowMenu == 1){
			GetGSM().ChangeState(GS_RANK);
		}else if(NowMenu == 2){
			return true;
		}
	}if(GetHgeDevice()->Input_KeyDown(HGEK_UP)){
		if(NowMenu > 0 )
			NowMenu--;
	}if(GetHgeDevice()->Input_KeyDown(HGEK_DOWN)){
		if(NowMenu < 2 )
			NowMenu++;
	}
	return false;
}

void MenuState::SetFocus(bool b){
	BaseGameState::SetFocus(b);

	if(b){
		MChannel = GetHgeDevice()->Stream_Play(MMusic,false);
	}else{
		GetHgeDevice()->Channel_Stop(MChannel);
	}
}