#pragma once

//Don't include "Global.h"
#include <hgeresource.h>

class BaseGameState{
public:
	const enum GameState{
		GS_NONE=0,                      // ���� ���°� �ƹ��͵� �ƴҶ�
		GS_LOGO,
		GS_MENU,
		GS_GAME,
		GS_STSE, // stage select
		GS_SCLR, // stage clear
		GS_RANK,
		GS_EXIT,
	};

	BaseGameState() : Gs(GS_NONE) , m_alpha(0) , m_onFadeOut(false) , m_Focus(false) , m_resman(NULL) {} // �ӵ��� ���� ��� �̴ϼȶ������� �ֿ��սô�.
	virtual ~BaseGameState(){}

	virtual void Init() =0;                             //�ȳ��ϽŰ�, �� ��(Scene)�� ���ۿ��� ����� �������� �ʱ�ȭ�� ����ϴ� init��� ��
	virtual void  End() =0;                             //�ȳ�      , �� ���� ������ ��� �������� �ٽ� ������������ �ϴ� end��� ��

	virtual void Render() = 0;                          //����      , �� ȭ������ ����� ����ϴ� render��� ��
	virtual bool Update(float timeDelta) = 0;           //�̺���    , �� ������ �ִ� ��� ������Ʈ���� ��ġ�� �����ϴ� ���� ����ϴ� Update��� �Ѵٳ�

	GameState	GetGameState(){ return Gs; }
	void		SetGameState(GameState _Gs){ Gs = _Gs; }
	
	virtual void SetFocus(bool b){ m_Focus = b;}
			bool GetFocus() {return m_Focus;}

private:
	GameState	Gs; // ������ ���� ������Ʈ ���¸� ���� ����
protected:
	bool		m_Focus;	 // ����ȭ�� �ΰ�?
	int			m_alpha;
	bool		m_onFadeOut; // ȭ���� ������� ���ΰ�?
	hgeResourceManager* m_resman;
};