#ifndef BackGround_h__
#define BackGround_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CTerrain;
class CTransform;

END
class CBackGround : public Engine::CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBackGround(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);

private:
	Engine::CTerrain*		m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

public:
	static CBackGround*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
