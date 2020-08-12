#ifndef Terrain_Locater_h__
#define Terrain_Locater_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CHeightCol;
class CTransform;
class CRenderer;

END

class CTerrain_Parts;

USING(Engine)

class CTerrain_Locater : public Engine::CGameObject
{
private:
	explicit CTerrain_Locater(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTerrain_Locater(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;


private:
	HRESULT		Add_Component(void);

private:
	Engine::CHeightCol*		m_pDummy = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

	CTerrain_Parts*	m_pParts[50] = { 0 };

public:
	static CTerrain_Locater*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__