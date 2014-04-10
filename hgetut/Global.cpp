#include "Global.h"

extern void initHGE(HGE** hge);

HGE* GetHgeDevice(bool release /*= false*/){
	static HGE *hge = NULL;
	if(hge == NULL){
		initHGE(&hge);
		hge->System_Initiate();
	}
	if(release && hge != NULL){
		hge->System_Shutdown();
		hge->Release();
	}

	return hge;
}

// hgeResourceManager* GetResMan(bool release /* =false */ , const char* FileName /* =0 */){
// 	static hgeResourceManager* ResMan = NULL;
// 	if(ResMan == NULL)
// 		ResMan = new hgeResourceManager(FileName);
// 	if(release == true)
// 		SAFE_DELETE(ResMan);
// 	return ResMan;
// }

camera* GetMainCamera(){
	static camera MainCamera;
	MainCamera.GetY() = -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;
	return &MainCamera;
}

GSManager& GetGSM(bool init){
	static GSManager GSM;
	if(init){
		GSM.init();
	}
	return GSM;
}