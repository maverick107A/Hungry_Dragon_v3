#ifndef GameMgr_h__
#define GameMgr_h__


#include "Engine_Define.h"

class CGameMgr
{
	DECLARE_SINGLETON(CGameMgr)

private:
	explicit CGameMgr(void);
	virtual ~CGameMgr(void);

public:
	void Game_Update(D3DXVECTOR3 _vPlayerPos);


};


#endif // GameMgr_h__
