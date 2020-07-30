#ifndef Chase_Monster_h__
#define Chase_Monster_h__


#include "Define.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeTex;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CChase_Monster : public CMonster
{
private:
	explicit CChase_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CChase_Monster(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);

public:
	static CChase_Monster*	Create(LPDIRECT3DDEVICE9 pGraphicDev, D3DXVECTOR3 _pos);
private:
	virtual void Free(void) override;
	float Move_Terrain(void);

};


#endif // Chase_Monster_h__
