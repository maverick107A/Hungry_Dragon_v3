#ifndef Normal_Bullet_h__
#define Normal_Bullet_h__


#include "Define.h"
#include "Bullet.h"

BEGIN(Engine)

class CCubeTex;
class CTexture;
class CTransform;
class CTerrainTex;

END

class  CNormal_Bullet : public CBullet
{
private:
	explicit CNormal_Bullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNormal_Bullet(void);
public:
	virtual HRESULT Ready_Object(void) override;
	virtual int Update_Object(const float& fTimeDelta) override;
	virtual void Render_Object(void) override;
private:
	HRESULT		Add_Component(void);

public:
	static CNormal_Bullet*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

private:
	bool m_bFirst = true;

};


#endif // Normal_Bullet_h__
