#include "MainGameState.h"
using namespace std;

MainGameState::MainGameState(int _stage)
: Stage(_stage),
	m_time(NULL),
	m_player(NULL),
	m_boxList(NULL),
	m_Heli(NULL),
	m_Back(NULL),
	m_Mini(NULL),
	fnt(NULL),

	stageMusic(NULL),
	musicChannel(NULL),
	HeliMusic(NULL),
	HeliChannel(NULL)
{ 
	SetGameState(GS_GAME);
};



void MainGameState::Init(){

	if(Stage == 0) return;
	
	//m_resman->ChangeScript("Resource\\Gaming.res");
	m_resman = new hgeResourceManager("Resource\\Gaming.res");
	GetMainCamera()->GetX() = 0;

	StageCleared = false;

	m_player = new Player(m_resman);
	m_Heli = new Plane(m_resman);
	m_boxList = new BoxList;
	m_Back = new BackGround(m_resman,Stage);
	m_time = new Score;
	m_Mini = new MiniMap;
	fnt = new hgeFont("Resource\\Font\\RF.fnt");

	x =  -( 1920 - GetSystemMetrics(SM_CXSCREEN) )/2;
	y =  -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;

	m_boxList->Push( Box( -512 , 0 ,Box::KB_BARR ) ); // 0번
	m_boxList->Push( Box(38400 , 0 ,Box::KB_BARR ) ); // 1번 <이거와 충돌되면 스테이지 클리어>

	/*-- 바리케이트 들 --*/

	char StageFilePath[256] = {0,};
	sprintf(StageFilePath,"Resource\\Map\\Stage%d.txt",Stage);

	InitMap(StageFilePath);

	char MusicPath[256] = {0,};
	sprintf(MusicPath,"Stage%dMusic",Stage);
	
	stageMusic	= m_resman->GetStream(MusicPath);
	HeliMusic	= m_resman->GetStream("Heil");

	m_time->InitScore();

	StartTime = GetTickCount();
}

void MainGameState::End(){
	printf(" GAMING STATE ENDING\n");
	SAFE_DELETE(m_resman);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_Heli);
	SAFE_DELETE(m_boxList);
	SAFE_DELETE(m_Back);
	SAFE_DELETE(m_time);
	SAFE_DELETE(m_Mini);
	SAFE_DELETE(fnt);
	printf(" GAMNING STATE ENDED\n");
}

void MainGameState::Render(){

	m_Back->Draw();
	m_boxList->Draw(m_resman);
	m_Heli->Draw();
	m_player->Draw();
	m_time->DrawScore();
	m_Mini->Draw(m_resman , m_boxList->GetBoxesInRange() , m_player->GetPosition() );

	if(GetTickCount()-StartTime < 3000){
		fnt->SetColor(ARGB(255,0,0,0));
		fnt->printf(GetSystemMetrics(SM_CXSCREEN)/2,GetSystemMetrics(SM_CYSCREEN)/2,HGEK_RIGHT,"%.3f",(float)(3000 - GetTickCount() + StartTime ) / 1000.0f);
	}

	if(m_player->GetNowState() == Player::CS_DEAD){
		m_time->StopCount();
		m_resman->GetSprite("GameOverSpr")->Render(x,y);
		//GetHgeDevice()->Stream_Play(m_resman->GetStream("Dead"),false);
	}
}

bool MainGameState::Update(float timeDelta){

	if(GetTickCount()-StartTime > 3000){
		// use time delta
		m_Back->Update(timeDelta);
		m_Heli->Update( m_boxList->GetVisibleBoxes() , m_player->GetPosition() , timeDelta );
		m_player->Update( timeDelta , m_boxList->GetVisibleBoxes() , m_Heli->CollWithPl( m_player->GetPosition() ) );
		m_time->UpdateScore(timeDelta);
		//
		BoxList t;
		t.Push(m_boxList->GetBox(1));

		if( GetCollisionCourners(m_player->GetPosition() , t ).GetCollide() || GetHgeDevice()->Input_KeyDown(HGEK_END) ){
			//
			StageCleared = true;
			GetGSM().PopScene(GS_SCLR);
			StageClear* tempPtr = dynamic_cast<StageClear*>(GetGSM().GetScene(GS_SCLR));
			tempPtr->SetClearInfo(Stage,m_time->GetNowScore());
			GetGSM().EndPopScene();
			GetGSM().ChangeState(GS_SCLR);
			
		}

	}
	if(GetHgeDevice()->Input_KeyDown(HGEK_ESCAPE)){
		GetGSM().SetBeforeScene(this->GetGameState());
		GetGSM().ChangeState(GS_MENU);
		return false;
	}if( GetHgeDevice()->Input_KeyDown(HGEK_R) ){
		End();
		Init();
	}
	return false;
}

void MainGameState::InitMap( const char* FileName ){
	ifstream Map;

	Map.open(FileName);

	if(!Map){
		MessageBox(NULL, TEXT(" Where the HELL is the Fucking \'Map.dat\' ? ") , TEXT("Hey Fucker"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		GetGSM().ChangeState(GS_MENU);
	}

	int x=0,y=0,kind=0;
	while(!Map.eof()){
		Map>>x>>y>>kind;
		m_boxList->Push(Box(x,y,(Box::KindOfBox)kind));
	}

	printf("Load OK\n");

	Map.close();
}

void MainGameState::SetFocus(bool b){
	BaseGameState::SetFocus(b);

	if(b){
		musicChannel	= GetHgeDevice()->Stream_Play(stageMusic,false);
		HeliChannel		= GetHgeDevice()->Stream_Play(HeliMusic,false);
	}else{
		GetHgeDevice()->Channel_Stop(musicChannel);
		GetHgeDevice()->Channel_Stop(HeliChannel);
	}
}