#include "LogoState.h"

void LogoState::Init(){

	m_onFadeOut = false;

	m_resman = new hgeResourceManager("Resource\\Logo.res");

	m_onFadeOut = false;

	m_alpha = 0;
	
}

void LogoState::End(){
	printf("Logo state alpha is %f\n",m_alpha);
	SAFE_DELETE(m_resman);
	printf("Logo state RESMAN DELETED\n");
}

void LogoState::Render(){
	m_resman->GetSprite("LogoSpr")->SetColor(ARGB(m_alpha,255,255,255));
	m_resman->GetSprite("LogoSpr")->Render( -( 1920 - GetSystemMetrics(SM_CXSCREEN) )/2 , -( 768 - GetSystemMetrics(SM_CYSCREEN) )/2 );
}

bool LogoState::Update(float timeDelta){

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

void LogoState::SetFocus(bool b){
	BaseGameState::SetFocus(b);

	HEFFECT mus = m_resman->GetEffect("LogoSound");
	static HCHANNEL musCHN = 0;

	if(b){
		musCHN = GetHgeDevice()->Effect_Play(mus);
	}else{
		GetHgeDevice()->Channel_Stop(musCHN);
	}
}