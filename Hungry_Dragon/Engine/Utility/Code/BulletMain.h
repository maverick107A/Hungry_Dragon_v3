#ifndef BulletMain_h__
#define BulletMain_h__

#include "GameObject.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;
class CMonsterBoard;

class ENGINE_DLL CBulletMain : public Engine::CGameObject
{

protected:
	explicit CBulletMain(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBulletMain(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
public:
	void	Dead_Bullet(void);
public:
	void	 Set_Pos(D3DXVECTOR3 _Pos);

public:
private:
	HRESULT		Add_Component(void);
	void		Key_Input(const float& fTimeDelta);

protected:
	Engine::CTransform*			m_pTransform = nullptr;
	Engine::CTransform*			m_pTransformX = nullptr;
	Engine::CMonsterBoard*		m_pBufferBoradCom = nullptr;
	Engine::CTexture_Cube*		m_pBufferCom = nullptr;
	Engine::CTexture*			m_pTextureCom = nullptr;
	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					vPlayerPos;
	int							m_iEvent = 0;
	float						 m_fDistance;

public:
	static CBulletMain*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual void Free(void) override;

};

END

#endif // BulletMain_h__