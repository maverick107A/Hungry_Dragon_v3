#ifndef Tree_Locater_h__
#define Tree_Locater_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CRenderer;

END

class CTree_Object;
class CTerrain_Locater;

USING(Engine)

class CTree_Locater : public Engine::CGameObject
{
private:
	explicit CTree_Locater(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTree_Locater(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Locate_Tree();

private:
	HRESULT		Add_Component(void);

private:
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTransform*		m_pPlayerTrans = nullptr;
	CTerrain_Locater*		m_pTerrainLocater = nullptr;
	list<CTree_Object*> m_arrRenderGroupIdx[50];

public:
	static CTree_Locater*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
