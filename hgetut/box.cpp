#include"box.h"

Box::Box(float x /*=0*/,float y/*=0*/,KindOfBox KoBox /* = KB_256_256 */){
	Position.x =x;
	Position.y =y;

	Kind = KoBox;

	switch(KoBox){
		case KB_GAS:
			width = 256;
			height = 256;
			break;
		case KB_BRICK:
			width = 256;
			height = 256;
			break;
		case KB_DK:
			width = 256;
			height = 256;
			break;
		case KB_STOREHOUSE:
			width = 512;
			height = 256;
			break;

		case KB_TECH:
			width = 256;
			height = 256;
			break;
		case KB_LOL:
			width = 256;
			height = 256;
			break;
		case KB_HYUNGA:
			width = 512;
			height = 256;
			break;
		case KB_LIMART:
			width = 512;
			height = 256;
			break;
		case KB_BRICKLADDER:
			width = 256;
			height = 512;
			break;
		case KB_TREE:
			width = 256;
			height = 512;
			break;
		case KB_GLASS:
			width = 256;
			height = 512;
			break;

		case KB_BARR:
			width = 768;
			height = 768;
			break;
	}
}

Box::~Box(){

}

void Box::Draw(hgeResourceManager* resman){
	switch(Kind){
		case KB_GAS:
			resman->GetSprite("Gas")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_BRICK:
			resman->GetSprite("Brick")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_DK:
			resman->GetSprite("DK")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_STOREHOUSE:
			resman->GetSprite("StoreHouse")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;

		case KB_TECH:
			resman->GetSprite("Tech")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_LOL:
			resman->GetSprite("LOL")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_HYUNGA:
			resman->GetSprite("HyunGa")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_LIMART:
			resman->GetSprite("LimArt")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_BRICKLADDER:
			resman->GetSprite("BrickLadder")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_TREE:
			resman->GetSprite("Tree")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;
		case KB_GLASS:
			resman->GetSprite("Glass")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
			break;

		case KB_BARR:
			resman->GetSprite("BarrSpr")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY());
			break;
	}

	//GetResMan()->GetSprite("Tech")->Render(Position.x - GetMainCamera()->GetX(), Position.y + GetMainCamera()->GetY() );
}

void Update(float timeDelta){

}
hgeVector Box::Crash(hgeVector CharPos){

	hgeVector CrashPoint;

	if(CharPos.y + 32 >= Position.y && CharPos.y-32 <= Position.y + height ){

		if( CharPos.x + 32 >= Position.x  && CharPos.x-32 <= Position.x + width ){

			if( CharPos.x  < Position.x ){
				CrashPoint.x = Position.x - 33;
				CrashPoint.y = 0;
				printf("1st collision\n");
				return CrashPoint;
			}

			if(CharPos.x  > Position.x + width ){
				CrashPoint.x = Position.x + width + 33;
				CrashPoint.y = 0;
				printf("2nd collision\n");
				return CrashPoint;
			}
			
			CrashPoint.x = 0;
			CrashPoint.y = Position.y - 33;
			printf("3rd collision\n");
		}
		
	}
	return CrashPoint;
}

BOOL Box::Collision(hgeVector CharPos){
	if(CharPos.y + 33 >= Position.y && CharPos.y-33 <= Position.y + height){
		if( CharPos.x + 33 >= Position.x && CharPos.x-33 <= Position.x + width){
			return true;
		}
	}
	return false;
}

hgeVector Box::CollisionVector(hgeVector CharPos){

	hgeVector CollidePoint;

	if(CharPos.y + 33 >= Position.y && CharPos.y-33 <= Position.y + height ){
		if( CharPos.x + 33 >= Position.x && CharPos.x-33 <= Position.x + width ){
			if( CharPos.x < Position.x + width/2 )
				CollidePoint.x = Position.x;
			else
				CollidePoint.x = Position.x + width;

			//if( CharPos.y < Position.y + height/2 )
				CollidePoint.y = Position.y;
			//else
				//CollidePoint.y = Position.y + height;
		}
	}
	return CollidePoint;
}

//bool Crash(hgeVector CharPos,hgeVector Position,float width,float height){
//
//	if( CharPos.x + 32 >= Position.x && CharPos.x-32 <= Position.x + width){
//		if( CharPos.y + 32 >= Position.y && CharPos.y-32 <= Position.y + height ){
//			return true;
//		}
//	}
//	return false;
//}