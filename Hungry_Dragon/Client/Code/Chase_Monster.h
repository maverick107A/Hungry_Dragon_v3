#ifndef Chase_Monster_h__
#define Chase_Monster_h__


#include "Define.h"
#include "MonsterMain.h"


BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;
class CTerrainTex;


END

class  CChase_Monster : public Engine::CMonsterMain
{
private:
	explicit CChase_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CChase_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;

private:
	HRESULT		Add_Component(void);

public:
	static CChase_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);


private:

	virtual void Free(void) override;

};


#endif // Chase_Monster_h__
