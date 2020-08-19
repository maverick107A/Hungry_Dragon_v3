#ifndef GiantGolem_h__
#define GiantGolem_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGiantGolem : public Engine::CMonsterMain
{
private:
	explicit CGiantGolem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGiantGolem(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
private:
	HRESULT		Add_Component(void);

public:
	static CGiantGolem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXVECTOR3 m_vBodyPos;
	float		m_fAngle = 0;
	D3DXVECTOR3 m_vLeftArmPos;
	D3DXVECTOR3 m_vRightArmPos;
	D3DXVECTOR3 m_vHeadPos;

private:
	virtual void Free(void) override;

};


#endif // GiantGolem_h__
