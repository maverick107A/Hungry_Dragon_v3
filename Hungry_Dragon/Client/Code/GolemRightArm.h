#ifndef GolemRightArm_h__
#define GolemRightArm_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGolemRightArm : public Engine::CMonsterMain
{
private:
	explicit CGolemRightArm(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGolemRightArm(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
private:
	HRESULT		Add_Component(void);

public:
	static CGolemRightArm*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};


#endif // GolemRightArm_h__
