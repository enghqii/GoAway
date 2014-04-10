#include "player.h"

hgeAnimation* Player::NowAnim;

Player::Player(hgeResourceManager* resman):m_resman(resman){
	Position.x = 320;
	Position.y = -27;

	ExternForce.x = 0;
	ExternForce.y = 0;

	NowState = CS_JUMPING;

	LookRight = true;

	NowAnim =m_resman->GetAnimation("Jumping");
	NowAnim->SetHotSpot(32,32);
	NowAnim->Play();
}

Player::~Player(){
}

void Player::Update(float timeDelta,BoxList BList,bool isDead){

	isDead = false;


	if(isDead && NowState != CS_DEAD){
		NowState = CS_DEAD;
		printf("Dead!\n");
	}

	if(NowState == CS_DEAD){
		return;
	}

	Key(timeDelta);

	MoveChar(timeDelta,BList);

	if( Position.y >= 700-32 ){ // Ground Collide

		Position.y = 700-32;

		ExternForce.y = 0;

		if(NowState != CS_RUNNING){
			NowState = CS_STANDING;
			NowAnim  = m_resman->GetAnimation("Stand");
		}

	}


	GetMainCamera()->GetX() = Position.x - 512;

	NowAnim->Update(timeDelta);

	//printf("NowState = %d  %d\n",NowState,NowAnim->IsPlaying());

	//if(timeDelta <= 0.018)
	//	printf("Ex.x = %f\n",ExternForce.x);

}


void Player::Key(float timeDelta){

	if(GetHgeDevice()->Input_GetKeyState(HGEK_UP) || GetHgeDevice()->Input_GetKeyState(HGEK_SPACE)){

		if(NowState != CS_JUMPING){
			if( abs(ExternForce.y) < 60* timeDelta ){
				ExternForce.y = -30;
			}
			NowState = CS_JUMPING;
			NowAnim  = m_resman->GetAnimation("Jumping");
			NowAnim->Play();
		}

	}if(GetHgeDevice()->Input_GetKeyState(HGEK_DOWN)){
		if(GetHgeDevice()->Input_KeyDown(HGEK_DOWN)){
			ExternForce.y += 70 * 60 * timeDelta;
		}
	}if(GetHgeDevice()->Input_GetKeyState(HGEK_LEFT)){

		static int BeforeKeyDown = 0;

		LookRight = false;
		if(NowState != CS_JUMPING && NowState != CS_RUNNING){
			NowAnim = m_resman->GetAnimation("Run");
			NowAnim->Play();
		}
		if( GetHgeDevice()->Input_KeyDown(HGEK_LEFT) ){

			int NowKeyDown = GetTickCount();

			if(NowKeyDown - BeforeKeyDown <= 300){
				ExternForce.x -= 2400.0f * timeDelta;
			}

			BeforeKeyDown = NowKeyDown;
		}
		else{
			ExternForce.x-=70 * timeDelta;
		}
	}if(GetHgeDevice()->Input_GetKeyState(HGEK_RIGHT)){

		static int BeforeKeyDown = 0;

		LookRight = true;
		if(NowState != CS_JUMPING && NowState != CS_RUNNING){
			NowState = CS_RUNNING;
			NowAnim  = m_resman->GetAnimation("Run");
			NowAnim->Play();
		}
		if( GetHgeDevice()->Input_KeyDown(HGEK_RIGHT) ){

			int NowKeyDown = GetTickCount();

			if(NowKeyDown - BeforeKeyDown <= 300){
				ExternForce.x += 40.0f * 60 * timeDelta;
			}

			BeforeKeyDown = NowKeyDown;
		}
		else{
			ExternForce.x+=70 * timeDelta;
		}
	}

}

void Player::MoveChar(float timeDelta,BoxList BList){

	if( ExternForce.x>= 28.8f){
		ExternForce.x = 28.8f;
	}
	if( ExternForce.x<=-28.8f){
		ExternForce.x = -28.8f;
	}

	if( abs(ExternForce.x) <= 5){
		if(NowState !=CS_JUMPING){
			NowState = CS_STANDING;
			NowAnim  = m_resman->GetAnimation("Stand");
		}
	}

	Courners cs = GetCollisionCourners(hgeVector(Position.x + ExternForce.x,Position.y),BList);
	//xÁÂÇ¥¸¦ Áßµ¹Ã³¸® ÇØÁÜ
	if(ExternForce.x > 0){
		if(cs.UpRight && cs.DownRight){
			if(NowState != CS_JUMPING){
				NowState = CS_JUMPING;
				NowAnim  = m_resman->GetAnimation("Jumping");
				NowAnim->Play();
			}
			ExternForce.x=0;
			Position.x = cs.CollidePoint.x - 33;
		}else{
			Position.x += ExternForce.x;
		}
	}else if(ExternForce.x < 0){
		if(cs.DownLeft && cs.UpLeft){
			if(NowState != CS_JUMPING){
				NowState = CS_JUMPING;
				NowAnim  = m_resman->GetAnimation("Jumping");
				NowAnim->Play();
			}

			ExternForce.x=0;
			Position.x = cs.CollidePoint.x + 33;
		}else{
			Position.x += ExternForce.x;
		}

	}
	cs = GetCollisionCourners(hgeVector(Position.x,Position.y + ExternForce.y),BList);

	if(ExternForce.y > 0){
		if(cs.DownLeft && cs.DownRight){ 
			// if those bool values are TRUE , it means Crash! Fucker.

			//printf("Position.y = 700-512-33 \n");
			ExternForce.y = 0; 
			if(NowState != CS_RUNNING && NowState != CS_STANDING){
				NowState = CS_STANDING;
				NowAnim  = m_resman->GetAnimation("Stand");
				NowAnim->Play();
			}
			Position.y = cs.CollidePoint.y-33;
		}else{
			Position.y += ExternForce.y;
		}
	}else if(ExternForce.y < 0){
		if(cs.UpRight && cs.UpLeft){
			ExternForce.y = 0;
		}else{
			Position.y += ExternForce.y;
		}

	}



	if(NowState != CS_STANDING || NowState != CS_RUNNING)
		ExternForce += GRAVITY * 60 * timeDelta;
	ExternForce *= 0.98f;
}

void Player::Draw(){
	if( NowState == CS_DEAD ){
		return;
	}
	NowAnim->RenderEx( Position.x - GetMainCamera()->GetX() 
		,              Position.y + GetMainCamera()->GetY()
		, NULL
		, ( LookRight ? 1.0f : -1.0f )
		, ( LookRight ? 0.0f :  1.0f ) 
		);
}

void Player::GiveForce(hgeVector Force){
	if( !(int)ExternForce.y ){
		ExternForce.y = Force.y;
	}
}