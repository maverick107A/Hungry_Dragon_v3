#ifndef Cliff_Locater_h__
#define Cliff_Locater_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;
class CBaseLand;
class CHeightCol;

END

class CCliff_Object;

USING(Engine)

class CCliff_Locater : public Engine::CGameObject
{
private:
	explicit CCliff_Locater(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCliff_Locater(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;


private:
	HRESULT		Add_Component(void);
	

private:
	Engine::CTransform*		m_pTransform;
	Engine::CTransform*		m_pPlayerTrans = nullptr;
	vector<CCliff_Object*>	m_vecCliff;
	_uint					m_uLength;
	_uint					m_uVerCntX;
	_uint					m_uVerCntZ;

public:
	static CCliff_Locater*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
