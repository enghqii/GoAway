#pragma once

#include "Global.h"
#include "BoxList.h"


class Player{
public:
	Player(hgeResourceManager*);
	~Player();

	enum CHARSTATE{
		CS_JUMPING = 1,
		CS_STANDING,
		CS_RUNNING,
		CS_EXMODE,
		CS_DEAD,
	};

	CHARSTATE NowState;
	
	void Key(float timeDelta);
	void MoveChar(float timeDelta,BoxList BList);

	void Update(float timeDelta,BoxList BList,bool isDead);
	void Draw();
	
	void GiveForce(hgeVector Force);
	hgeVector GetPosition(){return Position;}
	CHARSTATE GetNowState(){return NowState;}

private:
	hgeVector Position;
	hgeVector ExternForce;

	bool LookRight; /*오른쪽을 바라보고 있는가?*/

	static hgeAnimation* NowAnim;
	hgeResourceManager* m_resman;

};