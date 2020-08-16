#ifndef BeamBase_h__
#define BeamBase_h__

#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CTransform;


class ENGINE_DLL CBeamBase : public Engine::CGameObject
{

protected:
	explicit CBeamBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBeamBase(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	HRESULT		Add_Component(void);

protected:
	Engine::CTransform*			m_pTransform = nullptr;
	Engine::CTexture*			m_pTextureCom = nullptr;

public:
	static CBeamBase*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual void Free(void) override;

};

END

#endif // BeamBase_h__