#pragma once

#include "Global.h"
#include "box.h"

#include <vector>
using namespace std;

struct Courners{

	Courners()
		: UpLeft(0) 
		, UpRight(0) 
		, DownLeft(0) 
		, DownRight(0) 
		, CollidePoint(0,0)
	{
	}

	bool GetCollide(){
		return UpRight||UpLeft||DownLeft||DownRight;
	}

	BOOL UpLeft;
	BOOL UpRight;
	BOOL DownLeft;
	BOOL DownRight;

	hgeVector CollidePoint;

};


class BoxList{
public:
	BoxList();
	~BoxList();

	hgeVector Collision(hgeVector CharPos);
	BOOL BoolCollision(hgeVector CharPos);
	Courners GetCollisionCourners(hgeVector CharPos);

	void      Draw(hgeResourceManager*);
	void      Push(Box val);

	Box GetBox(int index){return Boxes[index];}
	int GetSize(){return Boxes.size();}

	BoxList GetVisibleBoxes(); // ȭ�� �� ���̴� �ڽ��鸸 üũ�� �൵ �ϳ��� ���� ����.
	BoxList GetBoxesInRange();

private:
	vector<Box> Boxes;
};


BOOL BoxCollision(hgeVector CharPos,BoxList BList);

Courners GetCollisionCourners(hgeVector CharPos,BoxList BList);