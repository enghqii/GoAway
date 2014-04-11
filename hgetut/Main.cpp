
#include "Global.h"

#include "GameStateManager.h"
#include "FmodClass.h"

#include <stdlib.h>
#include <time.h>

//#include <vld.h>

/*
#ifdef _DEBUG
#include<crtdbg.h>
#define CRT_MAP_ALLOC
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif
//*/

const int width = GetSystemMetrics(SM_CXSCREEN);
const int height = GetSystemMetrics(SM_CYSCREEN);


bool FrameMove()
{
	float timeDelta = GetHgeDevice()->Timer_GetDelta();
	
	return GetGSM().Update(timeDelta);
}

bool Render(){

	GetHgeDevice()->Gfx_BeginScene();
	GetHgeDevice()->Gfx_Clear(RGB(0,0,0));

	GetGSM().Render();

	GetHgeDevice()->Gfx_EndScene();

	return false;
}
bool CleanUp(){

	//GetResMan(true,0);

	GetHgeDevice(true);

	return false;
}

void initHGE(HGE** hge){

	(*hge) = hgeCreate(HGE_VERSION);

	(*hge)->System_SetState(HGE_FRAMEFUNC, FrameMove);
	(*hge)->System_SetState(HGE_RENDERFUNC,Render);
	(*hge)->System_SetState(HGE_LOGFILE,"LogFile.txt");

	(*hge)->System_SetState(HGE_TITLE, "How about to RUN?");

	(*hge)->System_SetState(HGE_WINDOWED,true);

	(*hge)->System_SetState(HGE_USESOUND, true);

	(*hge)->System_SetState(HGE_SHOWSPLASH, false);

	(*hge)->System_SetState(HGE_SCREENWIDTH ,width ); // Look Wide!

	(*hge)->System_SetState(HGE_SCREENHEIGHT, height );

	//(*hge)->System_SetState(HGE_FPS,60);
	// 고정 60프레임

	(*hge)->System_SetState(HGE_FPS,HGEFPS_VSYNC);
	// 수직 동기화는 이렇게


	
}

void SetUp(){	

	//ShowCursor(false);

	srand((UINT)time(NULL));

	//GetResMan(false,"Resource\\Logo.res");

	GetHgeDevice();

	GetGSM().ChangeState(BaseGameState::GS_LOGO);
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetUp();
}

int main(){

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif

	HINSTANCE hInst;
	LPSTR str = "Go away";

	wWinMain(GetModuleHandle(NULL), hInst, str,SW_SHOW);
	
	GetHgeDevice()->System_Start();
	

	CleanUp();

	return 0;
}