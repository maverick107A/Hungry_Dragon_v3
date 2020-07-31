#ifndef Ocean_h__
#define Ocean_h__

#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CLandTex;
class CTransform;
class CTexture;

END
class COcean : public Engine::CGameObject
{
private:
	explicit COcean(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~COcean(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
	

private:
	HRESULT		Add_Component(void);

private:
	Engine::CLandTex*		m_pBufferCom = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTexture*		m_pTexture = nullptr;
	float m_fLoopCnt = 0.f;

public:
	static COcean*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};

#endif // BackGround_h__
