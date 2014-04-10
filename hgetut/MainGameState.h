#include "GameState.h"
#include "Global.h"

#include "plane.h"
#include "player.h"
#include "BoxList.h"
#include "BackGround.h"
#include "FmodClass.h"
#include "Score.h"
#include "MiniMap.h"
#include "StageClear.h"

#include <fstream>
using namespace std;

class MainGameState : public BaseGameState{
public:
	MainGameState(int stage = 0 );
	//MainGameState(){ printf("MainGameState Created with no INITALIZE\n");  SetGameState(GS_GAME);};
	virtual ~MainGameState(){ End(); };

	virtual void Init();
	virtual void  End();

	virtual void Render();
	virtual bool Update(float timeDelta);

	void SetStage(int _stage){
		End();
		Stage = _stage;
		Init();
	}

	virtual void SetFocus(bool b);

private:

	void InitMap(const char* FileName);

	HSTREAM stageMusic;
	HCHANNEL musicChannel;
	HSTREAM HeliMusic;
	HCHANNEL HeliChannel;

	Score* m_time;
	Player* m_player;
	BoxList* m_boxList;
	Plane* m_Heli;
	BackGround* m_Back;
	MiniMap* m_Mini;

	int Stage;

	bool StageCleared;

	float x;
	float y;

	int StartTime;

	hgeFont* fnt;
};