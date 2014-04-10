#pragma once

#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4996)


#include <stdio.h>

#include <hge.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgevector.h>
#include <hgeFont.h>
#include <hgeresource.h>
#include <hgeparticle.h>

#include "camera.h"
#include "GameStateManager.h"

#define SAFE_DELETE(p) { if(p){ delete ((p)); (p) = NULL;} }
#define SAFE_ALL_DELETE(p) { if(p){ delete [] ((p)); (p) = NULL;} }
#define SAFE_RELEASE(p) { if(p){ ((p))->Release(); (p) = NULL;} }
#define SAFE_PURGE(p) { if(p){ ((p))->Purge(); SAFE_DELETE(p)} } // for hgeResourceManager
#define GRAVITY hgeVector(0,1.0)
#define FADING_SPEED 20


HGE* GetHgeDevice(bool release = false);

/*hgeResourceManager* GetResMan(bool release =false , const char* FileName =0);*/

camera* GetMainCamera();

GSManager& GetGSM(bool init = false);
