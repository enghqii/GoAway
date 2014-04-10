#include "FmodClass.h"
#include "Global.h"

Song::Song(){
	FSound = 0;
	FChannel = 0;
	Playing = false;
	Mode = 0;
	Volume = 1.0f;
}

void Song::Create(const char* FileName){
	GetFsystem()->createSound(FileName,Mode,0,&FSound); 
}

void Song::Play(){
	if(Playing == false){
		Playing = true;
		GetFsystem()->playSound(FMOD_CHANNEL_FREE,FSound,false,&FChannel);
	}
}

void Song::Stop(){
	if(Playing){
		Playing = false;
		FChannel->stop();
	}
}

void Song::Release(){

	Stop();

	if(FSound!=0)
		FSound->release();
	FSound = NULL;
}

bool Song::isEnd(){
	UINT Pos = 0;
	FChannel->getPosition(&Pos,FMOD_TIMEUNIT_MS);

	UINT Len = 0;
	FSound->getLength(&Len,FMOD_TIMEUNIT_MS);

	if(Pos == 0)
		return true;
	return false;
}

Song::~Song(){
	Release();
}