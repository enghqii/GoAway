#include "GameState.h"
#include "Global.h"
#include "missile.h"

class MenuState : public BaseGameState{
public:
	MenuState():MMusic(NULL),MChannel(NULL) { SetGameState(GS_MENU); };
	virtual ~MenuState(){ End(); };

	virtual void Init();
	virtual void  End();

	virtual void Render();
	virtual bool Update(float timeDelta);

	virtual void SetFocus(bool b);

private:

	HSTREAM		MMusic;
	HCHANNEL	MChannel;

	int NowMenu;
	
	int x;//출력할 x축의 절대 좌표
	int y;//  "" 
};