#ifndef Player_h__
#define Player_h__

#include "Define.h"
#include "GameObject.h"


BEGIN(Engine)

class CCubeTex;
class CTexture;
class CTransform;

END

class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;



private:
	HRESULT		Add_Component(void);


private:
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CCubeTex*			m_pBufferCom = nullptr;
	D3DXVECTOR3					m_vLook;
public:
	static CPlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void) override;

};


















#endif // Player_h__
