#include "BackGround.h"

BackGround::BackGround(hgeResourceManager* resman,int stage){
	this->stage = stage;

	char StageSprite[256];
	sprintf(StageSprite,"Stage%dBack",stage);

	spr = resman->GetSprite(StageSprite);
	spr->SetColor(ARGB(255,255,255,255));
}

void BackGround::Update(float timeDelta){

}

void BackGround::Draw(){
	spr->Render( -(int)GetMainCamera()->GetX()%1920       ,(int)GetMainCamera()->GetY());
	spr->Render( -(int)GetMainCamera()->GetX()%1920 +1920 ,(int)GetMainCamera()->GetY());
}