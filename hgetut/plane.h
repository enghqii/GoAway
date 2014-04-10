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
	void CollWithMis(BoxList BList); //미사일은 움직이는 물체이니 여기서 충돌체크 할꺼라네
									
	// 산은 산이요 물은 물이로다. 

private:

	hgeAnimation* HeliAnim; // 헬리콥터는 애니메이션이 하나밖에 없다네 허허허헣

	hgeVector Position;
	hgeVector DeltaPos;

	//vector<Missile> missiles; 벡터를 쓰는대신 연결리스트를 쓸거라네
	LinkedList missiles;

	hgeResourceManager* m_resman;
};