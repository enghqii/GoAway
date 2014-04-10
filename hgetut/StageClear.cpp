#include "StageClear.h"


void StageClear::Init(){
	printf("#### Stage Clear init\n");
	//m_resman->ChangeScript("Resource\\StageClear.res");
	m_resman = new hgeResourceManager("Resource\\StageClear.res");
	fnt= m_resman->GetFont("RF");
	
	m_onFadeOut = false;
	m_alpha = 0;

	x =  -( 1920 - GetSystemMetrics(SM_CXSCREEN) )/2;
	y =  -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;

	name[0] = NULL;
	name[1] = NULL;
	name[2] = NULL;
	name[3] = NULL;

	if( stage > 0 && stage < STAGE_MAX ){
		printf("#### STAGE FILE LOADIING ####\n");
		RI.clear();
		if(inRank){
			GetRankingInfo();
		}
	}

	

	SCMusic = m_resman->GetStream("SCMusic");
	//GetHgeDevice()->Stream_Play(m_resman->GetStream("SCMusic"),false);
}

void StageClear::End(){
	RI.clear();
	if( stage > 0 && stage < STAGE_MAX ){
		stage = 0;
	}
	inRank = false;

	name[0] = NULL;
	name[1] = NULL;
	name[2] = NULL;
	name[3] = NULL;

	SAFE_DELETE(m_resman);
	outRankFile.close();
}

void StageClear::Render(){
	m_resman->GetSprite("SCspr")->Render(x,y);

	fnt->SetColor(ARGB(255,0,0,0));
	fnt->printf(x+1260,y+300,HGEK_RIGHT,"%.3f",PlayerTime);

	if(inRank){
		m_resman->GetSprite("NameSpr")->Render(x+702,y+471);

		fnt->printf(x+975,y+480,HGEK_RIGHT,"%c",name[0]);
		fnt->printf(x+1071,y+480,HGEK_RIGHT,"%c",name[1]);
		fnt->printf(x+1161,y+480,HGEK_RIGHT,"%c",name[2]);
	}
}

bool StageClear::Update(float timeDelta){
	static int cnt = 0;

	if(inRank){

		if( cnt < 3 ){

			for(int i=HGEK_A; i<=HGEK_Z; i++){
				if(GetHgeDevice()->Input_KeyDown(i)){
					name[cnt] = i - HGEK_A + 65;
					cnt++;
					printf("#### + CNT  %d\n",cnt);
				}
			}

		}
		if(GetHgeDevice()->Input_KeyDown(HGEK_BACKSPACE)){
			if(cnt > 0){
				name[--cnt] = NULL;
				printf("#### - CNT  %d\n",cnt);
			}
		}

	}

	if(GetHgeDevice()->Input_KeyDown(HGEK_ENTER)){
		if(inRank){
			if(cnt>2){
				cnt = 0;
				UpdateRankingInfo();
				GetGSM().SetBeforeScene(this->GetGameState());
				GetGSM().ChangeState(GS_RANK);
			}
		}else{
			GetGSM().SetBeforeScene(this->GetGameState());
			GetGSM().ChangeState(GS_MENU);
		}
		return false;
	}
	return false;
}

bool StageClear::RankAvailable(){

	char Name[4];
	float time =0;

	for(int i=0;i<4;i++){
		RankFile>>Name>>time;

		if( PlayerTime * 1000 < time ){
			printf("#### THE Rank is available\n");
			return true;
		}
	}
	return false;
}

void StageClear::GetRankingInfo(){

	char FileName[256];
	sprintf(FileName,"Resource\\Rank\\Rank%d.txt",stage);

	RankFile.open(FileName);

	if(!RankFile)
		return;

	inRank = RankAvailable();

	RankFile.clear();
	RankFile.seekg(0,ios::beg);

	char Name[4];
	float time =0;

	for(int i=0;i<4;i++){
		RankFile>>Name>>time;

		RankingInfo t;
		strcpy(t.name , Name);
		t.score = time;
		printf("#### PUSH BACK Ranking Information\n");
		RI.push_back(t);
	}

	if(inRank){
		outRankFile.open(FileName);
		if(!outRankFile){
			printf("######### out rank file can't be opened\n");
			return;
		}
	}
}

void StageClear::UpdateRankingInfo(){
	RankingInfo t;
	//strcpy(t.name,this->name);
	t.name[0] = this->name[0];
	t.name[1] = this->name[1];
	t.name[2] = this->name[2];
	t.name[3] = NULL;

	t.score = (int)(PlayerTime * 1000);
	RI.push_back(t);

	for(UINT i=0;i<RI.size();i++){
		for(UINT j=0;j<i;j++){
			if(RI[i].score < RI[j].score){
				RankingInfo t = RI[i];
				RI[i] = RI[j];
				RI[j] = t;
			}
		}
	}

	RankFile.close();

	for(int i=0; i<4; i++){
		outRankFile<<RI[i].name<<" "<<RI[i].score<<endl;
	}
}

void StageClear::SetFocus(bool b){
	BaseGameState::SetFocus(b);

	if(b){
		SChannel = GetHgeDevice()->Stream_Play(SCMusic,false);
	}else{
		GetHgeDevice()->Channel_Stop(SChannel);
	}
}