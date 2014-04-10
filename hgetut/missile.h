#pragma once
//#include <d3dx9.h>
//#include "Global.h"
#include "Global.h"
#include "FmodClass.h"


class Missile{
public:
	Missile(hgeResourceManager* resman, hgeVector Position,float dgree = 0);
	Missile(const Missile &p);
	~Missile();

	void init(float dgree);

	void draw();
	void move(hgeVector targetPos,float timeDelta);

	void Fire();
	void Boom();
	void Bang();

	hgeVector GetPosition(){return Position;}

	bool GetFire(){return Fired;}
	bool GetJet(){return Jet;}
	bool GetExplode(){return Explode;}

private:

	hgeResourceManager* m_resman;

	hgeVector Position;  //그릴때 필요한 미사일의 절대 위치
	hgeVector Direction; //미사일이 나아가는 방향
	hgeVector Target; // 목표 (플레이어)와 미사일 사이의 벡터

	hgeAnimation* ExAnim;  // explosion Animation
	hgeAnimation* Firing;

	float thetha; // 미사일 추적 범위
	float phi; // 미사일 벡터 회전 각도

	float ratio;//배수

	bool Fired;//발사되었나?
	bool Jet;//미사일이 추진중인가?
	bool Explode;

	int startTime;
};