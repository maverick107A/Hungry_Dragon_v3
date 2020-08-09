#ifndef RunMonster_h__
#define RunMonster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;

END

class  CRun_Monster : public Engine::CMonsterMain
{
private:
	explicit CRun_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRun_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);
	void LateUpdate_Object(const float & fTimeDelta);
public:
	static CRun_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev, D3DXVECTOR3 _pos);
private:
	virtual void Free(void) override;

};


#endif // RunMonster_h__
