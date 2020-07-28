#ifndef Fly_Monster_h__
#define Fly_Monster_h__


#include "Define.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeTex;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CFly_Monster : public CMonster
{
private:
	explicit CFly_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFly_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
public:
	void Shooting(void);

public:
	static CFly_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
	bool  m_bFirst = true;
	float m_fShotingLate = 0;
};


#endif // Fly_Monster_h__
