#ifndef FlyChaseGolem_h__
#define FlyChaseGolem_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CFlyChaseGolem : public Engine::CMonsterMain
{
private:
	explicit CFlyChaseGolem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFlyChaseGolem(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
private:
	HRESULT		Add_Component(void);

public:
	static CFlyChaseGolem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXVECTOR3 m_vBodyPos;
	D3DXVECTOR3 m_vBombPos;
	float	m_fMaxHalfScale;
	float		m_fAngle = 0;
	D3DXVECTOR3 m_vLeftArmPos;
	D3DXVECTOR3 m_vRightArmPos;
private:
	virtual void Free(void) override;

};


#endif // FlyChaseGolem_h__
