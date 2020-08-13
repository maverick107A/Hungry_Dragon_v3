#ifndef GameMgr_h__
#define GameMgr_h__


#include "Engine_Define.h"

class CGameMgr
{
	DECLARE_SINGLETON(CGameMgr)

private:
	explicit CGameMgr(void);
	explicit CGameMgr(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameMgr(void);

public:
	// ���� �ѷ� �ִ� ��
	void Game_Update(D3DXVECTOR3 _vPlayerPos);
	void Cave_ObjPool_Update(D3DXVECTOR3 _vPlayerPos);
	
private:
	// ����� �۵��.
	LPDIRECT3DDEVICE9				m_pGraphicDev;
};


#endif // GameMgr_h__
