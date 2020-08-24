#ifndef CompassCon_h__
#define CompassCon_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CTransform;

END

USING(Engine)

class CCompassCon : public Engine::CGameObject
{
private:
	explicit CCompassCon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCompassCon(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

public:
	void Set_Trans(_vec3& _vPos);
	void Set_Scale(_uint _uTimes);
	void Set_Destroyed(_bool _bDes) { m_bDestroyed = _bDes; }
	IDirect3DBaseTexture9*	Get_Texture(_uint _uNum=0);


private:
	HRESULT		Add_Component(void);

private:
	Engine::CTexture*		m_pTex = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

private:
	Engine::_bool			m_bDestroyed = true;

public:
	static CCompassCon*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // Terrain_h__
