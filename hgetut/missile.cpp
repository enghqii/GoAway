#include "missile.h"
#include <math.h>
#include <stdlib.h>

#define _60_TO_RAD(thetha) (thetha * 3.141592 /180 )
#define _RAD_TO_60(thetha) (thetha * 180 /3.141592 )

#define MAX_RATIO 30

float GetVectorAngle(hgeVector v1,hgeVector v2){
	return _RAD_TO_60(  atan2 (
		( v2.x * v1.y )  -  ( v2.y * v1.x )
		, ( v2.x * v1.x )  +  ( v2.y * v1.y )
		)  );
}


Missile::Missile(hgeResourceManager* resman,hgeVector Position,float dgree): m_resman(resman){

	//printf("contructor\n");
	this->Position = Position;
	ExAnim = NULL;
	Firing = NULL;
	init(dgree);
	Fire();
}

Missile::Missile(const Missile &p)
{
	ExAnim = NULL;
	Firing = NULL;
	//printf("copy\n");
	*this = p;
	ExAnim = new hgeAnimation( *( m_resman->GetAnimation("MisExp") ) ) ;
	ExAnim->SetHotSpot(128,315);
	ExAnim->Play();
	
	Firing = new hgeAnimation( *( m_resman->GetAnimation("MisFiring") ) ) ;
	Firing->SetHotSpot(30,0);
	Firing->Play();
}

Missile::~Missile(){
	//printf("destructor\n");
	SAFE_DELETE(ExAnim);
	SAFE_DELETE(Firing);
}

void Missile::Fire(){
	if(Fired == false)
		Fired = true;
}

void Missile::draw(){
	if(Fired){
		m_resman->GetSprite("MissileSpr")->RenderEx( Position.x - GetMainCamera()->GetX() , Position.y + GetMainCamera()->GetY() , Direction.y/Direction.x );
		Firing->RenderEx(Position.x - GetMainCamera()->GetX() , Position.y + GetMainCamera()->GetY() , Direction.y/Direction.x);
	}
	else if(Explode){
		ExAnim->Render(Position.x - GetMainCamera()->GetX() , Position.y + GetMainCamera()->GetY());
	}
}

void Missile::move(hgeVector targetPos,float timeDelta){

	Boom();

	if(Fired){

		Firing->Update(timeDelta);

		if(!Jet){
			if( GetTickCount() > (unsigned)startTime+100)
				Jet = true;
			Direction.Normalize();
			Position +=  ratio * 60 * timeDelta * Direction;
		}

		else{

			Jet = false;

			hgeVector Target = targetPos - Position;

			Target.Normalize();

			float Angle = GetVectorAngle(Target,Direction);

			if( Angle >= -thetha && Angle <= thetha ){

				int a = rand()%(int)phi;

				if(Angle < 0){

					if(abs(Angle) <= phi)
						Direction = Target;
					else
						Direction.Rotate(_60_TO_RAD(-a));

				}

				else if(Angle > 0){

					if(abs(Angle) <= phi)
						Direction = Target;
					else
						Direction.Rotate(_60_TO_RAD(a)); // angle in radian

				}

				ratio = abs( -(MAX_RATIO - phi)/thetha * Angle + MAX_RATIO );
			}

			else{
				if(ratio < MAX_RATIO)
					ratio += 0.1f;
			}

			Position += (int)ratio* 60 *timeDelta *Direction;
		}
	}

	else if(Explode){
		ExAnim->Update(timeDelta);
		if(ExAnim->GetFrame()+1 == ExAnim->GetFrames()){
			Explode = false;
		}
	}
}

void Missile::init(float dgree){

	Direction.x = cosf(dgree * 3.141592 / 180);
	Direction.y = sinf(dgree * 3.141592 / 180);

	Target.x = 0.0f;
	Target.y = 0.0f;

	thetha =45;
	phi = 10.0f;
	ratio = 20;

	Fired =false;
	Jet =false;
	Explode = false;

	ExAnim = new hgeAnimation( *( m_resman->GetAnimation("MisExp") ) ) ;
	ExAnim->SetHotSpot(128,315);
	ExAnim->Play();

	Firing = new hgeAnimation( *( m_resman->GetAnimation("MisFiring") ) ) ;
	Firing->SetHotSpot(30,8);
	Firing->Play();

	startTime = GetTickCount();
}

void Missile::Boom(){
	if(Position.y> 700){
		Fired = false;
		Jet = false;
		Explode = true;
		GetHgeDevice()->Effect_Play(m_resman->GetEffect("MisExSound"));
	}
}
void Missile::Bang(){
	if(Fired){
		Fired = false;
		Jet= false;
		Explode = true;
		GetHgeDevice()->Effect_Play(m_resman->GetEffect("MisExSound"));
	}
}