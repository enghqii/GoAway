#include "MiniMap.h"

MiniMap::MiniMap(void)
{
	width = GetSystemMetrics(SM_CXSCREEN) / 8.0f;
	height = GetSystemMetrics(SM_CYSCREEN) / 8.0f;

	Position.x = GetSystemMetrics(SM_CXSCREEN)/2 + 150 ;
	Position.y = -(  768 - GetSystemMetrics(SM_CYSCREEN) )/2;
}

MiniMap::~MiniMap(void)
{
}

void MiniMap::Update( float timeDelta )
{

}

void MiniMap::Draw(hgeResourceManager* resman, BoxList DrawList,hgeVector CharPos)
{
	resman->GetSprite("MiniMapSpr")->Render(Position.x , Position.y);

	for(int i=0;i<DrawList.GetSize();i++){

		if( DrawList.GetBox(i).GetKind() == Box::KB_BARR)
			continue;

		resman->
			GetSprite("MiniBuilding")->
				Render(Position.x + ( DrawList.GetBox(i).GetPosition().x - GetMainCamera()->GetX() )/8 + 64
				,	   Position.y + ( DrawList.GetBox(i).GetPosition().y - 2 )/8);

		if(	   DrawList.GetBox(i).GetKind() == Box::KB_HYUNGA 
			|| DrawList.GetBox(i).GetKind() == Box::KB_LIMART
			|| DrawList.GetBox(i).GetKind() == Box::KB_STOREHOUSE){
				resman->
					GetSprite("MiniBuilding")->
					Render(Position.x + ( DrawList.GetBox(i).GetPosition().x - GetMainCamera()->GetX() + 256 )/8 + 64
					,	   Position.y + ( DrawList.GetBox(i).GetPosition().y - 2 )/8);
		}
		if(    DrawList.GetBox(i).GetKind() == Box::KB_BRICKLADDER
			|| DrawList.GetBox(i).GetKind() == Box::KB_TREE
			|| DrawList.GetBox(i).GetKind() == Box::KB_GLASS){
			resman->
			GetSprite("MiniBuilding")->
			Render(Position.x + ( DrawList.GetBox(i).GetPosition().x - GetMainCamera()->GetX() )/8 + 64
			,	   Position.y + ( DrawList.GetBox(i).GetPosition().y - 2 + 256 )/8);
		}
	}

	if( ( CharPos.y - 2 )/8 >= 0 )
		resman->GetSprite("MiniPlayer")->Render( Position.x + ( CharPos.x - GetMainCamera()->GetX() )/8 + 64
													,Position.y + ( CharPos.y - 2 )/8);
}