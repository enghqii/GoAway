#include "GameStateManager.h"

#include "LogoState.h"
#include "MenuState.h"
#include "MainGameState.h"
#include "StageClear.h"
#include "RankingState.h"
#include "StageSelect.h"


GSManager::GSManager(){
	init();
}

GSManager::~GSManager(){
	end();
	//SAFE_DELETE(NowState);
}

bool GSManager::init(){
	
	printf("\n====Game State Manager INITING====\n");
	BefState = NULL;
	AddState(new LogoState);
	AddState(new MenuState);
	AddState(new StageSelect);
	AddState(new MainGameState);
	AddState(new StageClear);
	AddState(new RankingState);
	// 사용할 장면들 모음.

	ChangeState(ID_TYPE::GS_LOGO);


	printf("\n====Game State Manager INITED====\n");
	
	return true;
}

bool GSManager::end(){
	printf("\n===Game state manager ending====\n");
	DeleteState(ID_TYPE::GS_LOGO);
	
	DeleteState(ID_TYPE::GS_GAME);
	DeleteState(ID_TYPE::GS_STSE);
	DeleteState(ID_TYPE::GS_SCLR);
	DeleteState(ID_TYPE::GS_RANK);
	DeleteState(ID_TYPE::GS_MENU);

	printf("\n===Game state manager ended====\n");

	return true;
}


void GSManager::Render(){
	
	if(BefState)
		BefState->Render();
	NowState->Render();
}

bool GSManager::Update(float timeDelta){
	if(BefState && BefState->GetFocus() == true)
		BefState->Update(timeDelta);
	return NowState->Update(timeDelta);
}

void GSManager::ChangeState(ID_TYPE Gs){

	if(NowState != NULL) { if(NowState->GetGameState() == Gs) return; }

	// if(NowState != NULL) NowState->End(); 여기서 닫지 않고 있다가 before state 가 바뀔때 닫는다. 

	BaseGameState* scene = StateMap[Gs];

	printf("now state is =  %d\n",Gs);

	if(scene == NULL) {
		printf(" error - \"Invalid Scene ID\"\n ");
	}

	scene->Init();
	scene->SetFocus(true);

	NowState = scene;
}

void GSManager::SetBeforeScene(ID_TYPE id){
	printf("Set before state = %d\n",id);
	if(BefState != NULL) BefState->End();
	BefState = StateMap[id];
	BefState->SetFocus(false);
}

void GSManager::PopScene(ID_TYPE id) {

	if(NowState != NULL) StateStack.push(NowState);

	BaseGameState* scene = StateMap[id];

	printf("pop scene is = %d\n",id);

	if(scene == NULL) {
		printf(" error - \"Invalid Scene ID\"\n ");
	}

	
	scene->Init();
	scene->SetFocus(true);
	NowState = scene;
}

void GSManager::EndPopScene() {

	//int result = m_CurScene->EndPosScene(); 


	printf("end pop scene is = %d\n",NowState->GetGameState());

	NowState->End();
	NowState->SetFocus(false);
	NowState = StateStack.top();
	StateStack.pop();

	if(NowState == NULL) {
		printf(" error - \"Scene EndPopScene \" \n ");
	}

}

void GSManager::ChangeState( BaseGameState* t ){
	SAFE_DELETE(NowState);
	NowState = t;
}

void GSManager::AddState(BaseGameState* scene ){
	printf("=ADD STATE\n");
	StateMap[scene->GetGameState()] = scene;
}

void GSManager::DeleteState(ID_TYPE id) {
	printf("=Delete STATE\n");
	SAFE_DELETE(StateMap[id]);
}
