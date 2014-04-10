#pragma once
#include "Global.h"

//bool Crash(hgeVector CharPos,hgeVector Position,float width,float height);

class Box{
public:

	enum KindOfBox{
		KB_GAS = 0 ,
		KB_BRICK = 1,
		KB_DK = 2,
		KB_STOREHOUSE = 3,

		KB_TECH = 4,
		KB_LOL = 5,
		KB_HYUNGA = 6,
		KB_LIMART = 7,
		KB_BRICKLADDER = 8,
		KB_TREE=9,
		KB_GLASS=10,

		KB_BARR=11,
	};

	Box(float x=0,float y=0,KindOfBox KoBox=KB_TECH);
	~Box();

	void Draw(hgeResourceManager*);
	void Update(float timeDelta);

	hgeVector GetPosition(){return Position;}
	float GetWidth(){return width;}
	float GetHeight(){return height;}

	hgeVector Crash(hgeVector CharPos);
	BOOL Collision(hgeVector CharPos);
	hgeVector CollisionVector(hgeVector CharPos);

	KindOfBox GetKind(){return Kind;}

private:

	KindOfBox Kind; // 빠악스의 종류를 정한다. 

	hgeVector Position;
	
	float width;
	float height;
};