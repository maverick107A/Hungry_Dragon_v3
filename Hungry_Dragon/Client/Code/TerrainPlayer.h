#ifndef TerrainPlayer_h__
#define TerrainPlayer_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CForestLand;
class CTexture;
class CTransform;
class CRenderer;

END

USING(Engine)

class CTerrainPlayer : public Engine::CGameObject
{
private:
	explicit CTerrainPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTerrainPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);

private:
	Engine::CForestLand*			m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;
	Engine::CTexture*		m_pSkyTex;

	ID3DXMesh*		m_pSkyBox;

public:
	static CTerrainPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
