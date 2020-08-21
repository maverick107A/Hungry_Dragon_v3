#ifndef RedCrystal_Monster_h__
#define RedCrystal_Monster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CRedCrystal_Monster : public Engine::CMonsterMain
{
private:
	explicit CRedCrystal_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRedCrystal_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
private:
	HRESULT		Add_Component(void);

public:
	static CRedCrystal_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

	void Update_Animation(const float & fTimeDelta);

private:
	D3DXVECTOR3 m_vBodyPos;
	D3DXVECTOR3 m_vBombPos;

	float		m_fAngle	  = 0;
	float		m_fLeft_Angle = 0;

	D3DXVECTOR3 m_vLeftArmPos;
	D3DXVECTOR3 m_vRightArmPos;
	D3DXVECTOR3 m_vUpArmPos;
	D3DXVECTOR3 m_vDownArmPos;
private:
	virtual void Free(void) override;

};


#endif // RedCrystal_Monster_h__
