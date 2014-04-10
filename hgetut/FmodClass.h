#pragma once
#include<fmod.hpp>

class Song{
public:
	Song();
	~Song();

	void Create(const char* FileName);
	void Play();
	void Stop();
	void Release();
	void SetMode(int m){Mode = m;}
	void SetVolume(float v){FChannel->setVolume(v);}

	bool isEnd(); // 소리의 끝인가?

	//나중에 삭제
	bool GetPlaying(){return Playing;}
private:
	FMOD::Channel *FChannel; // 
	FMOD::Sound *FSound;  //
	bool Playing;
	int Mode;
	float Volume;
};