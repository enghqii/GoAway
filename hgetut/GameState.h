#pragma once

//Don't include "Global.h"
#include <hgeresource.h>

class BaseGameState{
public:
	const enum GameState{
		GS_NONE=0,                      // 현재 상태가 아무것도 아닐때
		GS_LOGO,
		GS_MENU,
		GS_GAME,
		GS_STSE, // stage select
		GS_SCLR, // stage clear
		GS_RANK,
		GS_EXIT,
	};

	BaseGameState() : Gs(GS_NONE) , m_alpha(0) , m_onFadeOut(false) , m_Focus(false) , m_resman(NULL) {} // 속도를 위해 멤버 이니셜라이저를 애용합시다.
	virtual ~BaseGameState(){}

	virtual void Init() =0;                             //안녕하신가, 난 씬(Scene)의 시작에서 잡다한 변수들의 초기화를 담당하는 init라고 해
	virtual void  End() =0;                             //안녕      , 난 씬의 끝에서 썼던 변수들을 다시 돌려놓는일을 하는 end라고 해

	virtual void Render() = 0;                          //하하      , 난 화면으로 출력을 담당하는 render라고 해
	virtual bool Update(float timeDelta) = 0;           //이보게    , 난 가지고 있는 모든 오브젝트들의 위치를 갱신하는 일을 담당하는 Update라고 한다네

	GameState	GetGameState(){ return Gs; }
	void		SetGameState(GameState _Gs){ Gs = _Gs; }
	
	virtual void SetFocus(bool b){ m_Focus = b;}
			bool GetFocus() {return m_Focus;}

private:
	GameState	Gs; // 현재의 게임 스테이트 상태를 갖고 있지
protected:
	bool		m_Focus;	 // 메인화면 인가?
	int			m_alpha;
	bool		m_onFadeOut; // 화면이 사라지는 중인가?
	hgeResourceManager* m_resman;
};