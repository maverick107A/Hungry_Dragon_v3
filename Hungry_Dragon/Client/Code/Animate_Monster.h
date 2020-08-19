#ifndef AnimateMonster_h__
#define AnimateMonster_h__

#include "Define.h"
#include "Export_Function.h"

BEGIN(Engine)

class CVICustom;
class CTransform;

END

class CAnimate_Monster :public Engine::CMovingObject
{
private:
	explicit CAnimate_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CAnimate_Monster(void);

public:
	virtual HRESULT Ready_Object(void)override;
	virtual int Update_Object(const float& fTimeDelta)override;
	virtual void LateUpdate_Object(const float& fTimeDelat)override;
	virtual void Render_Object(void)override;

private:
	HRESULT Add_Componenet(void);

public:
	static CAnimate_Monster* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void)override;
};
#endif
