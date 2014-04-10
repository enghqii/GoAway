#include "GameState.h"
#include "Global.h"
#include "FmodClass.h"

class LogoState : public BaseGameState{
public:
	LogoState() { SetGameState(GS_LOGO); };
	virtual ~LogoState(){ End(); };

	virtual void Init();
	virtual void  End();

	virtual void Render();
	virtual bool Update(float timeDelta);

	virtual void SetFocus(bool b);

private:
};