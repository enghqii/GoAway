#pragma once

#include "Global.h"
#include "missile.h"
#include "BoxList.h"
#include "LinkedList.h"
#include <vector>
using namespace std;
 
class Plane{
public:
	Plane(hgeResourceManager*);
	~Plane();

	void Update(BoxList BList,hgeVector targetPos,float timeDelta);
	void Move(hgeVector targetPos,float timeDelta);
	void Key(float timeDelta);

	void Draw();

	bool CollWithPl(hgeVector CharPos);
	void CollWithMis(BoxList BList); //�̻����� �����̴� ��ü�̴� ���⼭ �浹üũ �Ҳ����
									
	// ���� ���̿� ���� ���̷δ�. 

private:

	hgeAnimation* HeliAnim; // �︮���ʹ� �ִϸ��̼��� �ϳ��ۿ� ���ٳ� �������S

	hgeVector Position;
	hgeVector DeltaPos;

	//vector<Missile> missiles; ���͸� ���´�� ���Ḯ��Ʈ�� ���Ŷ��
	LinkedList missiles;

	hgeResourceManager* m_resman;
};