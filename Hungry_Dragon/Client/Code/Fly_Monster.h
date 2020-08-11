#ifndef Fly_Monster_h__
#define Fly_Monster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CFly_Monster  : public Engine::CMonsterMain
{
private:
	explicit CFly_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFly_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);
	void LateUpdate_Object(const float & fTimeDelta);
public:
	void Shooting(void);

public:
	static CFly_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

private:
	float m_fShotingLate = 0;
	float m_fHeight = 0;
};


#endif // Fly_Monster_h__
