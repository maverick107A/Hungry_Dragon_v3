#ifndef HorizonBat_Monster_h__
#define HorizonBat_Monster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CMonsterBoard;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CHorizonBat_Monster : public Engine::CMonsterMain
{
private:
	explicit CHorizonBat_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CHorizonBat_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;
public:
	void Update_Animation(const float& fTimeDelta);


private:
	HRESULT		Add_Component(void);

public:
	static CHorizonBat_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXMATRIX		matBilboard;
	float m_fHeight = 0;
private:
	virtual void Free(void) override;

};


#endif // HorizonBat_Monster_h__
