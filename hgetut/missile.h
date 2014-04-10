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

	hgeVector Position;  //�׸��� �ʿ��� �̻����� ���� ��ġ
	hgeVector Direction; //�̻����� ���ư��� ����
	hgeVector Target; // ��ǥ (�÷��̾�)�� �̻��� ������ ����

	hgeAnimation* ExAnim;  // explosion Animation
	hgeAnimation* Firing;

	float thetha; // �̻��� ���� ����
	float phi; // �̻��� ���� ȸ�� ����

	float ratio;//���

	bool Fired;//�߻�Ǿ���?
	bool Jet;//�̻����� �������ΰ�?
	bool Explode;

	int startTime;
};