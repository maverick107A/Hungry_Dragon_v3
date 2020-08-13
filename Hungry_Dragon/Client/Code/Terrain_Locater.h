#ifndef Terrain_Locater_h__
#define Terrain_Locater_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CHeightCol;
class CTransform;
class CRenderer;
class CBaseLand;

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
	virtual void Initialize_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	_uint Get_CurrSectorNum() { return m_uCurrSectorNum; }
	list<_uint>& Get_RenderIdx() { return m_lstRenderIdx; }
	vector<int> Get_PartsHeight(_uint _uNum);
	Engine::CBaseLand*	Get_Terrain();

private:
	HRESULT		Add_Component(void);

private:
	Engine::CHeightCol*		m_pDummy = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTransform*		m_pPlayerTrans = nullptr;

	CTerrain_Parts*	m_pParts[50] = { 0 };

	list<_uint> m_lstRenderIdx;
	_uint m_uOldSectorNum = 0;
	_uint m_uCurrSectorNum = 0;

public:
	static CTerrain_Locater*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
