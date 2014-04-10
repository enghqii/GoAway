#include "BoxList.h"


BoxList::BoxList(){

}

BoxList::~BoxList(){

}

hgeVector BoxList::Collision(hgeVector CharPos){

	hgeVector T1 = Boxes[0].CollisionVector(CharPos);

	for(UINT i=0; i<Boxes.size(); ++i){

		hgeVector T2 = Boxes[i].CollisionVector(CharPos);

			T1.x = (T1.x > T2.x ? T1.x : T2.x);
			T1.y = (T1.y > T2.y ? T1.y : T2.y);
	}

	return T1;
}

BOOL BoxList::BoolCollision(hgeVector CharPos){
	for(UINT i=0; i<Boxes.size(); ++i){
		if( Boxes[i].Collision(CharPos) ){ // 박스 리스트의 박스들의 collision
			return true;
		}
	}
	return false;
}

void BoxList::Draw(hgeResourceManager* resman){
	for(UINT i=0; i<Boxes.size(); ++i){
		Boxes[i].Draw(resman);
	}
}

void BoxList::Push(Box val){
	Boxes.push_back(val);
}

BoxList BoxList::GetVisibleBoxes(){

	BoxList VisibleList;

	for(UINT i=0; i<Boxes.size();i++){
		if( GetMainCamera()->GetX() <= Boxes[i].GetPosition().x + Boxes[i].GetWidth() )
			if( GetMainCamera()->GetX() + GetSystemMetrics(SM_CXSCREEN) >= Boxes[i].GetPosition().x )
				VisibleList.Push(Boxes[i]);

	}

	return VisibleList;
}

BoxList BoxList::GetBoxesInRange(){
	BoxList RangeList;

	for(UINT i=0; i<Boxes.size();i++){
		if( GetMainCamera()->GetX() <= Boxes[i].GetPosition().x + Boxes[i].GetWidth() )
			if( GetMainCamera()->GetX() + 3840 - 512 >= Boxes[i].GetPosition().x )
				RangeList.Push(Boxes[i]);
	}

	return RangeList;
}


BOOL BoxCollision(hgeVector CharPos,BoxList BList){
	return BList.BoolCollision(CharPos);
}


struct Courners;

Courners GetCollisionCourners(hgeVector CharPos,BoxList BList){

	Courners CharCourner; //여기서 코너를 다 만들어야지.

	CharCourner.UpLeft = BList.BoolCollision(hgeVector(CharPos.x-32 , CharPos.y-32));
	CharCourner.UpRight = BList.BoolCollision(hgeVector(CharPos.x+32 , CharPos.y-32));
	CharCourner.DownLeft = BList.BoolCollision(hgeVector(CharPos.x-32 , CharPos.y+32));
	CharCourner.DownRight = BList.BoolCollision(hgeVector(CharPos.x+32 , CharPos.y+32));

	if(CharCourner.UpLeft) CharCourner.CollidePoint = BList.Collision(hgeVector(CharPos.x-32 , CharPos.y-32));
	if(CharCourner.UpRight) CharCourner.CollidePoint = BList.Collision(hgeVector(CharPos.x+32 , CharPos.y-32));
	if(CharCourner.DownLeft) CharCourner.CollidePoint = BList.Collision(hgeVector(CharPos.x-32 , CharPos.y+32));
	if(CharCourner.DownRight) CharCourner.CollidePoint = BList.Collision(hgeVector(CharPos.x+32 , CharPos.y+32));
	

	return CharCourner;
}