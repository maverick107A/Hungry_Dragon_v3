#ifndef Golem_h__
#define Golem_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGolem : public Engine::CMonsterMain
{
private:
	explicit CGolem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGolem(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
private:
	HRESULT		Add_Component(void);

public:
	static CGolem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXVECTOR3 m_vBodyPos;

	D3DXVECTOR3 m_vLeftArmPos;
	D3DXVECTOR3 m_vRightArmPos;
private:
	virtual void Free(void) override;

};


#endif // Golem_h__
