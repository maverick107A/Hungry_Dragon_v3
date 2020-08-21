#ifndef GiantGolem_Body_h__
#define GiantGolem_Body_h__


#include "Define.h"
#include "MonsterMain.h"

BEGIN(Engine)

class CVICustom;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGiantGolem_Body : public Engine::CMonsterMain
{
private:
	explicit CGiantGolem_Body(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGiantGolem_Body(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	virtual void LateUpdate_Object(const float& fTimeDelta) override;

private:
	HRESULT		Add_Component(void);

public:
	static CGiantGolem_Body*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	D3DXVECTOR3 m_vBodyPos;


private:
	virtual void Free(void) override;

};


#endif // GiantGolem_Body_h__
