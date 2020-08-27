#ifndef Goal_h__
#define Goal_h__


#include "Define.h"
#include "GameObject.h"

BEGIN(Engine)

class CMonsterBoard;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CGoal : public Engine::CGameObject
{
private:
	explicit CGoal(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGoal(void);

public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	HRESULT		Add_Component(void);

public:
	static CGoal*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CMonsterBoard*		m_pBufferBoradCom = nullptr;
	D3DXMATRIX		matBilboard;
	float m_fHeight = 0;

private:
	virtual void Free(void) override;

};


#endif // Goal_h__
