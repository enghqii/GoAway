#include "plane.h"
#include <omp.h>

Plane::Plane(hgeResourceManager* resman): HeliAnim(NULL) , m_resman(resman) , missiles(resman) {
	Position.x = -700;
	Position.y = 200;
	HeliAnim =resman->GetAnimation("HeliAnim");
	HeliAnim->SetHotSpot(280,220);
	HeliAnim->Play();
}

Plane::~Plane(){

}

void Plane::Update(BoxList BList,hgeVector targetPos,float timeDelta){

	Key(timeDelta);

	Move(targetPos,timeDelta);

	static int cnt = 0;

	if( cnt%10 == 0 )
		missiles.InsertLast(node(m_resman,Position,rand()%90-30));
	cnt++;

	_iterator it = missiles.GetIter();

	while(it.hasNext()){
		if(  it->GetMissile().GetJet() == false 
			&& it->GetMissile().GetFire()== false 
			&& it->GetMissile().GetExplode()== false  ){

			node* del = *it;
			it++;
			missiles.DeleteNode(del);
			continue;
		}
		else{
			it->GetMissile().move(targetPos,timeDelta);
			it++;
		}
	}

	CollWithMis(BList);

	HeliAnim->Update(timeDelta);
}

void Plane::Move(hgeVector targetPos,float timeDelta){
	if( Position.x < targetPos.x - 300){
		DeltaPos.x += 70 * timeDelta;
	}

	Position += DeltaPos;
	DeltaPos *= 0.97f;
}

void Plane::Key(float timeDelta){
}

void Plane::Draw(){
	HeliAnim->Render( Position.x - GetMainCamera()->GetX() , Position.y + GetMainCamera()->GetY() );


	_iterator it = missiles.GetIter();
	
	while(it.hasNext()){
		it->GetMissile().draw();
		it++;
	}
}

bool Plane::CollWithPl(hgeVector CharPos){

	_iterator it = missiles.GetIter();

	while(it.hasNext()){
		if(it->GetMissile().GetFire()){
			if( CharPos.x-16 <= it->GetMissile().GetPosition().x && it->GetMissile().GetPosition().x <= CharPos.x+16 ){
				if( CharPos.y-16 <= it->GetMissile().GetPosition().y && it->GetMissile().GetPosition().y <= CharPos.y+16 ){
					it->GetMissile().Bang();
					return true;
				}
			}
		}
		it++;
	}
	return false;
}

void Plane::CollWithMis(BoxList BList){// �ڽ��� �̻����� �浹 üũ�� �Ѵٳ�.
	
	_iterator it = missiles.GetIter();

//#pragma omp parallel for

	while(it.hasNext()){ //�̰� �ٷ� �̻��� ��ü�� ���鼭 �浹üũ�� �ϴ� �� ����.

		if(it->GetMissile().GetFire()){

			for(UINT j= 0; j < BList.GetSize(); j++ ){

				if(BList.GetBox(j).GetKind() != Box::KB_BARR){

					if(    BList.GetBox(j).GetPosition().x < it->GetMissile().GetPosition().x 
						&& it->GetMissile().GetPosition().x < BList.GetBox(j).GetPosition().x + BList.GetBox(j).GetWidth()){

							if(    BList.GetBox(j).GetPosition().y < it->GetMissile().GetPosition().y 
								&& it->GetMissile().GetPosition().y < BList.GetBox(j).GetPosition().y + BList.GetBox(j).GetHeight()){
									it->GetMissile().Bang();
							}
					}
				}
			}
		}
		it++;
	}
}