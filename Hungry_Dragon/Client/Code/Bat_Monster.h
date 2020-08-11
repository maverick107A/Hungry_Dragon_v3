#ifndef Bat_Monster_h__
#define Bat_Monster_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CMonsterBoard;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CBat_Monster : public Engine::CMonsterMain
{
private:
	explicit CBat_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBat_Monster(void);
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
	static CBat_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXMATRIX		matBilboard;
private:
	virtual void Free(void) override;

};


#endif // Bat_Monster_h__
