#pragma once
#include "GameState.h"
#include <stack>
#include <map>
using namespace std;

typedef BaseGameState::GameState ID_TYPE;


class GSManager{
public:
	GSManager();
	virtual ~GSManager();

	bool init();
	bool end();

	void Render();
	bool Update(float timeDelta);

	BaseGameState* GetScene(ID_TYPE id){
		return StateMap[id];
	}

	void ChangeState(ID_TYPE Gs);
	void ChangeState(BaseGameState* t);
	void PopScene(ID_TYPE id);
	void EndPopScene();

	void SetBeforeScene(ID_TYPE id);

	void AddState(BaseGameState* scene );
	void DeleteState(ID_TYPE id);

protected:

	BaseGameState*			NowState;
	BaseGameState*			BefState;
	stack<BaseGameState*>	StateStack;
	map< ID_TYPE , BaseGameState* > StateMap;
};