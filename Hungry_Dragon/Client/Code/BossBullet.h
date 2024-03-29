#ifndef Boss_Bullet_h__
#define Boss_Bullet_h__


#include "Define.h"
#include "BulletMain.h"

BEGIN(Engine)

class CTexture_Cube;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CBoss_Bullet : public Engine::CBulletMain
{

	enum BULLETSTATE { IDLE_BULLET, DEAD_BULLET, REFLECT_BULLET, STATE_END };


private:
	explicit CBoss_Bullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBoss_Bullet(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);
	void		State_Change();
public:
	static CBoss_Bullet*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

private:
	bool			m_bFirst = true;
	BULLETSTATE		m_preState;
	BULLETSTATE		m_eState;
	D3DXVECTOR3		m_vReflDir;
	D3DXVECTOR3		m_FirstPos;
	Engine::FRAME			m_tFrame;
};


#endif // Boss_Bullet_h__
