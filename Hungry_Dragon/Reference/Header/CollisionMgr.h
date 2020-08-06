#ifndef CollisionMgr_h__
#define CollisionMgr_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CCollisionMgr :public CBase {
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit CCollisionMgr(void);
	virtual ~CCollisionMgr(void);

	//필요한 함수 static으로 만들고 Export_Function 통해서 불러오면됨
public:
	static bool Find_First(CGameObject* _caller, CGameObject* _callee);
	static bool PBullet_Monster(CGameObject* _pPBullet, CGameObject* _pMonster);

	// CBase을(를) 통해 상속됨
	virtual void Free(void) override;
};

END

#endif