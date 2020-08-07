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

	//�ʿ��� �Լ� static���� ����� Export_Function ���ؼ� �ҷ������
public:
	static bool Find_First(CGameObject* _caller, CGameObject* _callee);
	static bool Player_Monster(CGameObject* _pPlayer, CGameObject* _pMonster);

	// CBase��(��) ���� ��ӵ�
	virtual void Free(void) override;
};

END

#endif